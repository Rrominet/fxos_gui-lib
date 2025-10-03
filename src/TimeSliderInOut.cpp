#include "./TimeSliderInOut.h"
#include "./Box.h"

#include "./Box.hpp"

namespace ml
{
    TimeSliderInOut::TimeSliderInOut(ml::Box* parent) : TimeSlider(parent, false)
    {
        _init(parent);
    }

    TimeSliderInOut::TimeSliderInOut(ml::Box* parent,double min,double max,double current,double start,double end) : TimeSlider(parent,min,max,current, false)
    {
        _start = start;

        if (end == -1)
            _end = _max;
        else 
            _end = end;

        if (current == -1)
            current = _min;

        _current = current;

        _init(parent);
        _updateGui();
    }

    void TimeSliderInOut::setStart(double val,bool sendEvent)
    {
        _start = val; 
        if (_end < _start)
            _end = _start + 1;
        if (sendEvent)
            _events.emit("start-changed", _start);
        _updateGui();
    }

    void TimeSliderInOut::setEnd(double val,bool sendEvent)
    {
        _end = val; 
        if (_start > _end)
            _start = _end - 1;
        if (sendEvent)
            _events.emit("end-changed", _end);
        _updateGui();
    }

    void TimeSliderInOut::_init(ml::Box* parent)
    {
        lg("TimeSliderInOut::_init");
        _container = parent->createAbsoluteBox().get();
        _composed.push(_container);

        _container->addCssClass("time-slider-in-out");
        _container->setCursor("pointer");

        _1 = _container->createBox().get();
        _1->addCssClass("before");
        _2 = _container->createBox().get();
        _2->addCssClass("range");

        _3 = _container->createBox().get();
        _3->addCssClass("after");

        _cursor = _container->createBox().get();
        _cursor->addCssClass("cursor");
        _cursor->setSize(2, _height);

        _container->setHExpand();
        _container->setVExpandSet();

        TimeSlider::_setEvents();
        this->_setEvents();

        this->setHeight(_height);
    }

    void TimeSliderInOut::_updateGui()
    {
        if (!_cursor || !_3)
            return;
        double cursor_ratio = (_current - _min)/(_max - _min); 
        double start_ratio = (_start - _min)/(_max - _min);
        double end_ratio = (_end - _min)/(_max - _min);

        auto w = _container->width();

        _1->setSize(start_ratio*w, _height);

        _2->setLeftMargin(start_ratio*w);
        _2->setSize((end_ratio - start_ratio)*w, _height);

        _3->setSize((1-end_ratio)*w, _height);
        _3->setLeftMargin(end_ratio*w);

        _cursor->setLeftMargin(cursor_ratio*w);
    }

    void TimeSliderInOut::_setEvents()
    {
    }
}
