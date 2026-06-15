#include "./MenuButton.h"
#include "./Scrollable.h"
#include "./Label.h"
#include "enums.h"

namespace ml
{
    MenuButton::MenuButton(ml::Scrollable* box, const std::string& text, const std::function<void()>& onClick, const std::string& keybind)
    {
        lg("a");
        _button = box->createBox();
        lg("a");
        __construct(text, onClick, keybind);
        lg("a");
    }

    MenuButton::MenuButton(ml::Box* box, const std::string& text, const std::function<void()>& onClick, const std::string& keybind)
    {
        lg("a");
        _button = box->createBox();
        lg("a");
        __construct(text, onClick, keybind);
        lg("a");
    }

    void MenuButton::__construct(const std::string& text, const std::function<void()>& onClick, const std::string& keybind)
    {
        lg("a");
        _button->addCssClass("menu-button");
        lg("a");
        _button->setOrient(ml::Orient::HORIZONTAL);
        lg("a");
        _label = _button->createLabel(text);
        lg("a");
        _keybind = _button->createLabel(keybind);
        lg("a");
        if (keybind.empty())
            _keybind->hide();
        lg("a");
        _keybind->setHExpand(); // equivalent to width : 100% in html/css
        lg("a");

        _label->setHAlign(ml::LEFT);
        lg("a");
        _keybind->setHAlign(ml::RIGHT);
        lg("a");

        _label->addCssClass("menu-button-label");
        lg("a");
        _keybind->addCssClass("menu-button-keybind");
        lg("a");

        _onClick = onClick;
        lg("a");

        auto f = [this](EventInfos& event)
        {
            if (_onClick)
                _onClick();  
        };

        lg("a");
        _button->addEventListener(Event::MOUSE_UP, f);
        lg("a");
        _label->addEventListener(Event::MOUSE_UP, f);
        lg("a");
        _keybind->addEventListener(Event::MOUSE_UP, f);
        lg("a");
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
