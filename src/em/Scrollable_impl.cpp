
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

}
