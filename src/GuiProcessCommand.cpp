#include "./GuiProcessCommand.h"
#include "./ConfirmDialog.h"
#include "./App.h"

namespace ml
{
    GuiProcessCommand::GuiProcessCommand(): ProcessCommand(){}

    void GuiProcessCommand::exec()
    {
        auto error_th = [this](const std::string& msg)
        {
            ml::app()->error("Error in the command : " + this->name() + "\nMore infos : " + msg);
        };
        auto ex = [this, error_th]
        {
            try
            {
                ProcessCommand::exec();
                if (_exitCode != 0)
                    ml::app()->error("Error in the command : " + this->name() + "\nExit code : " + std::to_string(_exitCode));
            }
            catch(const std::exception& e)
            {
                lg(e.what());
                ml::app()->queue([error_th, e] {error_th(e.what());});
                return;
            }
        };
        if (_detached)
            ex();
        else 
            ml::app()->execAsync("Running " + this->name(), ex, this->name() + " executed.");
    }
}
