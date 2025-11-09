#pragma once
#include "GuiCommand.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Process;
namespace ml
{
    class GuiBackendCommand : public GuiCommand    
    {
        public :
            GuiBackendCommand();
            virtual ~GuiBackendCommand() = default;

            virtual bool check() override;

            // need to be setted before calling exec (often when clicking on a button.)
            void setProcessCommand(Process* process, const std::string &function, const json& args, const std::function<void(const json& response)>& cb=0);
            void setCallback(const std::function<void(const json& response)>& cb){_userCb = cb;}
           
            virtual void setExec(const std::function<void(const std::any&)>& f) override;

            virtual bool waiting()const override{return _waiting;}

            virtual json serialize() const override;
            virtual void deserialize(const json& j) override;

            void onError(const std::string& error);

        protected : 
            Process* _process = nullptr;
            std::string _function;
            json _jsonArgs; //bp cgs
            std::function<void(const json& response)> _cb;
            std::function<void(const json& response)> _userCb=0;
            bool _waiting = false;

        public : 
#include "./GuiBackendCommand_gen.h"
    };
}
