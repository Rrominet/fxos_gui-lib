#include "./Video.h"
#include "enums.h"
#include "files.2/files.h"
#include "mlTime.h"
#include "str.h"

#include "./Box.h"
#include "./Box.hpp"

#include "./Popover.h"

#include "ffmpeg.h"
#include "./App.h"

#include <any>
#include <fstream>

namespace ml
{
    static const unsigned char SOI[] = { 0xFF, 0xD8 };
    static const unsigned char EOI[] = { 0xFF, 0xD9 };

    Video::Video(ml::Box* parent) : _events(ml::app())
    {
        __construct(parent);
    }

    Video::Video(ml::Box* parent, const std::string& filepath) : _events(ml::app())
    {
        __construct(parent);
        this->setPath(filepath);
    }

    void Video::__construct(ml::Box* parent)
    {
        _box = parent->createBox();
        _box->addCssClass("video-container");
        _composed.push(_box.get());

        _popover = parent->createPopover();
        _popoverLabel = _popover->createLabel();

        _image = _box->createImage(false).get();
        _image->setFocusable(true);
        _image->addEventListener(LEFT_UP,[this](EventInfos &) {_image->focus();});

        _ffmpeg.treatOutputAsBinary();
        _ffmpeg.addOnOutputBin([this](const std::vector<unsigned char>& data_chunk){_onffmpegOut(data_chunk);});

        _events.add("frame-loaded", [this]{this->_onFrameLoaded(std::any_cast<long>(_events.data()));});
        _sound.events().add("error", [this]{this->pause(); _have_sound = false;});
        _sound.events().add("loaded", [this]{this->pause(); _have_sound = true;});
    } 

    void Video::setPath(const std::string& filepath)
    {
        {
            std::lock_guard<std::mutex> lock(_procMtx);
            _stopProcess();
        }
        this->setDefaultSettings();
        _filepath = filepath;
        _sound.setPath(_filepath);
        _startLoadingForTheFirstTime();
    }

