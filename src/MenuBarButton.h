#pragma once
#include "./MenuButton.h"

namespace ml
{
    class MenuBar;
    class Menu;
    class MenuBarButton : public MenuButton    
    {
        public :
            MenuBarButton(ml::MenuBar* menubar, ml::Menu* menu);
            virtual ~MenuBarButton();

        private : 
            ml::Menu* _menu = nullptr; //bp cg

        public : 
#include "./MenuBarButton_gen.h"
    };
}
