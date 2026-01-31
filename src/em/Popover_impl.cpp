
#include "./Popover_impl.h"
#include "../Popover.h"

namespace ml
{
    Popover_impl::Popover_impl(Popover* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    Popover_impl::~Popover_impl()
    {
    }

    void Popover_impl::_createWidget()
    {
        auto domWidget = em::createElement("popover");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "popover");
    }

    void Popover_impl::setPosition(float x,float y)
    {
        em::setCss(*_dom, "left", std::to_string(x) + "px");
        em::setCss(*_dom, "top", std::to_string(y) + "px");
    }

    void Popover_impl::setAutoHide(bool v)
    {
        //TODO : need to check the behavior in GTK to copy it in the dom 
    }
}
