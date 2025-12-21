
#include "./Fixed_impl.h"
#include "../Fixed.h"

namespace ml
{
    Fixed_impl::Fixed_impl(Fixed* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    Fixed_impl::~Fixed_impl()
    {
    }

    void Fixed_impl::_createWidget()
    {
        auto domWidget = em::createElement("fixed");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "fixed");
    }
}
