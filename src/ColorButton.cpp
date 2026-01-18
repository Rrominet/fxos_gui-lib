#include "./ColorButton.h"
#include "./Popover.h"
#include "./Box.hpp"

namespace ml
{
    ColorButton::ColorButton(ml::Box* parent)
    {
        this->draw(parent);
    }

    void ColorButton::draw(ml::Box* parent)
    {
        _clickable = parent->createBox().get();
        _clickable->addCssClass("color-button");
        _clickable->setSize(100, 27); //changed
        _clickable->setHAlign(CENTER);
        _clickable->setCursor("pointer");

        _popover = parent->createPopover().get();
        _popover->hide();

        _colorPicker = _popover->content()->content().createComposedWidget<ColorPicker>(&_popover->content()->content()).get();

        _composed.push(_clickable);
        _composed.push(_popover);

        _clickable->addEventListener(LEFT_UP, [this](EventInfos& e){
                    _popover->show();
                    _popover->setSize(300, 300);
                });

        _colorPicker->events().add("change", [this]{
             _clickable->addCss(_colorPicker->css()); 
        });
        _clickable->addCss(_colorPicker->css());
    }

    std::any ColorButton::valueAsAny()
    {
        return _colorPicker->valueAsAny();
    }

    void ColorButton::setValue(const std::string& value)
    {
        _colorPicker->setValue(value);
    }

    void ColorButton::setValue(double value)
    {
        _colorPicker->setValue(value);
    }

    void ColorButton::setValue(const Color<double>& value)
    {
        _colorPicker->setValue(value);
    }

    void ColorButton::setValue(const json& value)
    {
        _colorPicker->setValue(value);
    }

    void ColorButton::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        if (event == CHANGE)
            _colorPicker->addEventListener(event, callback);
        else
            _clickable->addEventListener(event, callback);
    }
}
