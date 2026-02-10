#pragma once
#include <gtkmm/window.h>
#include <memory>

#include "../Widget.h"
#include "mlMath.h"

namespace ml
{
    class Window;
    class Window_impl
    {
        public : 
            Window_impl(Window* win);
            virtual ~Window_impl();

            void show(){_window->show();}
            void hide(){_window->hide(); _onhide.exec();}
            std::shared_ptr<Gtk::Window> window(){return _window;}

            virtual void _createWindow();

            void setChild(std::shared_ptr<ml::Widget> child){_window->set_child(*child->gtk());}

            void focus(){_window->grab_focus();}
            void unfocus(){_window->unset_focus();};

            unsigned int width(){return _window->get_width();}
            unsigned int height(){return _window->get_height();}

            void setTitle(const std::string& title){_window->set_title(title);}
            std::string title() const {return _window->get_title();}

            void setSize(unsigned int w, unsigned int h){_window->set_default_size(w, h);}
            void setWidth(unsigned int w){_window->set_default_size(w, this->height());}
            void setHeight(unsigned int h){_window->set_default_size(this->width(), h);}

            void remove();
            void setMain(bool main){}

            void addCssClass(const std::string& cls);
            void removeCssClass(const std::string& cls);

            math::vec2d mousePos();

            void addWheelEventListener(const std::function<void(EventInfos&)>& callback);
            void hideOnClose(bool val);
            bool doHideOnClose() const {return _hideOnClose;}

            void addOnClose(const std::function<void()>& callback){_onclose.push_back(callback);}
            void addOnHide(const std::function<void()>& callback){_onhide.push_back(callback);}
            ml::Widget* focusedWidget() const;

        protected : 
            Window* _win = nullptr;
            std::shared_ptr<Gtk::Window> _window;

            Glib::RefPtr<Gtk::EventControllerScroll> _controller_scroll = nullptr;

            void _createControllerScroll();
            void _setCloseEvent();
            bool _hideOnClose = false;

            ml::Vec<std::function<void()>> _onclose;
            ml::Vec<std::function<void()>> _onhide;
    };
}
