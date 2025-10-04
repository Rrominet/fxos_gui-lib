#include "./Commander.h"
#include "./Box.h"
#include "./Entry.h"
#include "./Scrollable.h"
#include "./CommandButton.h"

#include "commands/CommandsManager.h"
#include "./App.h"
#include "./Window.h"

#include "./App.hpp"
#include "./Box.hpp"
#include "./Scrollable.hpp"

namespace ml
{
    Commander::Commander(Box* parent)
    {
        _box = parent->createBox();
        _box->addCssClass("commander-container");
        _composed.push_back(_box.get());

        _search = _box->createEntry();
        _search->addCssClass("commander-search");

        _list = _box->createScrollable();
        _list->addCssClass("commander-list");

        _search->addEventListener(CHANGE, std::bind(&Commander::_onSearchChange, this));
        _search->addEventListener(VALID, std::bind(&Commander::_onSearchValid, this));
    }

    Commander::~Commander()
    {}

    void Commander::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        _search->addEventListener(event, callback);
    }

    void Commander::setValue(const std::string& value)
    {
        _search->setValue(value);
    }

    void Commander::setValue(double value)
    {
        _search->setValue(value);
    }

    std::any Commander::valueAsAny()
    {
        return std::any(_search->value());
    }

    void Commander::_onSearchChange()
    {
        std::string searched = _search->value();
        _sortCommands(searched);
        _buttons.clear();

        int max=30;
        lg("commands size " << _commands.size());
        for (int i=0; i<_commands.size(); i++)
        {
            lg("i " << i << " max " << max);
            if (i>=max)
                break;
            auto cmd = _commands[i];
            auto button = std::make_unique<CommandButton>(&_list->content(), cmd);
            button->events().add("context", [this, cmd](){ _events.emit("context", cmd); });
            button->events().add("executed", [this, cmd](){ _events.emit("valid", cmd); });
            button->draw();
            _buttons.push_back(std::move(button));
        }

        _events.emit("changed");
    }

    void Commander::_onSearchValid()
    {
        if(_commands.size() > 0)
        {
            if (!_doNothing)
                _commands[0]->exec();
            _events.emit("valid", _commands[0]);
        }

    }

    double Commander::_score(const std::string& searched, ml::Command* cmd)
    {
        for (auto& alias : cmd->aliases())
        {
            if (alias == searched)
                return 100;
            else if (str::lower(alias) == str::lower(searched))
                return 50;
            else if (str::contains(str::lower(alias), str::lower(searched)))
                return 25;
            else if (str::contains(str::lower(alias), str::clean(searched, true)))
                return 15;
        }
        
        if (str::contains(str::lower(cmd->name()), str::lower(searched)))
            return 10;
        else if (str::contains(str::lower(cmd->name()), str::clean(searched, true)))
            return 5;

        if (str::contains(str::lower(cmd->help()), str::lower(searched)))
            return 2;
        else if (str::contains(str::lower(cmd->help()), str::clean(searched, true)))
            return 1;

        return 0;
    }

    void Commander::_sortCommands(const std::string& searched)
    {
        auto sort = [this, &searched](ml::Command* a, ml::Command* b) -> bool
        {
            return this->_score(searched, a) > this->_score(searched, b);
        };

        std::sort(_commands.begin(), _commands.end(), sort);
    }

    void Commander::addCommand(ml::Command* cmd)
    {
        _commands.push_back(cmd);
    }

    void Commander::addCommand(const std::string& id,ml::CommandsManager* mgr)
    {
        if (!mgr)
            mgr = &ml::app()->cmds();
        try
        {
            _commands.push_back(mgr->command(id).get()); 
        }
        catch(const std::exception& e)
        {
            lg("Command not found : " << id << " -- ignored.");
            lg(e.what());
        }
    }

    void Commander::addAllCommands(ml::CommandsManager* mgr)
    {
        for (auto& cmd : mgr->commands()) 
            _commands.push_back(cmd.second.get());
    }

    void Commander::addAllCommands(ml::Window* win)
    {
        for (auto& cmd : win->cmds().commands()) 
            _commands.push_back(cmd.second.get());
    }

    void Commander::addAllCommands(ml::App* app)
    {
        for (auto& cmd : app->cmds().commands()) 
            _commands.push_back(cmd.second.get());
    }

    void Commander::removeCommand(ml::Command* cmd)
    {
        _commands.remove(cmd);
        for (auto& button : _buttons)
        {
            if (button->cmd() == cmd)
            {
                _buttons.remove(button);
                break;
            }
        }
    }

    void Commander::removeCommands(const std::string& id)
    {
        ml::Vec<ml::Command*> removed;
        int i=0;
        while (i<_commands.size())
        {
            if (_commands[i]->id() == id)
            {
                _commands.removeByIndex(i);
                removed.push_back(_commands[i]);
            }
            else
                i++;
        }

        for (auto& cmd : removed)
        {
            int i=0;
            while (i<_buttons.size())
            {
                if (_buttons[i]->cmd() == cmd)
                    _buttons.removeByIndex(i);
                else
                    i++;
            }
        }
    }

    void Commander::removeCommand(const std::string& id,ml::CommandsManager* mgr)
    {
        try
        {
            auto cmd = mgr->command(id);
            if (cmd)
                this->removeCommand(cmd.get());
        }
        catch(const std::exception& e)
        {
            lg(e.what());
            lg("id not found : " << id << " in the command manager given. Ignored.");
        }
    }

    void Commander::clear()
    {
        _buttons.clear();
        _commands.clear();
    }
}
