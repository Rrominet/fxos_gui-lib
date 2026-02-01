
#include "./Fixed_impl.h"
#include "../Fixed.h"

namespace ml
{
    Fixed_impl::Fixed_impl(Fixed* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    Fixed_impl::~Fixed_impl()
    {
    }

    void Fixed_impl::_createWidget()
    {
        auto domWidget = em::createElement("fixed");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "fixed");
    }

    void Fixed_impl::append(std::shared_ptr<ml::Widget> child)
    {
        _children.append(child->dom());
        em::append(*_dom, *child->dom());
    }

    void Fixed_impl::remove(ml::Widget* child)
    {
        em::remove(*child->dom());
        _children.remove(child->dom());
    }

    void Fixed_impl::move(ml::Widget* w,double x,double y)
    {
        em::move(*w->dom(),x,y);
    }

    geometry::Point<double> Fixed_impl::widgetPos(ml::Widget* w)
    {
        return em::position(*w->dom());
    }
}
