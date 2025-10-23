
#include "./Button_impl.h"
#include "../Button.h"
#include "../EventInfos.h"

namespace ml
{
    Button_impl::Button_impl(Button* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    Button_impl::~Button_impl()
    {
    }

    void Button_impl::_createWidget()
    {
        auto domWidget  = em::createElement("button");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "button");
    }

    void Button_impl::_addOnLeftUp(Event event, const std::function<void(EventInfos&)>& callback)
    {
        auto f = [callback](const emval& dom, const EmscriptenMouseEvent* event)
        {
            lg(event->button);
            if (event->button == 0)
            {
                EventInfos infos;
                infos.x = event->clientX;
                infos.y = event->clientY;
                callback(infos);
                return infos.preventDefault;
            }
            return false;
        };
        em::addEventListener(*_dom, ml::Event::CLICK, f);
    }
}
