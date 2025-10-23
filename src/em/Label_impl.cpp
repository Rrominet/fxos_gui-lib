#include "./Label_impl.h"
#include "../Label.h"

namespace ml
{
    Label_impl::Label_impl(Label* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    Label_impl::~Label_impl()
    {
    }

    void Label_impl::_createWidget()
    {
        auto domWidget  = em::createElement("label");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "label");
    }
}
