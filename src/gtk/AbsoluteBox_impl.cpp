#include "./AbsoluteBox_impl.h"
#include "../Widget.h"

namespace ml
{
    AbsoluteBox_impl::AbsoluteBox_impl(AbsoluteBox* abstract) : Widget_impl((Widget*)abstract)
    {

    }

    void AbsoluteBox_impl::_createWidget()
    {
        lg("AbsoluteBox_impl::_createWidget");
        _gtk = std::make_shared<Gtk::Overlay>();
    }

    void AbsoluteBox_impl::append(std::shared_ptr<ml::Widget> c)
    {
        c->setHAlign(LEFT);
        c->setVAlign(TOP);
        if (!this->overlay()->get_child())
            this->overlay()->set_child(*c->gtk());
        else 
            this->overlay()->add_overlay(*c->gtk());
        _children.append(c->gtk().get());
    }

    void AbsoluteBox_impl::prepend(std::shared_ptr<ml::Widget> c)
    {
        c->setHAlign(LEFT);
        c->setVAlign(TOP);
        
        // Remove all overlays temporarily
        std::vector<Gtk::Widget*> temp_children;
        for (auto child : _children)
        {
            temp_children.push_back(child);
            this->overlay()->remove_overlay(*child);
        }
        
        // Set new widget as first overlay
        if (!this->overlay()->get_child())
            this->overlay()->set_child(*c->gtk());
        else
            this->overlay()->add_overlay(*c->gtk());
        
        // Re-add all previous overlays
        for (auto child : temp_children)
        {
            this->overlay()->add_overlay(*child);
        }
        
        // Prepend to children list
        _children.prepend(c->gtk().get());
    }

    void AbsoluteBox_impl::remove(ml::Widget* c)
    {
        if (this->overlay()->get_child() == c->gtk().get())
            this->overlay()->unset_child();
        else 
            _children.remove(c->gtk().get());
        this->overlay()->remove_overlay(*c->gtk());
    }

    void AbsoluteBox_impl::setBackground(std::shared_ptr<ml::Widget> c)
    {
        this->overlay()->set_child(*c->gtk());
    }

    void AbsoluteBox_impl::setBackground(ml::Widget* c)
    {
        this->overlay()->set_child(*c->gtk());
    }

    void AbsoluteBox_impl::removeBackground()
    {
        this->overlay()->unset_child();
    }

    void AbsoluteBox_impl::sendToFront(ml::Widget* c)
    {
        this->moveDepth(c, 0);
    }

    void AbsoluteBox_impl::sendToBack(ml::Widget* c)
    {
        this->moveDepth(c, _children.size()-1);
    }

    void AbsoluteBox_impl::moveDepth(ml::Widget* c,unsigned int x)
    {
        if (x > _children.size() - 1)
            x = _children.size() - 1;

        for (auto c : _children)
            this->overlay()->remove_overlay(*c);

        _children.setPosition(c->gtk().get(), x);

        for (auto c : _children)
            this->overlay()->add_overlay(*c);
    }
}
