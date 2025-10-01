#pragma once
#include <string>
#include <memory>
#include "./ComposedWidget.h"
#include "./Events.h"

// a button that represent a coommand.
// Should show the name, the description in helper and the Keybind to the right
// Should give a context menu to be able to modify this command
// Should execute the command when left clicked 

// this widget is not drawn as it creation but when draw() is called because you can have a lot commands in one big list, and it could be long to draw if you needed to draw all in once.
//
namespace ml
{
    class Box;
    class Label;
    class Scrollable;
    class Command;

    class CommandButton
    {
        public:
             //carefull here if you use an id, only the command globally in the app could be found (not the one in specific windows)
            CommandButton(ml::Box* box, const std::string& cmdId);
            CommandButton(ml::Box* box, ml::Command* cmd);

            virtual ~CommandButton();

            void draw();

            void show();
            void hide();
            void remove();

            void setCommand(ml::Command* cmd);
            void setEvents();

            ml::Events& events() { return _events; }

        protected: 
            ml::Command* _cmd = nullptr; //bp cg
            bool _drawn = false;

            std::shared_ptr<ml::Box> _button;
            std::shared_ptr<ml::Label> _label;
            std::shared_ptr<ml::Label> _right;

            void __construct(ml::Box* box, ml::Command* cmd);

            ml::Box* _futureParent = nullptr;
            ml::Events _events;

        public :
            #include "./CommandButton_gen.h"
    };
}
