
#include "./Switch_impl.h"
#include "../Switch.h"
#include "em/em.h"
#include "../EventInfos.h"

namespace ml
{
    Switch_impl::Switch_impl(Switch* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    Switch_impl::~Switch_impl()
    {
    }

    void Switch_impl::_createWidget()
    {
        auto domWidget  = em::createElement("div");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "switch");

        _switchButton = std::make_shared<emval>(em::newNode(*_dom, "div", "", "switchButton"));
    }

    void Switch_impl::setEvents()
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

    void Switch_impl::setValue(bool value)
    {
        if (value)
            em::addClasses(*_dom, "active");
        else
            em::removeClasses(*_dom, "active");
    }

    bool Switch_impl::value()
    {

        return em::containsClasses(*_dom, "active"); 
    }

    void Switch_impl::_addOnChange(Event event, const std::function<void(EventInfos&)>& callback)
    {
        _onChange = callback;
    }

}
