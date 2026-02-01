
#include "./Fixed_impl.h"
#include "../Fixed.h"

namespace ml
{
    Fixed_impl::Fixed_impl(Fixed* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    void Fixed_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::Fixed>();
        this->addCssClass("fixed");
        // implement sepecific stuff here if necessecary.
    }

    void Fixed_impl::append(std::shared_ptr<ml::Widget> child)
    {
        _children.append(child->gtk().get());
        this->fixed()->put(*child->gtk(),0,0);
    }

    void Fixed_impl::remove(ml::Widget* child)
    {
        this->fixed()->remove(*child->gtk());
        _children.remove(child->gtk().get());
    }

    void Fixed_impl::move(ml::Widget* w,double x,double y)
    {
        this->fixed()->move(*w->gtk(),x,y);
    }

    geometry::Point<double> Fixed_impl::widgetPos(ml::Widget* w)
    {
        geometry::Point<double> _r;
        this->fixed()->get_child_position(*w->gtk(), _r.x, _r.y);
        return _r;
    }
}
