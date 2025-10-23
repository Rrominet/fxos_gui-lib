
#include "./Canvas_impl.h"
#include "../Canvas.h"

namespace ml
{
    Canvas_impl::Canvas_impl(Canvas* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    Canvas_impl::~Canvas_impl()
    {
    }

    void Canvas_impl::_createWidget()
    {
        auto domWidget = em::createElement("canvas");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "canvas");
    }
}
