#include "./VideoSound.h"
#include "sound/mlSound.h"
#include "ffmpeg.h"
#include "debug.h"
#include "thread.h"
#include "str.h"
#include "mlTime.h"

namespace ml
{
    namespace bp = boost::process;
    VideoSound::VideoSound(){}
    VideoSound::VideoSound(const std::string& path)
    {
        this->setPath(path);
    }

    VideoSound::~VideoSound()
    {
        std::lock_guard<std::mutex> lock(_mtx);
        if (_sys)  
            _sys->release();
    }

    std::string VideoSound::_ffprobe_path() const
    {
#ifdef _WIN32
        return "ffprobe.exe";
#else 
        return "/usr/bin/ffprobe";	
#endif
    }

    std::string VideoSound::_ffmpeg_path() const
    {
#ifdef _WIN32
        return "ffmpeg.exe";
#else 
        return "/usr/bin/ffmpeg";	
#endif
    }


    void VideoSound::load_async()
    {
        auto f = [this]
        {
            std::lock_guard<std::mutex> lock(_mtx);
            std::string cmd = ffmpeg::pcm(_path, _ffmpeg_path());
            try
            {
                _data = ffprobe::audioStream(_path, _ffprobe_path());
            }
            catch(const std::exception& e)
            {
                lg(e.what());
                _events.emit("error", _S"Invalid sound data, ffmpeg could not decode the file.");
                return;
            }

            float rate = -1;
            int channels = -1;
            double duration = -1;

            if (_data.contains("sample_rate"))
                rate = stof(_data["sample_rate"].get<std::string>());
            if (_data.contains("channels"))
                channels = _data["channels"].get<int>();

            if (_data.contains("duration"))
                duration = stod(_data["duration"].get<std::string>());
            else if (_data.contains("tags"))
            {
                if (_data["tags"].contains("DURATION"))
                    duration = ml::time::asSeconds(_data["tags"]["DURATION"].get<std::string>());
            }

            if (rate == -1 || channels == -1 || duration == -1)
            {
                lg("Invalid sound data : rate : " << rate << " channels : " << channels << " duration : " << duration);
                _events.emit("error", _S"Invalid sound data");
                return;
            }

            int length = rate  * channels * sizeof(float) * duration;

            _sys = mlSystem::createAndInit();

            FMOD_CREATESOUNDEXINFO infos;
            memset(&infos, 0, sizeof(FMOD_CREATESOUNDEXINFO));
            infos.length = length ;
            infos.numchannels = channels;
            infos.defaultfrequency = rate;
            infos.format = FMOD_SOUND_FORMAT_PCMFLOAT;
            infos.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
            infos.suggestedsoundtype = FMOD_SOUND_TYPE_RAW;

            try 
            {
                bp::ipstream is;
                bp::child c(cmd, bp::std_out > is);
                lg("trying to read the data");
                char* sound_data = (char*)malloc(length);
                bytes = length;
                lg("process finished.");
                while (c.running() && is.read(sound_data, length))
                {
                    lg("data readed.");
                }
                lg("quitting the loop");

                FMOD_RESULT res;
                _sound = _sys->soundFromData((const char*)sound_data, &infos);
                _sound->preloadChannel();
                _loaded = true;
                _events.emit("loaded");
            }
            catch (const std::exception& e)
            {
                lg(e.what());
            }
        };
        std::thread(f).detach();
    }

    void VideoSound::play()
    {
        try_guard(_mtx);
        if (!lk.owns_lock()) 
            return;
        _sound->play();
    }

    void VideoSound::pause()
    {
        try_guard(_mtx);
        if (!lk.owns_lock()) 
            return;
        _sound->pause();
    }

    void VideoSound::setPath(const std::string& path)
    {
        std::lock_guard<std::mutex> lock(_mtx);
        _path = path;
        if (!_sys)
            return;
        _data = json::object();
        _sys->removeSound(_sound);
        _sound = nullptr;
        _loaded = false;
    }

    bool VideoSound::loaded() const
    {
        std::lock_guard<std::mutex> lock(_mtx);
        return _loaded;
    }

    double VideoSound::currentTime()const
    {
        std::lock_guard<std::mutex> lock(_mtx);
        return _sound->position()/_sound->freq() * _speed;
    }

    void VideoSound::seek(double time)
    {
        try_guard(_mtx);
        if (!lk.owns_lock())
        {
            _events.add("loaded", [this, time]{this->seek(time);});
            return;
        }
        if (!_loaded)
        {
            _events.add("loaded", [this, time]{this->seek(time);});
            return;
        }
        _sound->setMsposition(time*1000.0);
    }

    void VideoSound::setVolume(double volume)
    {
        std::lock_guard<std::mutex> lock(_mtx);
        _sound->setVolume(volume);
    }

    double VideoSound::volume() const
    {
        std::lock_guard<std::mutex> lock(_mtx);
        return _sound->volume();
    }

    void VideoSound::setSpeed(double speed)
    {
        _speed = speed;
        std::lock_guard<std::mutex> lock(_mtx);
        _sound->setSpeed(speed);
    }

    double VideoSound::speed() const
    {
        std::lock_guard<std::mutex> lock(_mtx);
        return _sound->speed();
    }
}    
