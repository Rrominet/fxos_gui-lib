#include "./Fixed.h"
#include "./App.h"
#include "./ComposedWidget.h"

namespace ml
{
    Fixed::Fixed() : Widget()
    {

    }
    void Fixed::init()
    {
        this->addCssClass("fixed");
    }

    void Fixed::append(std::shared_ptr<ml::Widget> child)
    {
        child->removeWindow();
        child->unparent();
        ml::app()->checker().set("can-set-window", true);
        if (this->hasWindow())
            child->setWindow(this->window());
        ml::app()->checker().set("can-set-window", false);
        this->fixed()->append(child);
        child->setParent(this);
        _children.push_back(child);
    }

    void Fixed::removeChild(std::shared_ptr<ml::Widget> child)
    {
        this->removeChild(child.get());
    }

    void Fixed::removeChild(ml::Widget* child)
    {
        lg("Removing child : " << child);
        this->fixed()->remove(child);
        for (auto& c : _children)
        {
            if (c.get() == child)
            {
                _children.remove(c);
                break;
            }
        }
    }

    void Fixed::removeChild(ml::ComposedWidget* child)
    {
        for (auto w : child->composed())
        {
            std::visit([this](auto& w){
                    if (!w->isComposed())
                    this->removeChild(w);
                    }, w);
        }

        for (auto& c : _composedChildren)
        {
            if (c.get() == child)
            {
                _composedChildren.remove(c);
                break;
            }
        }
    }

    bool Fixed::containsChild(Widget* child)
    {
        bool res = false;
        for (auto &c : _children)
        {
            if (c.get() == child)
            {
                res = true;
                break;
            }
        }
        return res;
    }

    int Fixed::childIndex(ml::Widget* child)
    {
        for (size_t i = 0; i < _children.size(); i++)
        {
            if (_children[i].get() == child)
                return i;
        }
        lg("Warning in Box::childIndex: child not found.");
        return -1;
    }

    void Fixed::clear()
    {
        lg("Fixed::clear");
        lg("Removing " << _children.size() << " children");
        for (size_t i = 0; i < _children.size(); i++)
            this->removeChild(_children[i]);
        _children.clear();
        _composedChildren.clear();
        lg("All children are removed.");
    }

#include "./Widget_creators_impl_fixed_gen.h"
#include "./Container_creators_impl_fixed_gen.h"
}
