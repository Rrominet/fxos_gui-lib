#pragma once
#include "./Window.h"

//TODO
//add the command to reload the plugins
//add the command to install/uninstall plugins

namespace ml
{
    class Switch;
    template <class T, bool Dynamic, bool MaxDrawn>
        class List;

    class PluginListElmt
    {
        public:
            PluginListElmt(List<PluginListElmt, false, false>* ls, const std::string& path, const std::string& eventname, bool enabled);

            void draw();
            std::string searchStr();
            ml::Widget* gui(){return _box;}

            void _setEvents();

        private:
            ml::Box* _box = nullptr;
            ml::Box* _parent = nullptr;
            std::string _path;
            std::string _name;
            std::string _eventname;
            bool _enabled;

            ml::Switch* _switch = nullptr;
    };

    class PluginWindow : public Window
    {
        public:
            PluginWindow(App* app);
            PluginWindow(App* app, ml::Window* parent);
            virtual ~PluginWindow() = default;

            virtual void init() override;
            void setFromPlugins();
        
        protected : 
            ml::List<PluginListElmt, false, false>* _list = nullptr;
    };
}
