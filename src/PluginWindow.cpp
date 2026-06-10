#ifdef __EMSCRIPTEN__
#else 

#include "./PluginWindow.h"
#include "enums.h"
#include "./Switch.h"
#include "./List.h"

#include "./Box.hpp"
#include "./Scrollable.hpp"

namespace ml
{
    PluginListElmt::PluginListElmt(List<PluginListElmt, false, false>* ls, const std::string& path, const std::string& eventname, bool enabled) : _path(path), _eventname(eventname), _enabled(enabled)
    {
        _name = files::name(_path); 
        _parent = ls->listbox();
        this->draw();
    }

    void PluginListElmt::draw()
    {
        _box = _parent->createBox().get();
        _box->setHelp(_path);
        _box->setOrient(ml::HORIZONTAL);
        _box->addCssClass("plugin-list-elmt");

        _box->createLabel(_name)->addCssClass("name");
        _box->createLabel(_eventname)->addCssClass("event");

        _switch = _box->createSwitch().get();
        _switch->setHExpand(true);
        if (_enabled)
            _switch->setValue(true);

        _setEvents();
    }

    std::string PluginListElmt::searchStr()
    {
        return _name + " " + _eventname; 
    }

    void PluginListElmt::_setEvents()
    {
        auto onswitch = [this](EventInfos& e)
        {
            ml::Ret<> res;
            if (_switch->value())
                res = ml::app()->pluginManager().enable(_eventname, _name);
            else
                res = ml::app()->pluginManager().disable(_eventname, _name);
            if (!res.success)
                ml::app()->error(res.message);
        };
        _switch->addEventListener(ml::CHANGE, onswitch);
    }

    PluginWindow::PluginWindow(App* app) : Window(app) {}
    PluginWindow::PluginWindow(App* app, ml::Window* parent) : Window(app, parent) {}

    void PluginWindow::init()
    {
        Window::init();        
        this->setTitle("Plugin Manager");
        this->setSize(640, 480);

        _list = this->main()->createComposedWidget<List<PluginListElmt, false, false>>(&this->main()->content()).get();
        this->setFromPlugins();
    }

    void PluginWindow::setFromPlugins()
    {
        auto& pm = ml::app()->pluginManager();
        if (pm.state() != ml::PluginManager::State::LOADED) 
        {
            ml::app()->error("Error while loading the plugins, the plugin manager is not loaded.");
            return;
        }

        for (const auto& pair : pm.plugins())
        {
            for (auto& plugin : pair.second)
                _list->createElmt(_list, plugin.path(), pair.first, pm.enabled(pair.first, plugin.name()));
        }
    }
}

#endif
