#pragma once
#include "./GuiCommand.h"
namespace ml
{
    class AsyncGuiCommand : public GuiCommand
    {
        public:
            AsyncGuiCommand();
            virtual ~AsyncGuiCommand() = default;

            virtual void exec() override;
            virtual void reverse() override;

            virtual bool async()const override{return true;}

            virtual void setExec(const std::function<void(const std::any&)>& f) override{_exec = f;}
    };
}
