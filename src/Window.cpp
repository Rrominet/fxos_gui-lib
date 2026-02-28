#include <cassert>
#include "./Window.h"
#include "./App.h"
#include "./Box.h"
#include "./Scrollable.h"
#include "./Label.h"
#include "./Button.h"
#include "./Widget.h"
#include "./EventInfos.h"
#include "./Popover.h"
#include "./MenuBar.h"
#include "./Popover.h"

#include "./Box.hpp"
#include "./Scrollable.hpp"
#include "./keybinds.h"
#include "./enums.h"
#include "./Spinner.h"

#include "./GuiBackendCommand.h"
#include "./Commander.h"

namespace ml
{
    Window::Window(App* app) 
    {
        assert(app != nullptr && "App can't be nullptr when creating a window.");
        app->checker().check("can-construct-window");
        _app = app;
    }

    Window::Window(App* app, ml::Window* parent)
    {
        assert(app != nullptr && "App can't be nullptr when creating a window.");
        app->checker().check("can-construct-window");
        _app = app;

        assert(parent != nullptr && "Parent can't be nullptr when creating a window.");
        _parent = parent;
    }

    Window::~Window()
    {
        lg("Window::~Window");
    }

    App* Window::app()
    {
        assert(_app != nullptr && "Window::app(), _app is nullptr.");
        return _app;
    }

    void Window::init()
    {
        this->createBaseUi();
        this->hideOnClose(true);
        this->setBasicEvents();
    }

    void Window::setBasicEvents()
    {
        lg("Window::setBasicEvents()");
        this->addEventListener(Event::MOUSE_MOVE, [this](EventInfos& event) {
                _state.x = event.x;
                _state.y = event.y;
                event.preventDefault = false;
        });

        this->addEventListener(Event::FOCUS, [this](EventInfos& event) {
                _state.alt = false;
                _state.ctrl = false;
                _state.shift = false;
                _state.meta = false;
                _state.key = "";
                ml::app()->setFocused(this);
                event.preventDefault = false;
        });

        this->addEventListener(Event::UNFOCUS, [this](EventInfos& event) {
                _state.alt = false;
                _state.ctrl = false;
                _state.shift = false;
                _state.meta = false;
                _state.key = "";
                event.preventDefault = false;
        });

        this->addEventListener(Event::KEY_UP, [this](EventInfos& event) {
                if (event.key == "Alt_L" || event.key == "Alt_R" || event.key == "ISO_Level3_Shift")
                    _state.alt = false;
                else if (event.key == "Control_L" || event.key == "Control_R")
                    _state.ctrl = false;
                else if (event.key == "Shift_L" || event.key == "Shift_R")
                    _state.shift = false;
                else if (event.key == "Super_L" || event.key == "Super_R")
                    _state.meta = false;
                else 
                    _state.key = "";
                event.preventDefault = false;
        });

        this->addEventListener(Event::KEY_DOWN, [this](EventInfos& event) {
                if (event.key == "Alt_L" || event.key == "Alt_R" || event.key == "ISO_Level3_Shift")
                    _state.alt = true;
                else if (event.key == "Control_L" || event.key == "Control_R")
                    _state.ctrl = true;
                else if (event.key == "Shift_L" || event.key == "Shift_R")
                    _state.shift = true;
                else if (event.key == "Super_L" || event.key == "Super_R")
                    _state.meta = true;
                else 
                    _state.key = event.key;
                event.preventDefault = false;
        });


        //note this is important to know : 
        //the priority of the keybinds arelike this : 
        // 1 - basic keybinds of the window
        // 2 - the commands of the window
        // 3 - the commands of the app.
        //
        // If 1 is triggered, 2 and 3 are ignored.
        // if 2 is triggered, 3 is ignored.
        auto keyevents = [this](EventInfos& event)
        {
            lg("keydown event (basic events)");
            auto focusedWidget = ml::app()->focusedWidget();
            ml::keybinds::FocusedType focusedType = ml::keybinds::NONE;
            if(focusedWidget)
            {
                if (focusedWidget->isOnelineEditable())
                    focusedType = ml::keybinds::ONELINE_EDITABLE;
                else if (focusedWidget->isMultilineEditable())
                    focusedType = ml::keybinds::MULTILINE_EDITABLE;
            }

            for (const auto& kb : _windowKeyBinds)
            {
                if (keybinds::match(kb.first, event, focusedType))
                {
                    if (kb.second())
                    {
                        event.preventDefault = true;
                        return;
                    }
                }
            }

            for (const auto& cmd : _cmds.commands())  
            {
                if (keybinds::match(cmd.second->keybind(), event, focusedType))
                {
                    cmd.second->exec();
                    event.preventDefault = true;
                    return;
                }
            }

            for (const auto& cmd : ml::app()->cmds().commands())  
            {
                if (keybinds::match(cmd.second->keybind(), event, focusedType))
                {
                    cmd.second->exec();
                    event.preventDefault = true;
                    return;
                }
            }
        };

        this->addEventListener(Event::KEY_DOWN, keyevents);
    }

    void Window::createBaseUi()
    {
        _content = ml::app()->widgetsFactory().createBox(this);
        _content->setCursor("default");
        _content->addCssClass("content");
 
        _head = ml::app()->widgetsFactory().createBox(_content.get());
        _head->addCssClass("head");
        _head->setOrient(Orient::HORIZONTAL);

        _body = _content->createBox();
        _body->addCssClass("body");
        _body->setOrient(Orient::VERTICAL);

        _menuBar = ml::app()->widgetsFactory().create<MenuBar>(_body.get());

        // replace this to a new type Scrollable Box
        _main = _body->createScrollable();
        _main->addCssClass("main");
        _main->setOrient(Orient::VERTICAL);

        _foot = _content->createBox();
        _foot->addCssClass("foot");
        _foot->setOrient(Orient::HORIZONTAL);
        _foot->setHExpand(true);
        _foot->setVExpand(false); //changed.
        _foot->setHAlign(RIGHT);
        _foot->setVAlign(BOTTOM);
    }

