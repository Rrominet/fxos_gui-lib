#include "./Box_impl.h"
#include "../Box.h"

namespace ml
{
    Box_impl::Box_impl(Box* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    void Box_impl::_createWidget()
    {
        lg("Box_impl::_createWidget");
        _gtk = std::make_shared<Gtk::Box>(Gtk::Orientation::VERTICAL);
        _abstract->addCssClass("vertical");
    }

    void Box_impl::setOrient(Orient orient)
    {
        if (orient == Orient::VERTICAL) 
        {
            _abstract->removeCssClass("horizontal");
            _abstract->addCssClass("vertical");
            this->box()->set_orientation(Gtk::Orientation::VERTICAL);
        }
        else
        {
            _abstract->removeCssClass("vertical");
            _abstract->addCssClass("horizontal");
            this->box()->set_orientation(Gtk::Orientation::HORIZONTAL);
        }
    }

    void Box_impl::moveChild(size_t from, size_t to)
    {
        lg("Box_impl::moveChild(" << from << ", " << to << ")");
        if (from == to)
        {
            lg("Warning : Box_impl::moveChild : from == to " << from << " == " << to);
            return;
        }
        if (from>=_children.size())
        {
            lg("Box_impl::moveChild : from > children.size : " << from << " > " << _children.size());
            return;
        }
        if (to>=_children.size())
            to = _children.size()-1;

        auto& widget = *_children[from];	
        if (to == 0)
        {
            lg("Box_impl::moveChild : reorder child at start");
            this->box()->reorder_child_at_start(widget);
        }
        else
        {
            lg("Box_impl::moveChild : reorder child after : " << to );
            this->box()->reorder_child_after(widget, *_children[to]);
        }

        _children.move(from, to);
    }

    void Box_impl::remove(ml::Widget* child)
    {
        lg("Box_impl::remove(" << child << ")");
        lg("removing from gtk box first.");
        this->box()->remove(*child->gtk());
        lg("then from list...");
        _children.remove(child->gtk().get()); 
        lg("child removed and deleted from memory (hopefully.)");
    }
}
