
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
}