    void Window::destroy()
    {
        this->impl()->remove();
        ml::app()->removeWindow(this);
    }

    void Window::hide()
    {
        this->unfocus();
        this->impl()->hide();
        _visible = false;
    }
    void Window::toggle()
    {
        if (this->visible())
            this->hide();
        else
            this->show();
    }

    void Window::setChild(std::shared_ptr<ml::Widget> child)
    {
        ml::app()->checker().set("can-set-window", true);
        child->setWindow(this);
        ml::app()->checker().set("can-set-window", false);
        this->impl()->setChild(child);
    }

    void Window::addEventListener(Event event, const std::function<void const(EventInfos&)>& callback)
    {
        assert(_content);
        if (event == WHEEL)
            this->addWheelEventListener(callback);
        else 
            _content->addEventListener(event, callback);
    }

    void Window::setMain(bool main)
    {
        if (main)
            this->addCssClass("main");
        else 
            this->removeCssClass("main");
        this->impl()->setMain(main);
    }

    void Window::showMenu(const std::string& id)
    {
        try
        {
            auto menu = ml::app()->menusFactory().menus().at(id);
            auto pos = this->mousePos();
            menu->popover()->setPosition(pos.x(), pos.y());
            _body->append(menu->popover());
            menu->popover()->show();
            menu->events().emit("shown");
        }
        catch (const std::exception& e)
        {
            ml::app()->error("Error showing menu '" + id + "' : " + e.what(), this);
        }
    }

    void Window::setInfos(const std::string& infos)
    {
        if (!_footLabel)
            _footLabel = _foot->createLabel(infos);
        else 
            _footLabel->setText(infos);
    }


    void Window::setWorking(bool val)
    {
        if (!_footSpinner)
            _footSpinner = _foot->createSpinner();
        if (val)
            _footSpinner->show();
        else 
            _footSpinner->hide();
    }


    void Window::setInfosFromCommand(GuiCommand* cmd)
    {
        if (cmd->waiting())
        {
            this->setInfos("Executing : " + cmd->name());
            this->setWorking(true);
        }
        else 
        {
            this->setInfos(cmd->name() + " executed.");
            this->setWorking(false);
        }
    }

    std::shared_ptr<GuiBackendCommand> Window::createBackendCommand(Process* p, const std::string &function, const json& args, const std::function<void(const json& response)>& cb)
    {
        auto cmd = _cmds.createCommand<GuiBackendCommand>(function);
        cmd->setProcessCommand(p, function, args, cb);
        return cmd;
    }

    json Window::serialize() const
    {
        json _r = json::object();
        _r["type"] = "window";
        _r["id"] = this->id();
        _r["title"] = this->title();
        return _r;
    }

    void Window::deserialize(const json& j)
    {
        if (j.contains("title"))
            this->setTitle(j["title"].get<std::string>());
    }

    ml::Commander* Window::createCommander()
    {
        if (_commander) 
        {
            ml::app()->error("Can't have more than one commander per window.");
            return _commander;
        }

        _commanderPopover = _main->createPopover().get();
        _commander = _commanderPopover->content()->createComposedWidget<ml::Commander>(&_commanderPopover->content()->content()).get();
        _commanderPopover->setWidth(500);
        _commander->events().add("valid", [this]{
            _commanderPopover->hide();
        });

        return _commander;
    }

    ml::Commander* Window::createCommanderFromAppCmds()
    {
        this->createCommander();
        _commander->addAllCommands(ml::app());
        return _commander;
    }

    ml::Commander* Window::createCommanderFromThisWindowCmds()
    {
        this->createCommander();
        _commander->addAllCommands(this);
        return _commander;
    }

    void Window::showCommander()
    {
        if (!_commanderPopover)
        {
            ml::app()->error("You need to create a commander before showing it.\n(missing the popover)");
            return;
        }
        if (!_commander)
        {
            ml::app()->error("You need to create a commander before showing it.\n(missing the commander)");
            return;
        }

        _commanderPopover->show();
        auto mpos = this->mousePos();
        _commanderPopover->setPosition(mpos.x(), mpos.y());
    }

    void Window::addKeybind(const std::string& keybind, const std::function<bool()>& callback)
    {
        _windowKeyBinds[keybind] = callback;
    }

    bool Window::removeKeybind(const std::string& keybind)
    {
        if (_windowKeyBinds.find(keybind) != _windowKeyBinds.end())
        {
            _windowKeyBinds.erase(keybind);
            return true;
        }
        return false;
    }

    void Window::clearKeybinds()
    {
        _windowKeyBinds.clear();
    }

    void Window::pop(Popover* popover, int sx, int sy, int px, int py)
    {
        auto pos = this->mousePos();
        if (px != -1)
            pos.x() = px;
        if (py != -1)
            pos.y() = py;

        popover->setPosition(pos.x(), pos.y());
        if (sx != -1 && sy != -1)
            popover->setSize(sx, sy);
        else if(sx != -1)
            popover->setWidth(sx);
        else if (sy != -1)
            popover->setHeight(sy);
        popover->show();
    }

    ml::Popover* Window::createPopover()
    {
        return _content->createPopover().get();
    }
}
