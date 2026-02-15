#include "./GuiCommand.h"
#include "./ConfirmDialog.h"
#include "./App.h"

namespace ml
{
    GuiCommand::GuiCommand()
    {
        _before = [](const std::any&) 
        {
            lg("before : setting the cursor to wait.");
            ml::app()->setCursor("wait");
        };

        _after = [](const std::any&) 
        {
            ml::app()->setCursor("default");
            lg("after : setting the cursor to default.");
        };
    }

    void GuiCommand::exec()
    {
        if (!this->check())
        {
            app()->error("Error in the command : " + this->name() + "\nMore infos : " + _error);
            return;
        }
        if (_before)
            _before(_args);
        auto ex = [this]{
            if (_exec)
                _exec(_args);
            if (_after)
                _after(_args);
            for (const auto&f : _toQueue)
                app()->queue(f);
        };
        app()->queue(ex);
    }

    void GuiCommand::reverse()
    {
        if (!this->checkReverse())
        {
            app()->error("Error in the command during undo : " + this->name() + "\nMore infos : " + _error);
            return;
        }

        if (_before)
            _before(_args);

        auto ex = [this]{
            if (_reverse)
                _reverse(_args);
            if (_after)
                _after(_args);
        };

        app()->queue(ex);
    }

    void GuiCommand::setExec(const std::function<void(const std::any&)>& f)
    {
        lg("setExec : " + this->name());
        if (!_confirm)
        {
            _exec = f;
            if (!_exec)
                return;
        }

        else 
        {
            _before = 0;
            _after = 0;
            _exec = [this, f](const std::any& args)
            {
                auto confdg = app()->confirm();
                confdg->events().add("ok", [f, args]{
                        app()->setCursor("wait");
                        app()->setTimeout([f, args]{f(args); app()->setCursor("default");}, 1);
                    });
            };
        }

        _execSetted = true;
    }

    void GuiCommand::setConfirm(bool confirm)
    {
        if (_execSetted)
        {
            lg("You can't set confirm after the exec function is setted.");
            lg("For command : " + this->name());
            assert(false);
        }
        _confirm = confirm;	
    }

    json GuiCommand::serialize() const
    {
        json _r = Command::serialize();
        _r["type"] = "guiCommand";
        _r["confirm"] = _confirm;
        return _r;
    }

    void GuiCommand::deserialize(const json& j)
    {
        Command::deserialize(j);
        if (j.contains("confirm"))
            _confirm = j["confirm"];
    }
}

