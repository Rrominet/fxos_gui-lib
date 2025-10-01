
#include "./ToggleButton_impl.h"
#include "../ToggleButton.h"
#include "em/em.h"
#include "../EventInfos.h"

namespace ml
{
    ToggleButton_impl::ToggleButton_impl(ToggleButton* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    void ToggleButton_impl::_createWidget()
    {
        auto domWidget  = em::createElement("button");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "button");
        (*_dom)["classList"].call<void, std::string>("add", "toggleButton");
    }

    void ToggleButton_impl::setEvents()
    {
        em::addEventListener(*_dom, ml::Event::CLICK, [this](const emval& dom, const EmscriptenMouseEvent* event)
                {
                    this->setValue(!this->value());
                    if (_onChange)
                    {
                        EventInfos e;
                        _onChange(e);
                    }
                    return true;
                }
                );
    }

    void ToggleButton_impl::setValue(bool value)
    {
        if (value)
            em::addClasses(*_dom, "active");
        else
            em::removeClasses(*_dom, "active");
    }

    bool ToggleButton_impl::value()
    {
        return em::containsClasses(*_dom, "active"); 
    }

    void ToggleButton_impl::_addOnChange(Event event, const std::function<void(EventInfos&)>& callback)
    {
        _onChange = callback;
    }

}
