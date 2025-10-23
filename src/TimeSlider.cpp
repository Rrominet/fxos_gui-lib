#include "./TimeSlider.h"
#include "./AbsoluteBox.h"
#include "./Box.h"

#include "./AbsoluteBox.hpp"
#include "./Box.hpp"

namespace ml
{
    TimeSlider::TimeSlider(ml::Box* parent, bool init)
    {
        if (!init)
            return;
        _init(parent);
    }

    TimeSlider::TimeSlider(ml::Box* parent,double min,double max,double current, bool init)
    {
        if (init)
            _init(parent);
        _min = min;
        _max = max;
        _current = current;
        if (init)
            _updateGui();
    }

    void TimeSlider::_init(ml::Box* parent)
    {
        lg("TimeSlider::_init");
        _container = parent->createAbsoluteBox().get();
        _composed.push(_container);

        _container->addCssClass("time-slider");
        _container->setCursor("pointer");

        _1 = _container->createBox().get();
        _1->addCssClass("before");
        _2 = _container->createBox().get();
        _2->addCssClass("after");

        _container->setHExpand();
        _container->setVExpandSet();

        _setEvents();

        this->setHeight(_height);
    }

    void TimeSlider::setMin(double val, bool sendEvent)
    {
        _min = val;
        if (sendEvent)
            _events.emit("min-changed", _min);
        _updateGui();
    }

    void TimeSlider::setMax(double val, bool sendEvent)
    {
        _max = val;
        if (sendEvent)
            _events.emit("max-changed", _max);
        _updateGui();
    }

    void TimeSlider::setCurrent(double val, bool sendEvent)
    {
        _current = val;
        if (sendEvent)
            _events.emit("current-changed", _current);
        _updateGui();
    }

    void TimeSlider::_setEvents()
    {
        _container->addEventListener(RESIZE, [this](EventInfos& e){_updateGui();});
        _container->addEventListener(LEFT_DOWN, [this](EventInfos& e){_onMouseDown(e);});
        _container->addEventListener(LEFT_UP, [this](EventInfos& e){_onMouseUp(e);});
        _container->addEventListener(MOUSE_MOVE, [this](EventInfos& e){_onMouseMove(e);});
    }

    void TimeSlider::setHeight(float height)
    {
        _height = height;
        _container->setHeight(height);
        _updateGui();
    }

    void TimeSlider::_onMouseDown(EventInfos& e)
    {
        _dragging = true;
        _onMouseMove(e);
    }

    void TimeSlider::_onMouseUp(EventInfos& e)
    {
        _dragging = false;
    }

    void TimeSlider::_onMouseMove(EventInfos& e)
    {
        if (!_dragging)
            return;
        double ratio = e.x/_container->width();
        this->setCurrent(_min + (_max - _min)*ratio);
    }

    void TimeSlider::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        _container->addEventListener(event, callback);
    }

    void TimeSlider::setHAlign(HAlignment align)
    {
        _container->setHAlign(align);
    }

    void TimeSlider::setVAlign(VAlignment align)
    {
        _container->setVAlign(align);
    }

    void TimeSlider::setHExpand(bool value)
    {
        _container->setHExpand(value);
    }

    void TimeSlider::setVExpand(bool value)
    {
        _container->setVExpand(value);
    }

    void TimeSlider::_updateGui()
    {
        double ratio = (_current - _min)/(_max - _min); 
        _1->setSize(ratio*_container->width(), _height);
        _2->setSize((1-ratio)*_container->width(), _height);
        _2->setLeftMargin(ratio*_container->width());
    }
}
