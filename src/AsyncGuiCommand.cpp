#include "./AsyncGuiCommand.h"
#include "./App.h"

namespace ml
{
    AsyncGuiCommand::AsyncGuiCommand(): GuiCommand()
    {
        _before = 0;
        _after = 0;
    }

    void AsyncGuiCommand::exec()
    {
        if (_before)
            _before(_args);
        auto job = [this]
        {
            if (_exec)
                _exec(_args);
        };

        auto onfinished = [this]
        {
            if (_after)
                _after(this->returned());
        };

        ml::app()->execAsync("Running " + this->name(), job, this->name() + " executed.", onfinished);
    }

    void AsyncGuiCommand::reverse()
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
        };

        auto after = [this]{
            if (_after)
                _after(_args);
        };

        ml::app()->execAsync("Reversing " + this->name(), ex, this->name() + " reversed.", after);
    }
}
