#pragma once
#include <memory>
#include <functional>
#include "vec.h"
#include "./Box.h"

//MenuButton is a button in vertical menu, when clicked, it execute a function or a command
//MenuBarButton is a button in horizontal menu, when clicked, it shows a menu with a list of MenuButtons

namespace ml
{
    class MenuBarButton;
    class MenuBar
    {
        public : 
            MenuBar(ml::Box* box);
            virtual ~MenuBar();

            void init();

            void addMenu(const std::string& id);

        protected : 
            ml::Vec<std::shared_ptr<ml::MenuBarButton>> _buttons; //bp cg
            std::shared_ptr<ml::Box> _box; //bp cg
        public : 
#include "./MenuBar_gen.h"
    };
}
