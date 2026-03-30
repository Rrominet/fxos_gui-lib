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

    std::shared_ptr<ml::MenuButton> Menu::addCommand(Command* cmd, const std::any& overrideArgs, const std::string& overrideText)
    {
        _cmdsIds.push_back(cmd->id());
        auto _onclick = [cmd, overrideArgs]()
        {
            if (overrideArgs.has_value())
                cmd->exec(overrideArgs);
            else
                cmd->exec();
        };
        auto txt = cmd->name();
        if (overrideText != "")
            txt = overrideText;
        auto btn = this->addButton(txt, _onclick, keybinds::label(cmd->keybind()));
        btn->button()->setHelp(cmd->help());
        return btn;
    }

    void Menu::addSeparator()
    {
        _popover->content()->createSeparator();
    }


    std::shared_ptr<ml::MenuButton> Menu::addCommand(const std::string& cmd_id, const std::any& overrideArgs, const std::string& overrideText)
    {
        return this->addCommand(ml::app()->cmds().command(cmd_id).get(), overrideArgs, overrideText);
    }

    void Menu::show(){ml::app()->focused()->showMenu(_id);}

    json Menu::serialize() const
    {
        json j;
        j["id"] = _id;
        j["name"] = _name;
        j["cmdsIds"] = _cmdsIds;
        return j;
    }

    void Menu::deserialize(const json& j)
    {
        if (j.contains("id"))
            _id = j["id"].get<std::string>();
        if (j.contains("name"))
            _name = j["name"].get<std::string>();
        if (j.contains("cmdsIds"))
        {
            for (auto& i : j["cmdsIds"])
            {
                if (i == "--") //separator
                    _cmdsIds.push_back(i);
                if (!_cmdsIds.contains(i.get<std::string>()))
                    _cmdsIds.push_back(i.get<std::string>());
            }
        }


        for (const auto& i : _cmdsIds)
        {
            if (i == "--")
            {
                this->addSeparator();
                continue;
            }
            try
            {
                auto cmd = ml::app()->cmds().command(i);
                if (cmd)
                    this->addCommand(cmd.get());
            }
            catch(const std::exception& e)
            {
                lg("Can't add the command " << i << " during deserialisation : ");
                lg(e.what());
            }
        }
    }
}
