#include "./GuiBackendCommand.h"
#include "GuiCommand.h"
#include "files.2/files.h"
#include "ipc.h"
#include "App.h"
#include "mlprocess.h"
#include "./Button.h"
#include <mutex>

namespace ml
{
    GuiBackendCommand::GuiBackendCommand() : GuiCommand()
    {
        this->init();
    }
    
    void GuiBackendCommand::init()
    {
        _cb = [this](const json& res)
        {
            auto mth = [this, res]
            {
                if (res.contains("success") && !res["success"])
                {
                    if (_useDefaultErrorWindow)
                        this->onError(res["error"]);
                }
                else 
                    this->execCallbacks(res);

                _waiting = false;
                app()->main()->setInfosFromCommand(this);
                for (auto& b : _buttons)
                    b->stopLoading();
            };
            app()->queue(mth);
            lg("process backend response received : " << res.dump(4));
        };
    }

    bool GuiBackendCommand::check()
    {
        if (!_process) 
        {
            _error = "GuiBackendCommand::setProcessCommand() was not called before exec() on the GuiBackendCommand : " + this->name();
            return false;
        }

        return Command::check();
    }

    void GuiBackendCommand::setProcessCommand(Process* process, const std::string &function, const json& args, const std::function<void(const json& response)>& cb, bool onetime)
    {
        _process = process;
        _jsonArgs = args;
        _function = function;

        if (cb)
            this->addCallback(cb, onetime);

        auto exec = [this](const std::any&)
        {
            for (auto& b : _buttons)
                b->mkLoading();
            try
            {
                ipc::call(_process, _function, _jsonArgs, _cb);
                _waiting = true; //changed
            }
            catch(const std::exception& e)
            {
                this->onError(_S(e.what()));
            }
            lg("process backend called : " << _function);
            lg("with these args : " << _jsonArgs.dump(4));
            app()->main()->setInfosFromCommand(this);
        };

        GuiCommand::setExec(exec);
    }

    void GuiBackendCommand::addCallback(const std::function<void(const json& response)>& cb, bool onetime)
    {
        std::lock_guard l(_callbacks);
        _callbacks.data().push_back({cb, onetime});
    }

    void GuiBackendCommand::execCallbacks(const json& response)
    {
        ml::Vec<GuiCallback> callbacks;
        {
            std::lock_guard l(_callbacks);
            for (auto& cb : _callbacks.data())
            {
                if (!cb.cb)
                    continue;
                cb.cb(response);
                if (cb.onetime)
                   cb.cb = 0;
            }
        }
    }

    void GuiBackendCommand::onError(const std::string& error)
    {
        for (auto& b : _buttons)
            b->stopLoading();
        app()->main()->setWorking(false);
        app()->main()->setInfos("");
        ml::app()->error("Error in the process backend (" + _process->cmd_s() + ") :\n" + error);
    }

    void GuiBackendCommand::setExec(const std::function<void(const std::any&)>& f)
    {
        assert(false && "You can't set the exec function on a GuiBackendCommand, you need to use setProcessCommand");
    }

    json GuiBackendCommand::serialize() const
    {
        json _r = GuiCommand::serialize();
        _r["type"] = "guiBackendCommand";
        _r["function"] = _function;
        return _r;
    }

    void GuiBackendCommand::deserialize(const json& j)
    {
        GuiCommand::deserialize(j);
        if (j.contains("function"))
            _function = j["function"];
    }
}
