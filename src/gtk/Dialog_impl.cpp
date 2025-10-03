#include "./Dialog_impl.h"
#include <gtkmm/dialog.h>

namespace ml
{
    Dialog_impl::Dialog_impl(Dialog* win) : Window_impl(win)
    {
    }

    void Dialog_impl::_createWindow()
    {
        if (_win->hasParent())
            _window = std::make_shared<Gtk::Dialog>("Dialog", *_win->parent()->gtk());
        else 
            _window = std::make_shared<Gtk::Dialog>();
        _window->add_css_class("window");
        _window->add_css_class("dialog");
    }
}
