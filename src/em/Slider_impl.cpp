
#include "./Slider_impl.h"
#include "../Slider.h"

namespace ml
{
    Slider_impl::Slider_impl(Slider* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    Slider_impl::~Slider_impl()
    {
    }

    void Slider_impl::_createWidget()
    {
        auto domWidget  = em::createElement("input");
        domWidget.set("type", "range");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "slider");
    }
}
