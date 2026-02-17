#include "./ColorPicker.h"
#include "./Box.h"
#include "./Slider.h"

#include "./Box.hpp"

namespace ml
{
    ColorPicker::ColorPicker(ml::Box* parent): _color(0, 0, 0, 1)
    {
        this->draw(parent);
    }

    void ColorPicker::draw(ml::Box* parent)
    {
        _main = parent->createBox().get();
        _main->addCssClass("color-picker");

        _colorBox = _main->createBox().get();
        _colorBox->addCssClass("color-box");
        _colorBox->setHExpand();
        _colorBox->setVExpand();
        _colorBox->setSize(-1, 50);
        _main->createSeparator();
        _rgbaBox = _main->createBox().get();
        _rgbaBox->addCssClass("rgba-box");

        _r = _main->createSlider().get();
        _g = _main->createSlider().get();
        _b = _main->createSlider().get();
        _a = _main->createSlider().get();

        _r->setRange(0, 255);
        _r->setHelp("Red");
        _g->setRange(0, 255);
        _g->setHelp("Green");
        _b->setRange(0, 255);
        _b->setHelp("Blue");
        _a->setRange(0, 1);
        _a->setHelp("Alpha");

        _a->setValue(255);

        _r->addEventListener(CHANGE, [this](EventInfos&){_onSlidersChange();});
        _g->addEventListener(CHANGE, [this](EventInfos&){_onSlidersChange();});
        _b->addEventListener(CHANGE, [this](EventInfos&){_onSlidersChange();});
        _a->addEventListener(CHANGE, [this](EventInfos&){_onSlidersChange();});

        _composed.push(_main);
        _onSlidersChange();
    }

    void ColorPicker::_onSlidersChange()
    {
        _colorBox->addCss(this->css());
        _color.setRGBA(_r->value()/255.0, _g->value()/255.0, _b->value()/255.0, _a->value());
        _events.emit("change", _color);
    }

    void ColorPicker::_updateGuiFromColor()
    {
        _r->setValue(_color.r()*255.0); 
        _g->setValue(_color.g()*255.0); 
        _b->setValue(_color.b()*255.0); 
        _a->setValue(_color.a());
    }

    std::string ColorPicker::css()
    {
        std::string css = "background-color: rgba(" + std::to_string(_r->value()) + ", " + std::to_string(_g->value()) + ", " + std::to_string(_b->value()) + ", " + std::to_string(_a->value()) + ");";
        css = "* { " + css + " }";
        return css;
    }

    std::any ColorPicker::valueAsAny()
    {
        return std::any(_color); 
    }

    void ColorPicker::setValue(const std::string& value)
    {
        try
        {
            auto data = json::parse(value) ;
            _color.deserialize(data);
            _updateGuiFromColor();
        }
        catch(const std::exception& e)
        {
            lg(e.what());
        }
    }

    void ColorPicker::setValue(double value)
    {
        _color.set(value, value, value, 1) ;
        _updateGuiFromColor();
    }

    void ColorPicker::setValue(const Color<double>& value)
    {
        _color = value; 
        _updateGuiFromColor();
    }

    void ColorPicker::setValue(const json& value)
    {
        _color.deserialize(value); 
        _updateGuiFromColor();
    }

    void ColorPicker::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        if(event == CHANGE)
        {
            _r->addEventListener(event, callback);
            _g->addEventListener(event, callback);
            _b->addEventListener(event, callback);
            _a->addEventListener(event, callback);
        }
        else 
            _main->addEventListener(event, callback);
    }
}
