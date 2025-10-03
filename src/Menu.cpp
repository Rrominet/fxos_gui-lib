#include "./Menu.h"
#include "./MenuButton.h"
#include "./Scrollable.h"
#include "./App.h"
#include "./Button.h"
#include "str.h"
#include "./keybinds.h"
#include "./Window.h"

namespace ml
{
    Menu::Menu(const std::string& id, const std::string& name) : _id(id), _name(name)
    {
        _popover = ml::app()->widgetsFactory().createPopover();
        _popover->addCssClass("menu-popover");
    }

    Menu::~Menu()
    {

    }

    std::shared_ptr<ml::MenuButton> Menu::addButton(const std::string& text, const std::function<void()>& onClick, const std::string& keybind)
    {
        auto _onclick = [this, onClick]()
        {
            if (onClick)
                onClick();
            _popover->hide();
        };
        auto _r = std::make_shared<ml::MenuButton>(_popover->content().get(), text, _onclick, keybind);
        _r->button()->setHAlign(HAlignment::FILL);
        _buttons.push_back(_r);
        return _r;
    }

    void Menu::clear()
    {
        for (auto& m : _buttons)
            m->remove();
        _buttons.clear();
    }


    void Menu::removeButton(const std::string& text)
    {
        for (auto& m : _buttons)
        {
            if (m->text() == text)
            {
                m->remove();
                _buttons.remove(m);
                break;
            }
        }
    }

    std::shared_ptr<ml::MenuButton> Menu::addCommand(Command* cmd)
    {
        auto _onclick = [cmd]()
        {
            cmd->exec();
        };
        return this->addButton(cmd->name(), _onclick, keybinds::label(cmd->keybind()));
    }

    void Menu::addSeparator()
    {
        _popover->content()->createSeparator();
    }


    std::shared_ptr<ml::MenuButton> Menu::addCommand(const std::string& cmd_id)
    {
        return this->addCommand(ml::app()->cmds().command(cmd_id).get());
    }

    void Menu::show(){ml::app()->focused()->showMenu(_id);}
}
