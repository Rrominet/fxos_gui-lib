#include "./CommandButton.h"
#include "commands/Command.h"
#include "./App.h"
#include "./Box.h"
#include "./Label.h"

#include "./Box.hpp"

namespace ml
{
    CommandButton::CommandButton(ml::Box* box,const std::string& cmdId)
    {
        __construct(box, ml::app()->cmds().command(cmdId).get());
    }

    CommandButton::CommandButton(ml::Box* box,ml::Command* cmd)
    {
        __construct(box,cmd);
    }

    void CommandButton::__construct(ml::Box* box, ml::Command* cmd)
    {
        _futureParent = box;
        _cmd = cmd;
    }

    CommandButton::~CommandButton()
    {
        this->remove();
        lg("CommandButton::~CommandButton");
    }

    void CommandButton::draw()
    {
        if (_drawn)
            return;

        _button = _futureParent->createBox();
        _button->addCssClass("command-button");
        _button->setOrient(ml::Orient::HORIZONTAL);
        _label = _button->createLabel(_cmd->name());
        _label->setHAlign(ml::LEFT);

        _right = _button->createLabel(str::capitalize(_cmd->keybind()));
        _right->setHAlign(ml::RIGHT);
        _right->setHExpand();

        if (_cmd->keybind().empty())
        {
            _right->setText(_cmd->help());
        }
        else 
        {
            _button->setHelp(_cmd->help());
        }

        _label->addCssClass("command-button-label");
        _right->addCssClass("command-button-right");

        this->setEvents();
        _button->setCursor("pointer");

        _drawn = true;
    }

    void CommandButton::setEvents()
    {
        auto lclick = [this](EventInfos& event)
        {
            if (_cmd)
            {
                _cmd->exec();
                _events.emit("executed");
            }
        };
        
        auto rclick = [this](EventInfos& event)
        {
            _events.emit("context");
        };
        
        _button->addEventListener(Event::LEFT_UP, lclick);
        _button->addEventListener(Event::RIGHT_UP, rclick);
    }

    void CommandButton::show()
    {
        if (!_drawn)	
            return;
        _button->show();
    }

    void CommandButton::hide()
    {
        if (!_drawn)	
            return;
        _button->show();
    }

    void CommandButton::remove()
    {
        if (!_drawn)	
            return;
        _button->remove();
    }

    void CommandButton::setCommand(ml::Command* cmd)
    {
        _cmd = cmd;
        if (!_drawn)	
            return;

        // update all gui and event stuff...
        // just recall draw() maybe ?
    }

}
