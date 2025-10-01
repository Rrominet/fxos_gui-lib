#include "./Scrollable_impl.h"
#include <memory>
#include <gtkmm/adjustment.h>

namespace ml
{
    Scrollable_impl::Scrollable_impl(Scrollable* abstract) : Widget_impl((Widget*)abstract)
    {

    }

    void Scrollable_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::ScrolledWindow>();
        this->scrollable()->set_propagate_natural_width();
        this->scrollable()->set_propagate_natural_height();
    }

    void Scrollable_impl::setChild(ml::Widget& child)
    {
        this->scrollable()->set_child(*child.gtk());
    }

    void Scrollable_impl::scrollDown(double amount)
    {
        this->scrollable()->get_vadjustment()->set_value(this->scrollable()->get_vadjustment()->get_value() + amount);
    }


    void Scrollable_impl::scrollUp(double amount)
    {
        this->scrollable()->get_vadjustment()->set_value(this->scrollable()->get_vadjustment()->get_value() - amount);
    }


    void Scrollable_impl::scrollLeft(double amount)
    {
        this->scrollable()->get_hadjustment()->set_value(this->scrollable()->get_hadjustment()->get_value() - amount);
    }


    void Scrollable_impl::scrollRight(double amount)
    {
        this->scrollable()->get_hadjustment()->set_value(this->scrollable()->get_hadjustment()->get_value() + amount);
    }

    void Scrollable_impl::addOnXScroll(const std::function<void(double)>& cb)
    {
        auto _cb = [this, cb]{
            cb(this->scrollable()->get_hadjustment()->get_value());
        };
        this->scrollable()->get_hadjustment()->signal_value_changed().connect(_cb);
    }

    void Scrollable_impl::addOnYScroll(const std::function<void(double)>& cb)
    {
        auto _cb = [this, cb]{
            cb(this->scrollable()->get_vadjustment()->get_value());
        };
        this->scrollable()->get_vadjustment()->signal_value_changed().connect(_cb);
    }

    double Scrollable_impl::scrollX() const
    {
        return this->scrollable()->get_hadjustment()->get_value();
    }

    double Scrollable_impl::scrollY() const
    {
        return this->scrollable()->get_vadjustment()->get_value();
    }
}
