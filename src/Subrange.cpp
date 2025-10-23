#include "./Subrange.h"
#include "./Box.h"

#include "./Box.hpp"
#include "enums.h"
#include "./mlMath.h"

namespace ml
{
    Subrange::Subrange(Box* parent)
    {
        _init(parent);
        _updateGui();
    }

    Subrange::Subrange(Box* parent,double min,double max,double start,double end)
    {
        _init(parent);
        this->setMin(min);
        this->setMax(max);
        this->setStart(start);
        this->setEnd(end);
    }

    void Subrange::_init(Box* parent)
    {
        _container = parent->createBox().get();
        _composed.push(_container);

        _container->addCssClass("subrange");

        _container->setOrient(Orient::HORIZONTAL);
        _container->setCursor("pointer");

        _1 = _container->createBox().get();
        _1->addCssClass("before");
        _2 = _container->createBox().get();
        _2->addCssClass("range");
        _3 = _container->createBox().get();
        _3->addCssClass("after");

        _container->setHExpand();

        _1->setVExpand();
        _2->setVExpand();
        _3->setVExpand();

        _container->setHeight(5);

        _setEvents();
    }

    void Subrange::_setInputTypeFromRatio(double ratio)
    {
        auto s = _start_ratio();
        auto e = _end_ratio();
        if (ratio <= s)
        {
            _inputType = InputType::START;
            return;
        }
        else if (ratio >= e)
        {
            _inputType = InputType::END;
            return;
        }

        auto dist_s = ratio - s;
        auto dist_e = e - ratio;

        if (dist_s < dist_e)
            _inputType = InputType::START;
        else 
            _inputType = InputType::END;
    }

    void Subrange::_onMouseDown(EventInfos& e)
    {
        _dragging = true;
        float r = e.x/_container->width();
        _setInputTypeFromRatio(r);
        _onMouseMove(e);
    }

    void Subrange::_onMouseUp(EventInfos& e)
    {
        _dragging = false;
    }

    void Subrange::_onMouseMove(EventInfos& e)
    {
        if (!_dragging)
            return;

        double ratio = e.x/_container->width();
        if (_inputType == InputType::START)
            this->setStart(_min + (_max - _min)*ratio);
        else if (_inputType == InputType::END)
            this->setEnd(_min + (_max - _min)*ratio);
    }

    void Subrange::_setEvents()
    {
        _container->addEventListener(RESIZE, [this](EventInfos& e){_updateGui();});
        _container->addEventListener(LEFT_DOWN, [this](EventInfos& e){_onMouseDown(e);});
        _container->addEventListener(LEFT_UP, [this](EventInfos& e){_onMouseUp(e);});
        _container->addEventListener(MOUSE_MOVE, [this](EventInfos& e){_onMouseMove(e);});
    }

    void Subrange::setHeight(float height)
    {
        _container->setHeight(height);	
    }

    void Subrange::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        _container->addEventListener(event, callback);
    }

    void Subrange::setMin(double val)
    {
        _min = val;
        _updateGui();

        for (auto cb : _onMinChange)
            cb(_min);
    }

    void Subrange::setMax(double val)
    {
        _max = val;
        _updateGui();
        for (auto cb : _onMaxChange)
            cb(_max);
    }

    void Subrange::setStart(double val)
    {
        if (val < _min)
            val = _min;
        if (val >= _end)
            val = _end;
        _start = val;
        _updateGui();
        for (auto cb : _onStartChange)
            cb(_start);
    }

    void Subrange::setEnd(double val)
    {
        if (val > _max)
            val = _max;
        if (val <= _start)
            val = _start;
        _end = val;
        _updateGui();
        for (auto cb : _onEndChange)
            cb(_end);
    }

    float Subrange::_pixelFromRatio(double ratio)
    {
        float w = _container->width();
        lg("container width " << w);
        return w * ratio;
    }


    float Subrange::_start_ratio() const
    {
        return 	(_start - _min) / (_max - _min);
    }

    float Subrange::_end_ratio() const
    {
        return (_end - _min) / (_max - _min);	
    }

    void Subrange::_updateGui()
    {
        float start_ratio = _start_ratio();
        float end_ratio = _end_ratio();

        lg("start_ratio " << start_ratio << " " << _pixelFromRatio(start_ratio));
        lg("end_ratio " << end_ratio << " " << _pixelFromRatio(end_ratio));

        _1->setWidth(_pixelFromRatio(start_ratio));
        _2->setWidth(_pixelFromRatio(end_ratio - start_ratio));
        _3->setWidth(_pixelFromRatio(1 - end_ratio));
    }
}
