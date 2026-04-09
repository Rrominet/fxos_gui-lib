
#include "./Scrollable_impl.h"
#include "../Scrollable.h"

namespace ml
{
    Scrollable_impl::Scrollable_impl(Scrollable* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    void Scrollable_impl::_createWidget()
    {
        auto domWidget  = em::createElement("div");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "scrollable");
    }

    void Scrollable_impl::setChild(ml::Widget& child)
    {
        _dom->call<void>("appendChild", *child.dom()); 
    }

    void Scrollable_impl::scrollDown(double amount)
    {
        double current = (*_dom)["scrollTop"].as<double>();
        _dom->set("scrollTop", current + amount);
    }

    void Scrollable_impl::scrollUp(double amount)
    {
        double current = (*_dom)["scrollTop"].as<double>();
        _dom->set("scrollTop", current - amount);
    }

    void Scrollable_impl::scrollLeft(double amount)
    {
        double current = (*_dom)["scrollLeft"].as<double>();
        _dom->set("scrollLeft", current - amount);
    }

    void Scrollable_impl::scrollRight(double amount)
    {
        double current = (*_dom)["scrollLeft"].as<double>();
        _dom->set("scrollLeft", current + amount);
    }

    void Scrollable_impl::addOnXScroll(const std::function<void(double)>& cb)
    {
        em::addEventListener(*_dom, "scroll", [this, cb](emval event) {
            cb((*_dom)["scrollLeft"].as<double>());
        });
    }

    void Scrollable_impl::addOnYScroll(const std::function<void(double)>& cb)
    {
        em::addEventListener(*_dom, "scroll", [this, cb](emval event) {
            cb((*_dom)["scrollTop"].as<double>());
        });
    }

    double Scrollable_impl::scrollX() const
    {
        return (*_dom)["scrollLeft"].as<double>();
    }

    double Scrollable_impl::scrollY() const
    {
        return (*_dom)["scrollTop"].as<double>();
    }
}