    void Video::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        _box->addEventListener(event, callback);
    }

    void Video::setHAlign(HAlignment align)
    {
        _box->setHAlign(align);	
    }

    void Video::setVAlign(VAlignment align)
    {
        _box->setVAlign(align);	
    }

    void Video::setHExpand(bool value)
    {
        _box->setHExpand(value);	
    }

    void Video::setVExpand(bool value)
    {
        _box->setVExpand(value);	
    }

    std::string Video::_ffmpeg_path() const
    {
#ifdef _WIN32
        return "ffmpeg.exe";
#else 
        return "/usr/bin/ffmpeg";	
#endif
    }

    std::string Video::_ffprobe_path() const
    {
#ifdef _WIN32
        return "ffprobe.exe";
#else 
        return "/usr/bin/ffprobe";	
#endif
    }

    bool Video::_getVideoData()
    {
        json data;
        try
        {
            data = ffprobe::data(_filepath, _ffprobe_path());
        }
        catch(const std::exception& e)
        {
            lg("metadata from the video failed : ");
            lg(e.what());
            return false;
        }
        {
            std::lock_guard<std::mutex> lock(_metadataMtx);
            _duration = ffprobe::duration(data);
            _width = ffprobe::width(data);
            _height = ffprobe::height(data);
            _fps = ffprobe::fps(data);
            _bitRate = ffprobe::bitRate(data);

        }
        {
            std::lock_guard<std::mutex> lk(_cacheMtx);
            _cache.setTotalImages(ffprobe::framesNumber(data));
        }

        _events.emit("metadata-changed");
        return true;
    }

    void Video::_getVideoData_async(const std::function<void()>& callback)
    {
        if (_loadingData)
        {
            _lastError = "Video data is already loading... Retry later.";
            return;
        }
        _loadingData = true;
        std::thread t([this, callback](){
                if (_getVideoData())
                    ml::app()->queue(callback);
                _loadingData = false;
                });
        t.detach();
    }

    void Video::_startLoadingForTheFirstTime()
    {
        _startLoadingVideoForTheFirstTime();
        _startLoadingSoundForTheFirstTime();
    }

    void Video::_startLoadingVideoForTheFirstTime()
    {
        if (_filepath.empty())
        {
            _lastError = "Video filepath is empty";
            lg2("Error", _lastError);
            return;
        }

        if (!files::exists(_filepath))
        {
            _lastError = "Video filepath does not exist : " + _filepath;
            lg2("Error", _lastError);
            return;
        }

        if (files::type(_filepath) != files::VIDEO)
        {
            _lastError = "Video filepath is not a video : " + _filepath;
            lg2("Error", _lastError);
            return;
        }

        {
            std::lock_guard lk(_cacheMtx);
            _cache.clearAll();
        }

        auto spc_f = [this]
        {
            _currentFrame = 0;
            _startProcess(0);
        }; 

        _getVideoData_async(spc_f);
    }

    void Video::_startLoadingSoundForTheFirstTime()
    {
        _sound.load_async();
    }

    void Video::_startProcess(double startTime, int framesToLoad)
    {
        if (startTime > this->duration() - 0.1)
            return;

        if (_needToWaitForSeek)
            return;

        {
            std::lock_guard<std::mutex> lock(_procMtx);
            _stopProcess();
            _stoppingProcess = false;

            _needToWaitForSeek = true; // hcanged

            auto frame = this->frameIdxFromTime(startTime);
            _cache.setFrameBeingLoaded(frame);
            _lastProcessFrame = frame;
            std::vector<std::string> cmd = {_ffmpeg_path(),
                "-nostdin",
                "-ss", ml::time::asVideoTime(startTime),
                "-i", _filepath, 
                "-vframes", str::fromInt(framesToLoad),
                "-f", "image2pipe",  
                "-vcodec", "mjpeg",
                "-qscale:v", str::fromInt(_quality),
                "-vsync", "0", "-an", "-"
            };

            lg2("ffmpeg cmd", process::to_string(cmd));
            _ffmpeg.setCmd(cmd);
            _ffmpeg.start();
        }

        ml::app()->setTimeout([this]{_needToWaitForSeek = false;}, 500);
    }

    void Video::_onFrameLoaded(long idx)
    {
        lg("frame-loaded " << idx << " frame-current : " << _currentFrame << " frame-not-shown : " << _currentFrameNotShown);
        if (idx == _currentFrame && _currentFrameNotShown)
            this->showImageIdx(idx);

        if (_wasPausedBecauseOfNeedToLoad)
        {
            this->play();
            _wasPausedBecauseOfNeedToLoad = false;
        }
    }

    void Video::_stopProcess()
    {
        _stoppingProcess = true;
        lg("terminating ffmpeg...");
        _ffmpeg.terminate(true);
        lg("ffmpeg terminated.");

        lg("clearing buffered data...");
        std::lock_guard<std::mutex> lk(_bufMtx);
        _ffmpegInputBuf.clear();
        lg("buffered data cleared.");
    }

    void Video::_onffmpegOut(const std::vector<unsigned char>& data_chunk)
    {
        std::lock_guard<std::mutex> lock(_bufMtx);
        _ffmpegInputBuf.insert(_ffmpegInputBuf.end(), data_chunk.begin(), data_chunk.end());

        // Search for complete JPEGs in buffer
        size_t start = 0;
        while (true) 
        {
            if (_stoppingProcess) 
                break;
            // Find SOI
            auto soi = std::search(_ffmpegInputBuf.begin() + start, _ffmpegInputBuf.end(),
                    std::begin(SOI), std::end(SOI));

            if (soi == _ffmpegInputBuf.end()) break;

            // Find EOI after SOI
            auto eoi = std::search(soi + 2, _ffmpegInputBuf.end(),
                    std::begin(EOI), std::end(EOI));

            if (eoi == _ffmpegInputBuf.end()) break;

            eoi += 2; // include the EOI marker
            VideoImgData img;
            img.frame = _cache.frameBeingLoaded();
            img.data = std::vector<unsigned char>(soi, eoi);
            img.format = JPEG;
            {
                std::lock_guard<std::mutex> lock(_cacheMtx);
                _cache.add(img);
            }

            // Erase processed bytes
            _ffmpegInputBuf.erase(_ffmpegInputBuf.begin(), eoi);
            start = 0; // restart from beginning

            _events.emit("frame-loaded", _cache.frameBeingLoaded());
            _cache.setFrameBeingLoaded(_cache.frameBeingLoaded() + 1);
        }

        auto clear_f = [this]
        {
            std::lock_guard<std::mutex> lock(_cacheMtx);
            _cache.clearIfNeeded(_cache.lastLoaded());
        };

        std::thread(clear_f).detach();
    }

    void Video::showImage(const VideoImgData& data)
    {
        _currentFrame = data.frame;
        if (data.data.size() == 0)
        {
            _currentFrameNotShown = true;
            return;
        }
        _image->loadFromMemory(data.data, data.format);
        _currentFrameNotShown = false;
        if (_lastFrameShown != _currentFrame)
        {
            _events.emit("frame-changed", _currentFrame);
            _lastFrameShown = data.frame;
        }
    }

    void Video::showImageIdx(long frame)
    {
        std::lock_guard<std::mutex> lock(_cacheMtx);
        if (_cache.exists(frame))
            this->showImage(_cache[frame]);
    }

    void Video::showImageAtTime(double time)
    {
        this->showImageIdx(this->frameIdxFromTime(time));
    }

    void Video::play()
    {
        lg("play " << _playing);
        if (_playing)
            return;

        if (_intervalPlayId != -1)
            ml::app()->removeInterval(_intervalPlayId);

        auto timeinterval = [this]
        {
            if (!_have_sound)
                this->nextFrame();
            else 
                this->seek(_sound.currentTime(), true);
        };

        if (!_have_sound)        {
            auto ms = this->frameDuration() * (1.0/_speed);
            lg("timeinterval : " << ms);
            if (ms < 0)
                return;
            _intervalPlayId = ml::app()->setInterval(timeinterval, ms);
        }
        else 
        {
            if (_sound.loaded())
            {
                _sound.play();
                auto ms = this->frameDuration();
                if (ms < 0)
                    return;
                _intervalPlayId = ml::app()->setInterval(timeinterval, ms);
            }
            else 
                lg("sound not loaded yet.");
        }
        _playing = true;

        _events.emit("played");
    }

    void Video::pause()
    {
        if (!_playing)
            return;

        if (_intervalPlayId != -1)
            ml::app()->removeInterval(_intervalPlayId);

        if (_have_sound && _sound.loaded())
            _sound.pause();

        _playing = false;
        _events.emit("paused");
    }

    void Video::toggle()
    {
        if (_playing)
            this->pause();
        else
            this->play();
    }

    long Video::currentFrame() const
    {
        return _currentFrame;
    }

    double Video::currentTime() const
    {
        return this->timeFromFrameIdx(_currentFrame); 
    }

    void Video::nextFrame()
    {
        _currentFrame++;
        if (_currentFrame >= this->frameCount())
            _currentFrame = 0;
        this->seekToFrame(_currentFrame);
    }

    void Video::prevFrame()
    {
        _currentFrame--;
        if (_currentFrame <= 0)
            _currentFrame = this->frameCount() - 1;
        this->seekToFrame(_currentFrame);
    }

    void Video::seekToFrame(long frame, bool ignoreSound )
    {
        if (this->loaded(frame))
        {
            this->showImageIdx(frame);    
            if (_cache.lastLoaded() < frame - _minIntervalBeforePreLoad && 
                    _lastProcessFrame < frame + _minIntervalBeforePreLoad * 3 * _speed)
            {
                lg("last Profress Frame started : " << _lastProcessFrame << " < " << frame + _minIntervalBeforePreLoad * 3);
                _startProcess(this->timeFromFrameIdx(_cache.lastLoaded()));
            }
        }

        else 
        {
            _currentFrame = frame;
            _currentFrameNotShown = true;
            if (_playing)
            {
                this->pause();
                _wasPausedBecauseOfNeedToLoad = true;
            }
            _startProcess(this->timeFromFrameIdx(frame));
        }

        if (!ignoreSound && _have_sound)
            _sound.seek(this->timeFromFrameIdx(frame));
    }

    void Video::seek(double time, bool ignoreSound )
    {
        lg("seeking to " << time);
        this->seekToFrame(this->frameIdxFromTime(time), ignoreSound);
    }

    void Video::seekToRatio(double ratio)
    {
        this->seekToFrame(this->frameIdxFromRatio(ratio));
        _lastRatioSeeked = ratio;
    }

    void Video::_onkeydown(EventInfos& infos)
    {
        if (infos.key == "Left" && !infos.ctrl)
            this->prevFrame();
        else if (infos.key == "Right" && !infos.ctrl)
            this->nextFrame();
        else if (infos.key == "Left" && infos.ctrl)
            this->setSpeed(_speed - 0.5);
        else if (infos.key == "Right" && infos.ctrl)
            this->setSpeed(_speed + 0.5);
        else if (infos.key == "space")
            this->toggle();
        else if (infos.key == "i" && infos.ctrl)
            this->showPopoverInfos();
        else if (infos.key == "Up")
            this->seekToFrame(_currentFrame + 25);
        else if (infos.key == "Down")
            this->seekToFrame(_currentFrame - 25);

        infos.preventDefault = false;
    }

    void Video::_onmousemove(EventInfos& infos)
    {
        if (_dragging)
        {
            double ratio = (double)infos.x / (double)_image->width();
            if (_lastRatioSeeked == ratio)
                return;
            this->seekToRatio(ratio);
        }
    }

    void Video::_onmouseup(EventInfos& infos)
    {
        _onmousemove(infos);
        _dragging = false;
    }

    void Video::setDefaultEvents()
    {
        _image->addEventListener(KEY_DOWN, [this](EventInfos & ev){_onkeydown(ev);});
        _image->addEventListener(RIGHT_DOWN, [this](EventInfos& e){_dragging = true;});
        _image->addEventListener(RIGHT_UP, [this](EventInfos& e){_onmouseup(e);});
        _image->addEventListener(MOUSE_MOVE, [this](EventInfos& e){_onmousemove(e);});
    }

    int Video::frameIdxFromTime(double time) const
    {
        auto _r = static_cast<long>(time * _fps);
        if (_r >= this->frameCount())
            _r = this->frameCount() - 1;
        return _r;
    }

    double Video::timeFromFrameIdx(long idx) const
    {
        if (_fps == 0)
            return 0;
        return static_cast<double>(idx) / _fps;
    }

    int Video::frameIdxFromRatio(double ratio) const
    {
        auto duration = this->duration() * ratio;
        return this->frameIdxFromTime(duration);
    }

    bool Video::loaded(long frame)
    {
        std::lock_guard lk(_cacheMtx);
        if (!_cache.exists(frame))
            return false;
        return _cache[frame].data.size() > 0;
    }

    double Video::frameDuration() const
    {
        if (_fps == 0)
            return 0;
        return 1000.0 / _fps;
    }

    std::string Video::popoverInfos() const
    {
        std::string _r;
        _r = "Current Frame : " + std::to_string(_currentFrame) + " / " + std::to_string(this->frameCount()) + "\n";
        _r += "Current Time : " + std::to_string(this->currentTime()) + " / " + std::to_string(this->duration()) + "\n";
        _r += "Fps : " + std::to_string(_fps) + "\n";
        _r += "1 Frame Duration : " + math::round(this->frameDuration() * 1000) + "ms\n\n";

        std::lock_guard lk(_cacheMtx);
        _r += "Frames cached : " + std::to_string(_cache.size());
        return _r;
    }

    void Video::showPopoverInfos()
    {
        _popover->show(); 
        _popoverLabel->setText(this->popoverInfos());
    }

    void Video::setSpeed(double speed)
    {
        _speed = speed;
        if (_have_sound)
            _sound.setSpeed(speed);
        
        //force update the interval time
        if (_playing && !_have_sound)
        {
            this->pause();
            this->play();
        }
        _events.emit("speed-changed", _speed);
    }

    void Video::setVolume(double volume)
    {
        if (!_have_sound)
            return;
        _volume = volume;
        _sound.setVolume(_volume);
        _events.emit("volume-changed", _volume);
    }

    void Video::setDefaultSettings()
    {
        this->pause();
        _speed = 1.0;
        _volume = 1.0;
        _duration = -1;
        _width = -1;
        _height = -1;
        _fps = -1;
        _bitRate = -1;
        _currentFrame = -1;
        _lastProcessFrame = -1;
        _have_sound = false; //changed
        _dragging = false;
        _lastFrameShown = -1;
        _lastRatioSeeked= -1;
        _currentFrameNotShown = true;
    }
}
