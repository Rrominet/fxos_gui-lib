#pragma once
#include "./ComposedInput.h"
#include "./Events.h"

namespace ml
{
    class Command;
    class Box;
    class CommandButton;
    class Entry;
    class Scrollable;
    class CommandsManager;
    class Window;
    class App;
    class Commander : public ComposedInput
    {
        public :
            Commander(Box* parent);
            virtual ~Commander();

            virtual void addEventListener(Event event, const std::function<void(EventInfos&)>& callback) override;
            virtual void setValue(const std::string& value) override;
            virtual void setValue(double value) override;
            virtual std::any valueAsAny() override;

            void addCommand(ml::Command* cmd);

            // if mgr is null, we use the ml::app()->cmds() one
            void addCommand(const std::string& id, ml::CommandsManager* mgr=nullptr);

            void addAllCommands(ml::CommandsManager* mgr=nullptr);
            void addAllCommands(ml::Window* win);
            void addAllCommands(ml::App* app);

            void removeCommand(ml::Command* cmd);

            // their could be several
            void removeCommands(const std::string& id);

            void removeCommand(const std::string& id, ml::CommandsManager* mgr);

            void clear();

            ml::Events& events() { return _events; }

        protected : 
            std::shared_ptr<Box> _box;
            std::shared_ptr<Entry> _search;
            std::shared_ptr<Scrollable> _list;

            ml::Vec<ml::Command*> _commands;
            ml::Vec<std::unique_ptr<CommandButton>> _buttons;

            void _onSearchChange();
            void _onSearchValid();

            double _score(const std::string& searched, ml::Command* cmd);
            void _sortCommands(const std::string& searched);

            ml::Events _events;


            // if true, the app will not launch any process
            // could be util, if you just want to react to fxhub event and manage the event withanother app.
            bool _doNothing = false; //bp cgs
        public :
            #include "./Commander_gen.h"
    };
}
