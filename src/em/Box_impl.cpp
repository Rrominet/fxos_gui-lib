
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
        
    }

    void Box_impl::setSpacing(int space)
    {
        //TODO : spacing is the px between each child. 
        //Certainly something to implement in css here... Maybe ?
    }

    int Box_impl::spacing() const
    {
        //TODO : Need to save the variable. 
    }
}
