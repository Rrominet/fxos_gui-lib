#include "./MultilineEntry_impl.h"

namespace ml
{
    MultilineEntry_impl::MultilineEntry_impl(MultilineEntry* abstract) : Widget_impl((Widget*)abstract)
    {

    }

    void MultilineEntry_impl::_createWidget()
    {
        auto domWidget = em::createElement("textarea");
        _dom = std::make_shared<emval>(domWidget);
    }

    std::string MultilineEntry_impl::value()
    {
        return (*_dom)["value"].as<std::string>();
    }

    void MultilineEntry_impl::setValue(const std::string& value)
    {
        _dom->set("value", value);
    }

    std::string MultilineEntry_impl::placeholder()
    {
        return (*_dom)["placeholder"].as<std::string>();
    }

    void MultilineEntry_impl::setPlaceholder(const std::string& placeholder)
    {
        _dom->set("placeholder", placeholder);
        this->setHelp(placeholder);
    }
}
