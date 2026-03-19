#include "./MenuBarButton.h"
#include "./MenuBar.h"
#include "./Menu.h"
#include "./Button.h"
#include "./Window.h"

namespace ml
{
    MenuBarButton::MenuBarButton(ml::MenuBar* menubar,ml::Menu* menu) : MenuButton(menubar->box().get())
    {
        _menu = menu;
        this->setText(menu->name());
        this->setOnClick([menu, this](){
            _button->window()->showMenu(menu->id());
        });
    }


    MenuBarButton::~MenuBarButton()
    {

    }

}
