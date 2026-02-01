
#include "./Box_impl.h"
#include "../Box.h"
#include "./em.h"
#include "../Window.h"
#include "./Window_impl.h"

namespace ml
{
    Box_impl::Box_impl(Box* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    void Box_impl::_createWidget()
    {
        _dom  = std::make_shared<emval>(em::createElement("div"));
        (*_dom)["classList"].call<void, std::string>("add", "box");
        (*_dom)["classList"].call<void, std::string>("add", "vertical");
    }

    void Box_impl::setOrient(Orient orient)
    {
        if (orient == Orient::VERTICAL) 
        {
            _abstract->removeCssClass("horizontal");
            _abstract->addCssClass("vertical");
        }
        else
        {
            _abstract->removeCssClass("vertical");
            _abstract->addCssClass("horizontal");
        }
    }

    void Box_impl::append(std::shared_ptr<ml::Widget> child)
    {
        _dom->call<void, emval&>("appendChild", *child->dom());
        _abstract->window()->impl()->setMainHeight();
    }

    void Box_impl::prepend(std::shared_ptr<ml::Widget> child)
    {
        _dom->call<void, emval&>("prepend", *child->dom());
        _abstract->window()->impl()->setMainHeight();
    }

    void Box_impl::remove(ml::Widget* child)
    {
        em::remove(*child->dom());
        _abstract->window()->impl()->setMainHeight();
    }

    void Box_impl::moveChild(size_t from,size_t to)
    {
        if (from == to) return;
        
        emval children = (*_dom)["children"];
        int childCount = children["length"].as<int>();
        
        if (from >= childCount || to >= childCount) return;
        
        emval childToMove = children[from];
        
        if (to >= childCount - 1)
        {
            _dom->call<void, emval&>("appendChild", childToMove);
        }
        else
        {
            emval referenceChild = children[to > from ? to + 1 : to];
            _dom->call<void, emval&, emval&>("insertBefore", childToMove, referenceChild);
        }
        
        _abstract->window()->impl()->setMainHeight();
    }

    void Box_impl::setSpacing(int space)
    {
        _spacing = space;
        (*_dom)["style"].set("gap", std::to_string(space) + "px");
    }

    int Box_impl::spacing() const
    {
        return _spacing;
    }
}
