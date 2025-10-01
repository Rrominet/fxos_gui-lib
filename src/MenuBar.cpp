#include "./MenuBar.h"
#include "./App.h"
#include "./Menu.h"
#include "./MenuBarButton.h"
#include <stdexcept>

namespace ml
{
    MenuBar::MenuBar(ml::Box* box) : _buttons{}
    {
        _box = box->createBox();
    }

    MenuBar::~MenuBar()
    {

    }

    void MenuBar::init()
    {
        _box->addCssClass("menu-bar");
        _box->setOrient(Orient::HORIZONTAL);
    }

    void MenuBar::addMenu(const std::string& id)
    {
        std::shared_ptr<ml::Menu> menu;
        try
        {
            menu = ml::app()->menusFactory().menus().at(id);
        }
        catch(const std::exception& e)
        {
            throw std::out_of_range("Menu " + id + " not found. You need to create it before adding it to a menubar using ml::app()->menusFactory().create(...)");
        }
        auto button = std::make_shared<ml::MenuBarButton>(this, menu.get());
        _buttons.push_back(button);
    }
}
