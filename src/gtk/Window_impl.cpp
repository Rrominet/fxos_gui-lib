#include "./Window_impl.h"
#include "../Window.h"
#include "debug.h"
#include "gdkmm/enums.h"
#include <gdkmm/seat.h>
#include "../EventInfos.h"

namespace ml
{
    Window_impl::Window_impl(Window* win) : _win(win)
    {
        this->addOnClose([this]{
                    _win->destroy();
                });
    }

    Window_impl::~Window_impl()
    {
        lg("~Window_impl");
    }

    void Window_impl::_createWindow()
    {
        _window = std::make_shared<Gtk::Window>();
        if (_win->hasParent())
            _window->set_transient_for(*_win->parent()->gtk());
        _window->add_css_class("window");
        _setCloseEvent();
    }

    void Window_impl::addCssClass(const std::string& cls)
    {
        _window->add_css_class(cls);	
    }

    void Window_impl::removeCssClass(const std::string& cls)
    {
        _window->remove_css_class(cls);	
    }

    void Window_impl::remove()
    {
        _window->destroy();
        _window = nullptr;
    }

    math::vec2d Window_impl::mousePos()
    {
        auto surface = _window->get_surface();
        auto display = _window->get_display();
        auto seat = display->get_default_seat();
        auto pointer_device = seat->get_pointer();

        double x, y;
        Gdk::ModifierType modifiers;
        surface->get_device_position(pointer_device, x, y, modifiers);

        return math::vec2d(x, y);
    }

    void Window_impl::addWheelEventListener(const std::function<void(EventInfos&)>& callback)
    {
        _createControllerScroll();
        auto f = [callback](double dx, double dy)
        {
            EventInfos e;
            e.dy = dy;
            e.dx = dx;
            callback(e);

            return e.preventDefault;
        };
        _controller_scroll->signal_scroll().connect(f, true);
    }


    void Window_impl::_createControllerScroll()
    {
        if (!_controller_scroll)
        {
            _controller_scroll = Gtk::EventControllerScroll::create();
            _controller_scroll->set_flags(Gtk::EventControllerScroll::Flags::BOTH_AXES);
            _window->add_controller(_controller_scroll);
        }
    }

    void Window_impl::_setCloseEvent()
    {
        _window->signal_close_request().connect([this]
                {
                    if (_hideOnClose)
                    {
                        _window->hide();
                        lg("GTK Window hidden from close request.");
                        return true;
                    }
                    else 
                    {
                        lg("GTK Window destroyed from close request.");
                        _onclose.exec();
                        return false;
                    }
                }, true);
    }

    void Window_impl::hideOnClose(bool val)
    {
        _hideOnClose = val; 
    }
}
