
#include "./Spinner_impl.h"
#include "../Spinner.h"

namespace ml
{
    Spinner_impl::Spinner_impl(Spinner* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    Spinner_impl::~Spinner_impl()
    {
    }

    void Spinner_impl::_createWidget()
    {
        auto domWidget = em::createElement("div");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "spinner");
    }
}
