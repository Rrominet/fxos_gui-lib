/*
 * An example is written in ExampleWindow.h
 */

#pragma once

#include "./WindowsFactory.h"
#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/Window_impl.h"
#else
#include "./gtk/Window_impl.h"
#endif

#include "./Scrollable.h"
#include "./WindowEventState.h"
#include "commands/CommandsManager.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

//this window has their personnal commands manager if you want to have commands that are specific to only one window.

class Process;
namespace ml
{
    class MenuBar;
    class Spinner;
    class App;
    class GuiCommand;
    class GuiBackendCommand;
    class Popover;
    class Commander;
    class Window
    {
        friend class WindowsFactory;

        public :
            Window(App* app);
            Window(App* app, ml::Window* parent);

            virtual ~Window();

#ifdef __EMSCRIPTEN__
            std::shared_ptr<emval> dom(){return _impl->window();}
#else
            std::shared_ptr<Gtk::Window> gtk(){return _impl->window();}
#endif

            App* app();
            void show(){_impl->show(); _visible = true;}

            virtual void init();
            virtual void setBasicEvents(); // called in init()
            void createBaseUi();
            unsigned int width(){return _impl->width();}
            unsigned int height(){return _impl->height();}
            unsigned int w(){return _impl->width();}
            unsigned int h(){return _impl->height();}

            void setSize(unsigned int w, unsigned int h){_impl->setSize(w, h);}
            void setWidth(unsigned int w){_impl->setWidth(w);}
            void setHeight(unsigned int h){_impl->setHeight(h);}

            void fitToContent(){this->setSize(-1, -1);}

            void setTitle(const std::string& title){_impl->setTitle(title);}
            std::string title() const {return _impl->title();}

            // remove the window from the app windows list
            void destroy();

            void hide();
            void toggle();

            bool hasParent(){return _parent != nullptr;}
            ml::Window* parent(){assert(_parent); return _parent;}
            void unparent(){_parent = nullptr;}

            void focus(){_impl->focus();}
            void unfocus(){_impl->unfocus();}

            void setChild(std::shared_ptr<ml::Widget> child);

            void addEventListener(Event event, const std::function<void const(EventInfos&)>& callback);
            void addWheelEventListener(const std::function<void(EventInfos&)>& callback){_impl->addWheelEventListener(callback);}
            void setMain(bool main);

            void addCssClass(const std::string& cls){_impl->addCssClass(cls);}
            void removeCssClass(const std::string& cls){_impl->removeCssClass(cls);}

            void showMenu(const std::string& id);
            math::vec2d mousePos(){return _impl->mousePos();}

            void setCursor(const std::string& cursor){_content->setCursor(cursor);}

            // this the footer content
            void setInfos(const std::string& infos);

            // add a spinner at the end of the window.
            void setWorking(bool val);

            // add the infos of the command
            void setInfosFromCommand(GuiCommand* cmd);

            // the callback will always be executed on the mainthread
            std::shared_ptr<GuiBackendCommand> createBackendCommand(Process* p, const std::string &function, const json& args={}, const std::function<void(const json& response)>& cb=0);

            void hideOnClose(bool val=true){_impl->hideOnClose(val);}
            bool doHideOnClose() const {return _impl->doHideOnClose();}

            virtual json serialize() const;
            virtual void deserialize(const json& j);

            void addOnClose(const std::function<void()>& callback){_impl->addOnClose(callback);}
            void addOnHide (const std::function<void()>& callback){_impl->addOnHide(callback);}

            ml::Commander* createCommander();
            ml::Commander* createCommanderFromAppCmds();
            ml::Commander* createCommanderFromThisWindowCmds();

            void showCommander();

        protected : 
            App* _app;
            ml::Window* _parent = nullptr; //pb s

            // this changed
            std::shared_ptr<Window_impl> _impl; //bp cg

            std::shared_ptr<Box> _content; //bp g
            std::shared_ptr<Box> _head; //bp g
            std::shared_ptr<Box> _body; //bp g
            std::shared_ptr<Scrollable> _main; //bp g
            std::shared_ptr<Box> _foot; //bp g
            std::shared_ptr<Label> _footLabel = nullptr; //bp g
            std::shared_ptr<Spinner> _footSpinner = nullptr; //bp g

            bool _visible = false; //bp g
                                   //
            WindowEventState _state; //bp cg
            std::shared_ptr<MenuBar> _menuBar; //bp cg
            ml::CommandsManager _cmds; //bp cg

            std::string _id; //bp cg
            
            bool _stayHiddenFirstRun = false; //bp cgs

            // to create the commander system automatcly if needed
            ml::Popover* _commanderPopover = nullptr;
            ml::Commander* _commander = nullptr;

        public : 
#include "Window_gen.h"
//#include "./Container_creators_gen.h"
    };
}
