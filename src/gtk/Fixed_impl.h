
#pragma once
#include <gtkmm/fixed.h>
#include <memory>
#include "./Widget_impl.h"
#include "vec.h"
#include "geometry.h"

namespace ml
{
    class Fixed;
    class Fixed_impl : public Widget_impl
    {
        public:
            Fixed_impl(Fixed* abstract);
            virtual ~Fixed_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::Fixed> fixed(){return std::static_pointer_cast<Gtk::Fixed>(_gtk);}
            std::shared_ptr<Gtk::Fixed> fixed() const{return std::static_pointer_cast<Gtk::Fixed>(_gtk);}

            void append(std::shared_ptr<ml::Widget> child);
            void remove(ml::Widget* child);

            //setPosition equivalent(it does not add to the existing translation)
            void move(ml::Widget* w, double x, double y);
            geometry::Point<double> widgetPos(ml::Widget* w);

        protected:
            ml::Vec<Gtk::Widget*> _children;
    };
}
