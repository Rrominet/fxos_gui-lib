#pragma once
#include "commands/ProcessCommand.h"

namespace ml
{
    //just need to set the command like in ProcessCommand and you're good to go !
    class GuiProcessCommand : public ml::ProcessCommand
    {
        public :
            GuiProcessCommand();
            virtual ~GuiProcessCommand() = default;
            virtual void exec() override;
    };
}
