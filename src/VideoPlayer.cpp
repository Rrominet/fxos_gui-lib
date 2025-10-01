#include "./VideoPlayer.h"
#include "./Video.h"
#include "./TimeSliderInOut.h"
#include "./Label.h"
#include "./Box.h"

#include "./Box.hpp"

namespace ml
{

    VideoPlayer::VideoPlayer(ml::Box* parent)
    {
        _init(parent);
    }

    VideoPlayer::VideoPlayer(ml::Box* parent,const std::string& filepath)
    {
        _init(parent);
        this->setPath(filepath);
    }

    void VideoPlayer::_init(ml::Box* parent)
    {
        _container = parent->createBox().get();
        _composed.push(_container);
        _container->addCssClass("video-player");

        _video = (Video*)_container->createComposedWidget<Video>(parent).get();
        _video->setHExpand();
        _video->setVExpand();
        _video->setHAlign(FILL);

        _sliderContainer = _container->createBox().get();
        //TODO : create the 3 labels.
        _slider = (TimeSliderInOut*)_sliderContainer->createComposedWidget<TimeSliderInOut>(parent).get();
        _setEvents();
    }

    void VideoPlayer::_setEvents()
    {
        _video->setDefaultEvents();
        auto onmetadataChanged = [this]
        {
            _slider->setMax(_video->duration());
            _slider->setMin(0);
            _slider->setStart(0);
            _slider->setEnd(_video->duration());
        };

        _video->events().add("metadata-changed", onmetadataChanged);

        auto onfchanged = [this]
        {
            long f = _video->events().data<long>();
            _slider->setCurrent(_video->timeFromFrameIdx(f), false);
        };

        _video->events().add("frame-changed", onfchanged);

        auto onschanged = [this]
        {
            _video->events().block();
            _video->seek(_slider->events().data<double>());
            _video->events().allow();
        };
        _slider->events().add("current-changed", onschanged);

    }

    void VideoPlayer::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        _container->addEventListener(event, callback);
    }

    void VideoPlayer::setPath(const std::string& filepath)
    {
        _video->setPath(filepath);
    }

    std::string VideoPlayer::path() const
    {
        return _video->path();
    }

    void VideoPlayer::setHAlign(HAlignment align)
    {
        _container->setHAlign(align); 
    }

    void VideoPlayer::setVAlign(VAlignment align)
    {
        _container->setVAlign(align);
    }

    void VideoPlayer::setHExpand(bool value)
    {
        _container->setHExpand(value);
    }

    void VideoPlayer::setVExpand(bool value)
    {
        _container->setVExpand(value);
    }

    void VideoPlayer::play()
    {
        _video->play();
    }

    void VideoPlayer::pause()
    {
        _video->pause();
    }

    void VideoPlayer::toggle()
    {
        _video->toggle();
    }

    bool VideoPlayer::playing() const
    {
        return _video->playing();
    }

    long VideoPlayer::currentFrame() const
    {
        return _video->currentFrame(); 
    }

    double VideoPlayer::duration() const
    {
        return _video->duration();
    }

    double VideoPlayer::currentTime() const
    {
        return _video->currentTime();
    }

    void VideoPlayer::nextFrame()
    {
        _video->nextFrame();
    }

    void VideoPlayer::prevFrame()
    {
        _video->prevFrame();
    }

    void VideoPlayer::seekToFrame(long frame)
    {
        _video->seekToFrame(frame);
    }

    void VideoPlayer::seek(double time)
    {
        _video->seek(time);
    }

    void VideoPlayer::seekToRatio(double ratio)
    {
        _video->seekToRatio(ratio);
    }

    size_t VideoPlayer::frameCount() const
    {
        return _video->frameCount();
    }

    void VideoPlayer::setSpeed(double speed)
    {
        _video->setSpeed(speed);
    }

    void VideoPlayer::setVolume(double volume)
    {
        _video->setVolume(volume);
    }

    float VideoPlayer::speed() const
    {
        return _video->speed();
    }

    double VideoPlayer::volume() const
    {
        return _video->volume();
    }

    ml::Events& VideoPlayer::events()
    {
        return _video->events();
    }
}
