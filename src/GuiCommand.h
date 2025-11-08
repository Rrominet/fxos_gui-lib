#pragma once
#include "commands/Command.h"
#include "vec.h"

namespace ml
{
    class Button;
    class GuiCommand : public Command    
    {
        public :
            GuiCommand();
            virtual ~GuiCommand() = default;

            virtual void exec() override;
            virtual void reverse() override;

            virtual void setExec(const std::function<void(const std::any&)>& f) override;

            void setConfirm(bool confirm);

            //alias
            void setNeedConfirm(bool confirm){this->setConfirm(confirm);}

            virtual bool waiting()const{return false;}

            virtual json serialize() const override;
            virtual void deserialize(const json& j) override;

            virtual bool async()const {return false;}

        protected : 
            std::function<void(const std::any&)> _before; //bp cgs
            std::function<void(const std::any&)> _after; //bp cgs

            // if confirm is true, it will ask the user to confirm the command before executing it.
            bool _confirm = false; //bp cg
            bool _execSetted = false;

            ml::Vec<std::shared_ptr<ml::Button>> _buttons; //bp cg

        public : 
#include "./GuiCommand_gen.h"
    };
}
