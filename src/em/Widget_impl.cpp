
#include "./Widget_impl.h"
#include "../Widget.h"
#include "./em.h"
#include "../EventInfos.h"

namespace ml
{
    Widget_impl::Widget_impl(Widget* abstract) : _abstract(abstract)
    {
    }

    void Widget_impl::addCssClass(const std::string& cls)
    {
        (*_dom)["classList"].call<void>("add", cls);
    }

    void Widget_impl::removeCssClass(const std::string& cls)
    {
        (*_dom)["classList"].call<void>("remove", cls);
    }

    void Widget_impl::show()
    {
        em::show(*_dom);
        _visible = true;
    }

    void Widget_impl::hide()
    {
        em::hide(*_dom);
        _visible = false;
    }

    bool Widget_impl::isVisible()
    {
        return _visible;
    }

    void Widget_impl::remove()
    {
        em::remove(*_dom); 
    }

    void Widget_impl::setHAlign(HAlignment align)
    {
        //TODO (css class)
    }

    void Widget_impl::setVAlign(VAlignment align)
    {
        //TODO (css class)
    }

    void Widget_impl::setText(const std::string& text)
    {
        _dom->set("innerText", text);
    }

    std::string Widget_impl::text()
    {
        return (*_dom)["innerHTML"].as<std::string>();
    }

    void Widget_impl::setHelp(const std::string& help)
    {
        _dom->set("title", help);
    }

    std::string Widget_impl::help()
    {
        return (*_dom)["title"].as<std::string>();
    }

    void Widget_impl::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        if (event == ml::Event::CLICK || 
            event == ml::Event::DOUBLE_CLICK || 
            event == ml::Event::MOUSE_DOWN ||
            event == ml::Event::MOUSE_UP ||
            event == ml::Event::MOUSE_MOVE ||
            event == ml::Event::MOUSE_ENTER ||
            event == ml::Event::MOUSE_LEAVE)
        {
            auto f = [callback](const emval& dom, const EmscriptenMouseEvent* event)
            {
                EventInfos infos;
                infos.x = event->clientX;
                infos.y = event->clientY;
                callback(infos);
                return infos.preventDefault;
            };
            em::addEventListener(*_dom, event, f);
        }

        else if (event == ml::Event::LEFT_DOWN)
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
            em::addEventListener(*_dom, ml::Event::MOUSE_DOWN, f);
        }

        else if (event == ml::Event::RIGHT_DOWN)
        {
            auto f = [callback](const emval& dom, const EmscriptenMouseEvent* event)
            {
                if (event->button == 2)
                {
                    EventInfos infos;
                    infos.x = event->clientX;
                    infos.y = event->clientY;
                    callback(infos);
                    return infos.preventDefault;
                }
                return false;
            };
            em::addEventListener(*_dom, ml::Event::MOUSE_DOWN, f);
        }

        else if (event == ml::Event::MIDDLE_DOWN)
        {
            auto f = [callback](const emval& dom, const EmscriptenMouseEvent* event)
            {
                if (event->button == 1)
                {
                    EventInfos infos;
                    infos.x = event->clientX;
                    infos.y = event->clientY;
                    callback(infos);
                    return infos.preventDefault;
                }
                return false;
            };
            em::addEventListener(*_dom, ml::Event::MOUSE_DOWN, f);
        }

        else if (event == ml::Event::LEFT_UP)
            _addOnLeftUp(event, callback);

        else if (event == ml::Event::RIGHT_UP)
        {
            auto f = [callback](const emval& dom, const EmscriptenMouseEvent* event)
            {
                if (event->button == 2)
                {
                    EventInfos infos;
                    infos.x = event->clientX;
                    infos.y = event->clientY;
                    callback(infos);
                    return infos.preventDefault;
                }
                return false;
            };
            em::addEventListener(*_dom, ml::Event::MOUSE_UP, f);
        }

        else if (event == ml::Event::MIDDLE_UP)
        {
            auto f = [callback](const emval& dom, const EmscriptenMouseEvent* event)
            {
                if (event->button == 1)
                {
                    EventInfos infos;
                    infos.x = event->clientX;
                    infos.y = event->clientY;
                    callback(infos);
                    return infos.preventDefault;
                }
                return false;
            };
            em::addEventListener(*_dom, ml::Event::MOUSE_UP, f);
        }

        else if (event == ml::Event::KEY_DOWN)
        {
            auto f = [callback](const emval& dom, const EmscriptenKeyboardEvent* event)
            {
                EventInfos infos;
                infos.key = event->key;
                callback(infos);
                return infos.preventDefault;
            };
            em::addEventListener(*_dom, ml::Event::KEY_DOWN, f);
        }

        else if (event == ml::Event::KEY_UP)
        {
            auto f = [callback](const emval& dom, const EmscriptenKeyboardEvent* event)
            {
                EventInfos infos;
                infos.key = event->key;
                callback(infos);
                return infos.preventDefault;
            };
            em::addEventListener(*_dom, ml::Event::KEY_UP, f);
        }

        else if (event == ml::Event::CHANGE)
            _addOnChange(event, callback);

        else if (event == ml::Event::VALID)
        {
            auto f = [callback]()
            {
                EventInfos infos;
                callback(infos);
            };
            em::addEventListener(*_dom, ml::Event::VALID, f);
        }
    }

    void Widget_impl::_addOnLeftUp(Event event, const std::function<void(EventInfos&)>& callback)
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
        em::addEventListener(*_dom, ml::Event::MOUSE_UP, f);
    }

    void Widget_impl::_addOnChange(Event event, const std::function<void(EventInfos&)>& callback)
    {
        auto f = [callback]()
        {
            EventInfos infos;
            callback(infos);
        };
        em::addEventListener(*_dom, ml::Event::CHANGE, f);
    }
}
