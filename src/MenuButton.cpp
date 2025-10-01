#include "./MenuButton.h"
#include "./Scrollable.h"
#include "./Label.h"
#include "enums.h"

namespace ml
{
    MenuButton::MenuButton(ml::Scrollable* box, const std::string& text, const std::function<void()>& onClick, const std::string& keybind)
    {
        _button = box->createBox();
        __construct(text, onClick, keybind);
    }

    MenuButton::MenuButton(ml::Box* box, const std::string& text, const std::function<void()>& onClick, const std::string& keybind)
    {
        _button = box->createBox();
        __construct(text, onClick, keybind);
    }

    void MenuButton::__construct(const std::string& text, const std::function<void()>& onClick, const std::string& keybind)
    {
        _button->addCssClass("menu-button");
        _button->setOrient(ml::Orient::HORIZONTAL);
        _label = _button->createLabel(text);
        _keybind = _button->createLabel(keybind);
        if (keybind.empty())
            _keybind->hide();
        _keybind->setHExpand(); // equivalent to width : 100% in html/css

        _label->setHAlign(ml::LEFT);
        _keybind->setHAlign(ml::RIGHT);

        _label->addCssClass("menu-button-label");
        _keybind->addCssClass("menu-button-keybind");

        _onClick = onClick;

        auto f = [this](EventInfos& event)
        {
            if (_onClick)
                _onClick();  
        };

        _button->addEventListener(Event::MOUSE_UP, f);
        _label->addEventListener(Event::MOUSE_UP, f);
        _keybind->addEventListener(Event::MOUSE_UP, f);
    }

    MenuButton::~MenuButton()
    {

    }

    std::string MenuButton::text() const
    {
        return _label->text();
    }

    void MenuButton::setText(const std::string& text)
    {
        _label->setText(text);
    }

    std::string MenuButton::keybind() const
    {
        return _keybind->text();	
    }

    void MenuButton::setKeybind(const std::string& text)
    {
        _keybind->setText(text);	
        if (text.empty())
            _keybind->hide();
        else 
            _keybind->show();
    }

    void MenuButton::remove()
    {
        _button->remove();
    }

    std::string MenuButton::asText() const
    {
        return _label->text() + " " + _keybind->text();
    }
}
