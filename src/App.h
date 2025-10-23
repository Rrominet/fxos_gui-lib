#pragma once
#include <memory>
#include "vec.h"
#include "./Window.h"
#include "./Checker.h"
#include "./WindowsFactory.h"
#include "./WidgetsFactory.h"
#include "./MenusFactory.h"
#include "./PropertiesManager.h"
#include "./Paths.h"
#include "commands/CommandsManager.h"
#include "./PanelsManager.h"
#include "./Argv.h"
#include "./GuiCommand.h"
#include "./Events.h"
#include "thread.h"

#ifdef __EMSCRIPTEN__
#include "./em/App_impl.h"
#else
#include "./gtk/App_impl.h"
#endif

class Process;
namespace ml
{
    class Menu;
    class Property;
    class PropertyGroup;
    class MessageDialog;
    class InfoDialog;
    class WarningDialog;
    class ErrorDialog;
    class ConfirmDialog;
    class AskPropertyDialog;
    class AskPropertyGroupDialog;
    class GuiBackendCommand;
    class WorkDialog;
    class ProgressDialog;
    class App    
    {
        public : 
            friend class App_impl;

            App();
            App(int argc, char *argv[]);
            virtual ~App();

            virtual void run();
            const Argv& argv()const {return _argv;}
            Argv& argv() {return _argv;}

            void removeWindow(ml::Window* window);
            void removeWindow(const std::string& id);
            void setMain(Window* main);

            template<typename T=ml::Window>
                std::shared_ptr<T> createMainWindow(ml::Window* parent = nullptr, const std::string& id="");

            template<typename T=ml::Window>
                std::shared_ptr<T> createWindow(ml::Window* parent = nullptr, const std::string& id="");

            template<typename T=ml::Dialog>
                std::shared_ptr<T> createDialog(ml::Window* parent = nullptr, const std::string& id="");

            // if parent is nullptr, the dialog will be floating alone.
            template<typename T=ml::MessageDialog>
                std::shared_ptr<T> message(const std::string& message, ml::Window* parent = nullptr, const std::string& id="");

            std::shared_ptr<InfoDialog>    info(const std::string& message, ml::Window* parent = nullptr, const std::string& id="");
            std::shared_ptr<WarningDialog> warning(const std::string& message, ml::Window* parent = nullptr, const std::string& id="");
            std::shared_ptr<ErrorDialog>   error(const std::string& message, ml::Window* parent = nullptr, const std::string& id="");
            std::shared_ptr<WorkDialog>   work(const std::string& message, ml::Window* parent = nullptr, const std::string& id="");
            std::shared_ptr<ProgressDialog>   progress(const std::string& message, ml::Window* parent = nullptr, const std::string& id="");
            std::shared_ptr<ConfirmDialog> confirm(const std::string& message="Are you sure ?", ml::Window* parent = nullptr, const std::string& id="");

            // used to ask about an existing prop
            std::shared_ptr<AskPropertyDialog> ask(ml::Property* prop, const std::string& message="", ml::Window* parent = nullptr);
            std::shared_ptr<AskPropertyDialog> ask(Property::PropertyType type, const std::string& propname="Value", const std::string& message="", ml::Window* parent = nullptr);

            std::shared_ptr<AskPropertyGroupDialog> ask(ml::PropertyGroup* prop, const std::string& message="", ml::Window* parent = nullptr);

            // for testing purpose
            void addCss(const std::string& filepath){_impl.addCss(filepath);}

            // the function will always be executed on the mainthread (particulary important for the gtk impl)
            size_t setTimeout(const std::function<void()>& callback, int ms){return _impl.setTimeout(callback, ms);}
            //
            // the function will always be executed on the mainthread (particulary important for the gtk impl)
            // It use a dispatcher and not the timeout.connect for gtk impl. Usefull if you ned to call this in another loop like a server loop with totally different thread. (the timeout method didn't work...)
            void queue(const std::function<void()>& callback){_impl.queue(callback);}
            // the function will always be executed on the mainthread (particulary important for the gtk impl)
            size_t setInterval(const std::function<void()>& callback, int ms){return _impl.setTimeout(callback, ms, true);}
            void removeInterval(size_t id){_impl.removeTimeout(id);}
            void removeQueued(size_t id){_impl.removeTimeout(id);}
            void removeTimeout(size_t id){_impl.removeTimeout(id);}

