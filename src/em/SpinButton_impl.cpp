
#include "./SpinButton_impl.h"
#include "../SpinButton.h"

namespace ml
{
    SpinButton_impl::SpinButton_impl(SpinButton* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    SpinButton_impl::~SpinButton_impl()
    {
    }

    void SpinButton_impl::_createWidget()
    {
        auto domWidget  = em::createElement("input");
        domWidget.set("type", "number");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "spinButton");
    }
}
