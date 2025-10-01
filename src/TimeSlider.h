#pragma once
#include "./ComposedWidget.h"
#include "Events.h"

//FIXME : Create a custom drawable and not a list of box, it's a nightmare to manage.

namespace ml
{
    class AbsoluteBox;
    class Box;
    class TimeSlider : public ComposedWidget
    {
        public : 
            TimeSlider(ml::Box* parent, bool init=true);
            TimeSlider(ml::Box* parent, double min, double max, double current=-1, bool init=true);
            virtual ~TimeSlider() = default;

            virtual void addEventListener(Event event, const std::function<void(EventInfos&)>& callback) override;

            virtual void setHAlign(HAlignment align) override;
            virtual void setVAlign(VAlignment align) override;

            virtual void setHExpand(bool value=true) override;
            virtual void setVExpand(bool value=true) override;

            virtual void setHeight(float height);

            void setMin(double val, bool sendEvent=true);
            void setMax(double val, bool sendEvent=true);
            void setCurrent(double val, bool sendEvent=true);

            ml::Events& events() { return _events; }

        protected : 
            ml::Events _events;
            ml::AbsoluteBox* _container;
            ml::Box* _1;
            ml::Box* _2;

            double _min = 0; //bp cg
            double _max = 100; //bp cg
            double _current = 0; //bp cg

            int _height = 5; //bp cg
            bool _dragging = false;

            virtual void _init(ml::Box* parent);
            void _setEvents();

            void _onMouseDown(EventInfos& e);
            void _onMouseUp(EventInfos& e);
            void _onMouseMove(EventInfos& e);

            virtual void _updateGui();

        public : 
#include "./TimeSlider_gen.h"
    };
}
