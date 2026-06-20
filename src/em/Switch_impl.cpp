
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
        this->addEventListener(ml::Event::CLICK, [this](EventInfos& e)
                {
                this->setValue(!this->value());
                for(auto& callback : _onChange)
                callback(e);
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

    void Switch_impl::_addOnChange(const std::function<void(EventInfos&)>& callback)
    {
        _onChange.push(callback);
    }

    void Switch_impl::setHAlign(HAlignment align)
    {
        if(align == FILL)
        {
            this->addCss("margin-left", "0");
            this->addCss("margin-right", "0");
        }

        else if (align == LEFT)
        {
            this->addCss("text-align", "left");
            this->addCss("margin-left", "0");
            this->addCss("margin-right", "auto");
        }

        else if (align == RIGHT)
        {
            this->addCss("text-align", "right");
            this->addCss("margin-left", "auto");
            this->addCss("margin-right", "0");
        }

        else if (align == CENTER)
        {
            this->addCss("text-align", "center");
            this->addCss("margin-left", "auto");
            this->addCss("margin-right", "auto");
        }
    }

    void Switch_impl::setVAlign(VAlignment align)
    {
        if(align == VFILL)
        {
            this->addCss("margin-top", "0");
            this->addCss("margin-bottom", "0");
        }

        else if (align == TOP)
        {
            this->addCss("margin-top", "0");
            this->addCss("margin-bottom", "auto");
        }

        else if (align == BOTTOM)
        {
            this->addCss("margin-top", "auto");
            this->addCss("margin-bottom", "0");
        }

        else if (align == VCENTER)
        {
            this->addCss("margin-top", "auto");
            this->addCss("margin-bottom", "auto");
        }
    }

}
