#pragma once
#include <gtkmm/box.h>
#include <memory>
#include "./Widget_impl.h"
#include "../Widget.h"
#include "../enums.h"

namespace ml
{
    class Box;
    class Widget;
    class Box_impl : public Widget_impl
    {
        public:
            Box_impl(Box* abstract);
            virtual ~Box_impl() = default;

            virtual void _createWidget() override;

            std::shared_ptr<Gtk::Box> box()
            {
                assert(_gtk);
                return std::static_pointer_cast<Gtk::Box>(_gtk);
            }

            std::shared_ptr<Gtk::Box> box() const
            {
                assert(_gtk);
                return std::static_pointer_cast<Gtk::Box>(_gtk);
            }

            void setOrient(Orient orient);
            void append(std::shared_ptr<ml::Widget> child){this->box()->append(*child->gtk()); _children.append(child->gtk().get());}
            void prepend(std::shared_ptr<ml::Widget> child){this->box()->prepend(*child->gtk()); _children.append(child->gtk().get());}
            void remove(ml::Widget* child);

            void moveChild(size_t from, size_t to);
            void setSpacing(int space){this->box()->set_spacing(space);}
            int spacing() const{return this->box()->get_spacing();}

        protected : 
            ml::Vec<Gtk::Widget*> _children;
    };
}
