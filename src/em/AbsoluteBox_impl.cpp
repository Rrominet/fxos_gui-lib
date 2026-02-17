#include "./AbsoluteBox_impl.h"
#include "../Widget.h"
#include "em/em.h"

namespace ml
{
    AbsoluteBox_impl::AbsoluteBox_impl(Box* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    void AbsoluteBox_impl::_createWidget()
    {
        _dom  = std::make_shared<emval>(em::createElement("div"));
        (*_dom)["classList"].call<void, std::string>("add", "overlay");
    }

    void AbsoluteBox_impl::append(std::shared_ptr<ml::Widget> c)
    {
        _children.append(c->dom());  
        em::append(*_dom, *c->dom());
        *(c->dom())["classList"].call<void, std::string>("add", "overlay-child");
    }

    void AbsoluteBox_impl::prepend(std::shared_ptr<ml::Widget> c)
    {
        _children.prepend(c->dom());
        em::prepend(*_dom, *c->dom());
        *(c->dom())["classList"].call<void, std::string>("add", "overlay-child");
    }

    void AbsoluteBox_impl::remove(ml::Widget* c)
    {
        em::remove(*c->dom());
    }

    void AbsoluteBox_impl::setBackground(std::shared_ptr<ml::Widget> c)
    {
        if (_background)
            em::remove(*_background);
        _background = c->dom();
        em::addClasses(*_background, "overlay-background");
    }

    void AbsoluteBox_impl::setBackground(ml::Widget* c)
    {
        this->setBackground(std::shared_ptr<ml::Widget>(c));
    }

    void AbsoluteBox_impl::removeBackground()
    {
        if (_background)
            em::remove(*_background);
        _background.reset();
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
        auto dom = c->dom();
        int currentIndex = -1;
        for (auto i = 0; i < _children.size(); i++)
        {
            if (_children[i].get() == dom.get())
            {
                currentIndex = i;
                break;
            }
        }

        if (currentIndex == -1)
            return;
        
        if (x >= _children.size())
            x = _children.size() - 1;
        
        if (currentIndex == x)
            return;
        
        _children.remove(dom);
        _children.insert(x, dom);
        
        em::remove(*dom);
        if (x == 0)
        {
            em::prepend(*_dom, *dom);
        }
        else
        {
            auto refChild = _children[x - 1];
            em::insertAfter(*_dom, *dom, *refChild);
        }
    }
}
