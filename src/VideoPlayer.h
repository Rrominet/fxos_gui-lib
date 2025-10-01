#pragma once
#include "./ComposedWidget.h"
#include "Events.h"

namespace ml
{
    class Video;
    class Box;
    class TimeSliderInOut;
    class Label;

    class VideoPlayer : public ComposedWidget
    {
        public : 
            VideoPlayer(ml::Box* parent);
            VideoPlayer(ml::Box* parent, const std::string& filepath);
            virtual ~VideoPlayer() = default;

            virtual void addEventListener(Event event, const std::function<void(EventInfos&)>& callback);

            void setPath(const std::string& filepath);
            std::string path() const;

            virtual void setHAlign(HAlignment align);
            virtual void setVAlign(VAlignment align);

            virtual void setHExpand(bool value=true);
            virtual void setVExpand(bool value=true);

            void play();
            void pause();
            void toggle();
            bool playing()const;
            long currentFrame() const;
            double duration() const;
            double currentTime() const;
            void nextFrame();
            void prevFrame();
            void seekToFrame(long frame);
            void seek(double time);
            void seekToRatio(double ratio);
            size_t frameCount() const;

            void setSpeed(double speed);
            void setVolume(double volume);

            float speed() const;
            double volume() const;

            ml::Events& events();
            TimeSliderInOut* slider() { return _slider; }

        protected : 
            Video* _video = nullptr;
            TimeSliderInOut* _slider = nullptr;

            ml::Box* _container = nullptr;
            ml::Box* _sliderContainer = nullptr;
            ml::Label* _start = nullptr;
            ml::Label* _current = nullptr;
            ml::Label* _end = nullptr;

            void _setEvents();
            void _init(ml::Box* parent);
    };
}
