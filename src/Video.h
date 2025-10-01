#pragma once
#include "./ComposedWidget.h"
#include "mlprocess.h"
#include <boost/concept_check.hpp>
#include <mutex>
#include <atomic>
#include "./Image.h"
#include "./GuiEvents.h"
#include "./VideoCache.h"
#include "./VideoSound.h"

//you can react the the events (acessible via the methd events()) the data is in long : 
// frame-changed
// played
// paused
// frame-loaded
// metadata-changed - void
// speed-changed - double
// volume-changed - double


namespace ml
{
    class Box;
    class Popover;
    class Label;
    class Video : public ComposedWidget
    {

        public:
            Video(ml::Box* parent);
            Video(ml::Box* parent, const std::string& filepath);
            virtual ~Video() = default;

            void setPath(const std::string& filepath);
            std::string path()const {return _filepath;}

            virtual void addEventListener(Event event, const std::function<void(EventInfos&)>& callback);

            virtual void setHAlign(HAlignment align);
            virtual void setVAlign(VAlignment align);

            virtual void setHExpand(bool value=true);
            virtual void setVExpand(bool value=true);

            void play();
            void pause();
            void toggle();
            bool playing()const {return _playing;}
            long currentFrame() const;
            double duration() const{ return _duration; }
            double currentTime() const;
            void nextFrame();
            void prevFrame();
            void seekToFrame(long frame, bool ignoreSound = false);
            void seek(double time, bool ignoreSound = false);
            void seekToRatio(double ratio);

            void setDefaultEvents();

            void showImage(const VideoImgData& data);
            void showImageIdx(long frame);
            void showImageAtTime(double time);

            size_t frameCount() const { return _cache.totalImages(); }

            //time in seconds
            int frameIdxFromTime(double time) const;
            double timeFromFrameIdx(long idx) const;
            int frameIdxFromRatio(double ratio) const;

            bool loaded(long frame);
            double frameDuration() const;
            ml::Events& events() {return _events;}

            std::string popoverInfos() const;
            void showPopoverInfos();

            void setSpeed(double speed);
            void setVolume(double volume);

            float speed() const { return _speed; }
            double volume() const { return _volume; }

            void setDefaultSettings();

        protected:
            ml::GuiEvents _events;
            std::string _filepath;
            std::string _lastError;
            int _quality = 5;

            mutable std::mutex _procMtx;
            Process _ffmpeg;

            std::shared_ptr<Box> _box;
            std::shared_ptr<Popover> _popover;
            std::shared_ptr<Label> _popoverLabel;

            void __construct(ml::Box* parent);

            bool _getVideoData();

            //callback is executed on the mainthread
            void _getVideoData_async(const std::function<void()>& callback);

            // will get the video data with ffprobe before starting the ffmpeg process
            void _startLoadingForTheFirstTime();
            void _startLoadingVideoForTheFirstTime();
            void _startLoadingSoundForTheFirstTime();
            void _startProcess(double startTime=0, int framesToLoad=2000);
            void _stopProcess();
            void _onFrameLoaded(long idx);

            bool _currentFrameNotShown = true;
            bool _stoppingProcess = false;
            bool _wasPausedBecauseOfNeedToLoad = false;

            //only when a process need to be started
            bool _needToWaitForSeek = false;

            std::string _ffmpeg_path() const;
            std::string _ffprobe_path() const;

            mutable std::mutex _metadataMtx;
            double _duration = -1;
            double _width = -1;
            double _height = -1;
            double _fps = -1;
            double _bitRate = -1;

            std::atomic_bool _loadingData = false;

            void _onffmpegOut(const std::vector<unsigned char>& data_chunk);

            mutable std::mutex _cacheMtx;
            mutable std::mutex _bufMtx;
            std::vector<unsigned char> _ffmpegInputBuf;

            VideoCache _cache;

            Image* _image = nullptr;
            long _currentFrame = -1;

            //default events list
            bool _dragging = false;
            void _onkeydown(EventInfos& infos);
            void _onmousemove(EventInfos& infos);
            void _onmouseup(EventInfos& infos);

            bool loading() {return _ffmpeg.running();}

            bool _have_sound = false; //changed
            bool _playing = false;

            int _intervalPlayId = -1;
            int _minIntervalBeforePreLoad = 100;

            double _lastRatioSeeked = -1;
            long _lastFrameShown = -1;
            std::atomic_long _lastProcessFrame = -1;

            float _speed = 1;
            float _volume = 1;

            VideoSound _sound;
    };
}
