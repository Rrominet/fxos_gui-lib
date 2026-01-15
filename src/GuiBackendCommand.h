#pragma once
#include "GuiCommand.h"
#include "thread.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Process;
namespace ml
{
    struct GuiCallback
    {
        std::function<void(const json& response)> cb;
        bool onetime = false;
    };

    class GuiBackendCommand : public GuiCommand    
    {
        public :
            GuiBackendCommand();
            virtual ~GuiBackendCommand() = default;

            void init();
            virtual bool check() override;
            virtual void execJson(const json& args){this->setJsonArgs(args); this->exec();}

            // need to be setted before calling exec (often when clicking on a button.)
            void setProcessCommand(Process* process, const std::string &function, const json& args, const std::function<void(const json& response)>& cb=0, bool onetime=false);
            void setProcessCommand(Process* process, const std::string &function, const std::function<json()>& getjsonArgs, const std::function<void(const json& response)>& cb=0, bool onetime=false);
            void addCallback(const std::function<void(const json& response)>& cb, bool onetime = false);

            //need to be executed on the mainthread !
            void execCallbacks(const json& response);
           
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
            std::function<json()> _getjsonArgs;

            th::Safe<ml::Vec<GuiCallback>> _callbacks;

            bool _waiting = false;
            bool _useDefaultErrorWindow = true;

        public : 
#include "./GuiBackendCommand_gen.h"
    };
}