            void setCursor(const std::string& name);
            void quit() const {_impl.quit();}

            // the callback will always be executed on the mainthread
            std::shared_ptr<GuiBackendCommand> createBackendCommand(Process* p, const std::string &function, const json& args={}, const std::function<void(const json& response)>& cb=0);
            std::shared_ptr<GuiBackendCommand> createBackendCommand(Process* p, const std::string& name, const std::string& id, const std::string &function, const json& args={}, const std::function<void(const json& response)>& cb=0);

            //this will show the window if it exists, will create it if not
            //winptr will be populate with the window if its nullptr
            template<typename W=Window>
                std::shared_ptr<GuiCommand> createShowWindowCommand(W** winptr, const std::string& cmdName, const std::string& id="", const std::string& keybind="");

            void setClipboardText(const std::string& text){_impl.setClipboardText(text);}
            std::string clipboardText() const {return _impl.clipboardText();}

            //return nullptr if it does not exists
            Window* windowFromId(const std::string& id) const;
            bool windowExists(const std::string& id) const;

            std::unordered_map<std::string, std::shared_ptr<ml::Window>>& windows(){return _windows;};
            const std::unordered_map<std::string, std::shared_ptr<ml::Window>>& windows() const {return _windows;};

            // the callbacks will always be executed on the mainthread -- so you can call GUI stuff in them
            // the process* is own by the app, do not delete it yourself.
            Process* exec_async(ml::Vec<std::string> cmd, 
                    const std::string& cwd="",
                    const std::function<void()>& ondone=0,
                    const std::function<void(const std::string&)> onlineout=0,
                    const std::function<void(const std::string&)> onlineerr=0);

            th::ThreadPool& pool(){return _pool;}

            void openFile(const std::string& title="Open File...", 
                    const std::string& initialDir="",
                    const std::function<void(const std::string&)>& callback = nullptr)
            {
                _impl.openFile(title, initialDir, callback);
            }

            void openFiles(const std::string& title="Open Files...", 
                    const std::string& initialDir="",
                    const std::function<void(const ml::Vec<std::string>&)>& callback = nullptr)
            {
                _impl.openFiles(title, initialDir, callback);
            }

            void openFolder(const std::string& title="Open Folder...",
                    const std::string& initialDir="",
                    const std::function<void(const std::string&)>& callback = nullptr)
            {
                _impl.openFolder(title, initialDir, callback);
            }

            void openFolders(const std::string& title="Open Folders...",
                    const std::string& initialDir="",
                    const std::function<void(const ml::Vec<std::string>&)>& callback = nullptr)
            {
                _impl.openFolders(title, initialDir, callback);
            }

            void saveFile(const std::string& title="Save File...", 
                    const std::string& initialDir="",
                    const std::function<void(const std::string&)>& callback = nullptr)
            {
                _impl.saveFile(title, initialDir, callback);
            }

            bool isDarkTheme() const {return _impl.isDarkTheme();}
            void setAbout(const std::string& about) {_about = about;}

        protected : 
            bool _setIdCalled = false;
            std::unordered_map<std::string, std::shared_ptr<ml::Window>> _windows;

            ml::Checker _checker; //bp cg
            ml::WindowsFactory _windowsFactory; //bp cg
            ml::WidgetsFactory _widgetsFactory; //bp cg
            App_impl _impl; //bp cg

            Window* _focused = nullptr; //bp cgs
            Window* _main = nullptr; //bp cg

            ml::MenusFactory _menusFactory; //bp cg
            ml::PropertiesManager _props; //bp cg
            ml::CommandsManager _cmds; //bp cg
            ml::PanelsManager _panels; //bp cg
            
            Paths _paths; //bp cg

            ml::Vec<std::unique_ptr<Process>> _processes;

            ml::Events _events; //bp cg
            th::ThreadPool _pool;

            std::string _about;

            //about, quit, help (?), bug-report (?) etc.
            void _createBasicCommands();
            void _createAboutCommand();
            void _createQuitCommand();
            //...

        private : 
            void _init();
            Argv _argv;

        public : 
#include "./App_gen.h"
    };

    App* app();
}
