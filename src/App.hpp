#include "./App.h"
#include "./WindowsFactory.hpp"
#include "./GuiCommand.h"

namespace ml
{
    template<typename T>
        std::shared_ptr<T> App::createWindow(ml::Window* parent , const std::string& id)
        {
            return _windowsFactory.createWindow<T>(parent, id);
        }

    template<typename T>
        std::shared_ptr<T> App::createMainWindow(ml::Window* parent , const std::string& id)
        {
            auto w = this->createWindow<T>(parent, id); 
            this->setMain(w.get());
            return std::static_pointer_cast<T>(w);
        }

    template<typename T>
        std::shared_ptr<T> App::createDialog(ml::Window* parent , const std::string& id)
        {
            return _windowsFactory.createDialog<T>(parent, id);
        }

    template<typename T>
        std::shared_ptr<T> App::message(const std::string& message, ml::Window* parent, const std::string& id)
        {
            auto dialog = this->createDialog<T>(parent, id);
            dialog->setMessage(message);
            dialog->show();
            return dialog;
        }

        template<typename W>
            std::shared_ptr<GuiCommand> App::createShowWindowCommand(W** winptr, const std::string& cmdName, const std::string& id, const std::string& keybind)
            {
                auto f = [this, winptr](const std::any& args)
                {
                    if (!*winptr)
                        *winptr = this->createWindow<W>().get();
                    (*winptr)->show();
                };

                auto c = this->cmds().createCommand<GuiCommand>(cmdName, id);
                c->setExec(f);
                c->setKeybind(keybind);
                return c;
            }
}
