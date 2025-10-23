#pragma once
#include "vec.h"
#include <gtkmm/overlay.h>
#include "./Widget_impl.h"

namespace ml
{
    class Widget;
    class AbsoluteBox;
    class AbsoluteBox_impl : public Widget_impl
    {
        public:
            AbsoluteBox_impl(AbsoluteBox* abstract);
            virtual ~AbsoluteBox_impl() = default;

            virtual void _createWidget() override;

            std::shared_ptr<Gtk::Overlay> overlay()
            {
                assert(_gtk);
                return std::static_pointer_cast<Gtk::Overlay>(_gtk);
            }

            std::shared_ptr<Gtk::Overlay> overlay() const
            {
                assert(_gtk);
                return std::static_pointer_cast<Gtk::Overlay>(_gtk);
            }

            void append(std::shared_ptr<ml::Widget> c);
            void prepend(std::shared_ptr<ml::Widget> c);
            void remove(ml::Widget* c);

            void setBackground(std::shared_ptr<ml::Widget> c);
            void removeBackground();

            void sendToFront(ml::Widget* c);
            void sendToBack(ml::Widget* c);
            void moveDepth(ml::Widget* c, unsigned int x);

        protected : 
            ml::Vec<Gtk::Widget*> _children;
    };
}
