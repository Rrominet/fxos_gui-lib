
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

    void Button_impl::_addOnLeftUp(const std::function<void(EventInfos&)>& callback)
    {
        this->addEventListener(ml::Event::CLICK, callback);
    }
}
