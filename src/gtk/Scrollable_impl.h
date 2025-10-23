#pragma once
#include "./Box_impl.h"
#include "gtkmm/scrolledwindow.h"

namespace ml
{
    class Scrollable; 
    class Scrollable_impl : public Widget_impl
    {
        public : 
            Scrollable_impl(Scrollable* abstract);
            virtual ~Scrollable_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::ScrolledWindow> scrollable(){return std::static_pointer_cast<Gtk::ScrolledWindow>(_gtk);}
            std::shared_ptr<Gtk::ScrolledWindow> scrollable() const {return std::static_pointer_cast<Gtk::ScrolledWindow>(_gtk);}

            void setChild(ml::Widget& child);
            void scrollDown(double amount);
            void scrollUp(double amount);

            void scrollLeft(double amount);
            void scrollRight(double amount);

            void addOnXScroll(const std::function<void(double)>& cb);
            void addOnYScroll(const std::function<void(double)>& cb);

            double scrollX() const;
            double scrollY() const;
    };
}
