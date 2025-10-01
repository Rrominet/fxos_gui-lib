
#pragma once
#include <gtkmm/popover.h>
#include <memory>
#include "../Widget.h"
#include "./Widget_impl.h"
#include "gtkmm/widget.h"

namespace ml
{
    class Popover;
    class Popover_impl : public Widget_impl
    {
        public:
            Popover_impl(Popover* abstract);
            virtual ~Popover_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::Popover> popover(){return std::static_pointer_cast<Gtk::Popover>(_gtk);}
            void setChild(std::shared_ptr<ml::Widget> child){this->popover()->set_child(*child->gtk());}

            virtual void show() override;
            virtual void hide() override;

            void setPosition(float x, float y);
            void setAutoHide(bool v=true){this->popover()->set_autohide(v);}

        private : 
            Gtk::Widget* _lastFocus = nullptr;

            void _setCloseEvent();
    };
}
