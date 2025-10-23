#pragma once
#include "./TimeSlider.h"

//FIXME : Create a custom drawable and not a list of box, it's a nightmare to manage.
namespace ml
{
    class TimeSliderInOut : public TimeSlider
    {
        public : 
            TimeSliderInOut(ml::Box* parent);
            TimeSliderInOut(ml::Box* parent, double min, double max, double current=-1, double start=0, double end=-1);

            virtual ~TimeSliderInOut() = default;

            void setStart(double val, bool sendEvent=true);
            void setEnd(double val, bool sendEvent=true);

            double start()const {return _start;}
            double end()const {return _end;}

        protected : 
            double _start = 0;
            double _end = -1;

            ml::Box* _cursor = nullptr;
            ml::Box* _3 = nullptr;

            virtual void _init(ml::Box* parent) override;
            void _setEvents();

            virtual void _updateGui() override;

            void _onKeyDown(EventInfos& e);
    };
}
