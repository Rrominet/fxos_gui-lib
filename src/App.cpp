#include "./App.h"
#include "./EventInfos.h"
#include "./keybinds.h"
#include "./App.hpp"
#include "./IconMessageDialog.h"
#include "./ConfirmDialog.h"
#include "./AskPropertyDialog.h"
#include "./AskPropertyGroupDialog.h"
#include "./GuiBackendCommand.h"
#include "./WorkDialog.h"
#include "./ProgressDialog.h"

namespace ml
{
    App* _app = nullptr;

    App::App() : _windows(), _windowsFactory(), _impl(this), _argv(_impl.argv())
    {
        _app = this;
        _init();
    }

    App::~App()
    {
        lg("App::~App");
    }

    App::App(int argc, char *argv[]) : _windows(), _windowsFactory(), _impl(this, argc, argv), _argv(_impl.argv())
    {
        _app = this;
        _init();
    }

    void App::_init()
    {
        _checker.init("can-construct-widget", "You can't construct a widget with new or make_unique/shared or even on the stack.\nYou need to create it via the createWidget method in Box or Window.");
        _checker.init("can-construct-window", "You can't construct a window with new or make_unique/shared or even on the stack.\nYou need to create it via the windowsFactory.");
        _checker.init("can-set-window", "The setWindow method can't be called by you. Use append, prepend or setChild to trigger it from its logic.");
    }

    void App::run()
    {
        _impl.run();
    }

    App* app()
    {
        assert(_app != nullptr && "ml::app(), _app is nullptr. Did you created it ?");
        return _app;
    }

    void App::removeWindow(const std::string& id)
    {
        lg("App::removeWindow (by id)" << id);
        if (_windows.find(id) != _windows.end())
            _windows.erase(id);
        else 
            lg("No window to remove with this id : " << id);
    }

    void App::removeWindow(ml::Window* window)
    {
        lg("App::removeWindow" << window);
        this->removeWindow(window->id());
    }

    void App::setMain(Window* main)
    {
        if (_main)
            _main->setMain(false);
        _main = main;
        _main->setMain(true);
    }

    std::shared_ptr<InfoDialog> App::info(const std::string& message, ml::Window* parent, const std::string& id)
    {
        return this->message<InfoDialog>(message, parent, id);
    }

    std::shared_ptr<WarningDialog> App::warning(const std::string& message, ml::Window* parent , const std::string& id)
    {
        return this->message<WarningDialog>(message, parent, id);
    }

    std::shared_ptr<ErrorDialog> App::error(const std::string& message, ml::Window* parent , const std::string& id)
    {
        return this->message<ErrorDialog>(message, parent, id);
    }

    std::shared_ptr<WorkDialog>   App::work(const std::string& message, ml::Window* parent , const std::string& id)
    {
        return this->message<WorkDialog>(message, parent, id);
    }

    std::shared_ptr<ProgressDialog>   App::progress(const std::string& message, ml::Window* parent , const std::string& id)
    {

        return this->message<ProgressDialog>(message, parent, id);
    }

    std::shared_ptr<ConfirmDialog> App::confirm(const std::string& message, ml::Window* parent , const std::string& id)
    {
        return this->message<ConfirmDialog>(message, parent, id);
    }

    std::shared_ptr<AskPropertyDialog> App::ask(ml::Property* prop, const std::string& message, ml::Window* parent )
    {
        auto dg = this->message<AskPropertyDialog>(message, parent);
        dg->set(prop);
        dg->drawProp();
        return dg;
    }
    std::shared_ptr<AskPropertyDialog> App::ask(Property::PropertyType type, const std::string& propname, const std::string& message, ml::Window* parent )
    {
        auto dg = this->message<AskPropertyDialog>(message, parent);
        dg->set(type, propname);
        dg->drawProp();
        return dg;
    }

    std::shared_ptr<AskPropertyGroupDialog> App::ask(ml::PropertyGroup* prop, const std::string& message, ml::Window* parent )
    {
        auto dg = this->message<AskPropertyGroupDialog>(message, parent);
        dg->set(prop);
        dg->drawProp();
        return dg;
    }

    void App::setCursor(const std::string& name)
    {
        for (auto& w : _windows)
            w.second->setCursor(name);	
    }

    std::shared_ptr<GuiBackendCommand> App::createBackendCommand(Process* p, const std::string &function, const json& args, const std::function<void(const json& response)>& cb)
    {
        auto cmd = _cmds.createCommand<GuiBackendCommand>(function);
        cmd->setProcessCommand(p, function, args, cb);
        return cmd;
    }

    std::shared_ptr<GuiBackendCommand> App::createBackendCommand(Process* p, const std::string& name, const std::string& id, const std::string &function, const json& args, const std::function<void(const json& response)>& cb)
    {
        auto cmd = _cmds.createCommand<GuiBackendCommand>(name, id);
        cmd->setProcessCommand(p, function, args, cb);
        return cmd;
    }

    Window* App::windowFromId(const std::string& id) const
    {
        if (_windows.find(id) == _windows.end())	
            return nullptr;
        else 
            return _windows.at(id).get();
    }

    bool App::windowExists(const std::string& id) const
    {
        if (this->windowFromId(id))
            return true;
        return false;
    }

    Process* App::exec_async(ml::Vec<std::string> cmd,
            const std::string& cwd,
            const std::function<void()>& ondone,
            const std::function<void(const std::string&)> onlineout,
            const std::function<void(const std::string&)> onlineerr)
    {
        auto p = std::make_unique<Process>(cmd);
        _processes.push(std::move(p));

        auto p_ptr = _processes.back().get();

        if (!cwd.empty())
            p_ptr->setCwd(cwd);
        if (onlineout)
        {
            auto mth_onlineout = [this, onlineout](const std::string& s)
            {
                this->queue([s, onlineout]{onlineout(s);});
            };
            p_ptr->addOnOutput(mth_onlineout);
        }
        if (onlineerr)
        {
            auto mth_onlineerr = [this, onlineerr](const std::string& s)
            {
                this->queue([s, onlineerr]{onlineerr(s);});
            };
            p_ptr->addOnError(onlineerr);
        }

        auto rm_process = [this](Process* p)
        {
            for (auto it = _processes.begin(); it != _processes.end(); ++it)
            {
                if (it->get() == p)
                {
                    _processes.vec.erase(it);
                    break;
                }
            }
        };

        if (ondone)
        {
            auto mth_ondone = [this, ondone, rm_process, p_ptr]
            {
                this->queue([ondone, rm_process, p_ptr]{
                            ondone();
                            rm_process(p_ptr);
                        });
            };
            p_ptr->addOnEnd(ondone);
        }
        else 
        {
            p_ptr->addOnEnd([this, rm_process, p_ptr]
            {
                this->queue([this, rm_process, p_ptr]{
                            rm_process(p_ptr);
                            lg(_processes.size());
                        });
            });
        }

        p_ptr->start();
        return p_ptr;
    }
}
