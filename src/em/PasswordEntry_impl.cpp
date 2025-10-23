
#include "./PasswordEntry_impl.h"
#include "../PasswordEntry.h"

namespace ml
{
    PasswordEntry_impl::PasswordEntry_impl(PasswordEntry* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    PasswordEntry_impl::~PasswordEntry_impl()
    {
    }

    void PasswordEntry_impl::_createWidget()
    {
        auto domWidget  = em::createElement("input");
        domWidget.set("type", "password");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "entry");
    }
}
