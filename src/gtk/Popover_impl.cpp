
#include "./Popover_impl.h"
#include "../Popover.h"
#include "glibmm/main.h"
#include <gtkmm/window.h>

namespace ml
{
    Popover_impl::Popover_impl(Popover* abstract) : Widget_impl((Widget*)abstract)
    {
    }
    void Popover_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::Popover>();
        this->popover()->set_has_arrow(false);

        _setCloseEvent();
    }

    void Popover_impl::show()
    {
        auto root = _gtk->get_root();
        if (root)
            _lastFocus = root->get_focus();

        this->popover()->popup();
    }

    void Popover_impl::hide()
    {
        this->popover()->popdown();

    }

    void Popover_impl::setPosition(float x, float y)
    {
        Gdk::Rectangle rect;
        rect.set_x(x);
        rect.set_y(y);
        this->popover()->set_pointing_to(rect);
    }

    //Prevent the automatic refocus of the first widget when the popover is closed
    void Popover_impl::_setCloseEvent()
    {
        auto resetFocus = [this]
        {
            auto root = _gtk->get_root();
            if (!root)
                return;
            if (!_lastFocus)
                root->unset_focus();
            else 
                root->set_focus(*_lastFocus);
        };

        this->popover()->signal_closed().connect([this, resetFocus]{
                Glib::signal_idle().connect_once(resetFocus);
        });
    }
}

