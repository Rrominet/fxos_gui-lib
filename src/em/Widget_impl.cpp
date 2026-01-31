
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

    void Widget_impl::clearCssClasses()
    {
        em::clearClasses(*_dom) ;
    }

    void Widget_impl::setCssClasses(const std::vector<std::string>& classes)
    {
        this->clearCssClasses();
        em::addClasses(*_dom, classes); 
    }

    bool Widget_impl::hadCssClass(const std::string& cls)
    {
        return em::containsClasses(*_dom, cls);
    }

    void Widget_impl::addCss(const std::string& css)
    {
        em::addCss(*_dom, css); 
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

    void Widget_impl::setHExpand(bool value)
    {
        //TODO (css class)
    }

    void Widget_impl::setVExpand(bool value)
    {
        //TODO (css class)
    }

    void Widget_impl::setText(const std::string& text)
    {
        _dom->set("innerText", text);
    }

    std::string Widget_impl::text()
    {
        return (*_dom)["innerText"].as<std::string>();
    }

    void Widget_impl::setHtml(const std::string& html)
    {
        _dom->set("innerHTML", html);
    }

    void Widget_impl::setWordWrap(bool wrap)
    {
        //TODO : need to check css attributes on the web
    }

    void Widget_impl::setTextJustify(HAlignment align)
    {
        em::removeClasses(*_dom, "align-left,align-right,align-center,align-fill");
        if (align == LEFT)
            this->addCssClass("align-left");
        else if (align == RIGHT)
            this->addCssClass("align-right");
        else if (align == CENTER)
            this->addCssClass("align-center");
        else if (align == FILL)
            this->addCssClass("align-fill");
    }

    void Widget_impl::setWrap(bool wrap)
    {
        //TODO : need to check css attributes on the web
        //AND need to check the difference with wrap and word wrap in gtk to get a similar behavior
    }

    void Widget_impl::setSelectable(bool sel)
    {
        if (sel)
            this->addCssClass("selectable");
        else 
            this->removeCssClass("selectable");
    }

    void Widget_impl::setEllipsizeMode(EllipsizeMode mode)
    {
        _ellipsizeMpde = mode;
        //TODO in css
    }

    EllipsizeMode Widget_impl::ellipsizeMode() const
    {
        return _ellipsizeMpde;
        //TODO in css
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

    void Widget_impl::setWidth(int w)
    {
        em::setCss(*_dom, "width", std::to_string(w) + "px");
    }

    void Widget_impl::setHeight(int h)
    {
        em::setCss(*_dom, "height", std::to_string(h) + "px");
    }

    void Widget_impl::setSize(int w,int h)
    {
        this->setWidth(w);
        this->setHeight(h);
    }

    int Widget_impl::width() const
    {
        return em::width(*_dom);
    }

    int Widget_impl::height() const
    {
        return em::height(*_dom);
    }

    void Widget_impl::setFocusable(bool value)
    {
        em::setFocusable(*_dom, value); 
    }

    bool Widget_impl::hovered() const
    {
        return em::hovered(*_dom);
    }

    void Widget_impl::setCursor(const std::string& name)
    {
        em::setCss(*_dom, "cursor", name);
    }

    void Widget_impl::focus()
    {
        _dom->call<void>("focus");
    }

    void Widget_impl::setMargins(int left,int top,int right,int bottom)
    {
        em::setCss(*_dom, "margin", std::to_string(left) + "px " + std::to_string(top) + "px " + std::to_string(right) + "px " + std::to_string(bottom) + "px");
    }

    void Widget_impl::setMargins(int margin)
    {
        em::setCss(*_dom, "margin", std::to_string(margin) + "px " + std::to_string(margin) + "px " + std::to_string(margin) + "px " + std::to_string(margin) + "px");
    }

    void Widget_impl::setLeftMargin(int margin)
    {
        em::setCss(*_dom, "margin-left", std::to_string(margin) + "px");
    }

    void Widget_impl::setTopMargin(int margin)
    {
        em::setCss(*_dom, "margin-top", std::to_string(margin) + "px");
    }

    void Widget_impl::setRightMargin(int margin)
    {
        em::setCss(*_dom, "margin-right", std::to_string(margin) + "px");
    }

    void Widget_impl::setBottomMargin(int margin)
    {
        em::setCss(*_dom, "margin-bottom", std::to_string(margin) + "px");
    }

    void Widget_impl::redraw() const
    {
        (*_dom)["offsetHeight"];
    }

    float Widget_impl::fontSize() const
    {
        return em::fontSize(*_dom);
    }

    void Widget_impl::scrollDown(double amount)
    {
        em::scrollBy(*_dom, 0, amount);
    }

    void Widget_impl::scrollUp(double amount)
    {
        em::scrollBy(*_dom, 0, -amount);
    }

    void Widget_impl::scrollLeft(double amount)
    {
        em::scrollBy(*_dom, amount, 0);
    }

    void Widget_impl::scrollRight(double amount)
    {
        em::scrollBy(*_dom, -amount, 0);
    }

    void Widget_impl::addOnXScroll(const std::function<void(double)>& cb)
    {
        //TODO : need to check the event listener in dom
    }

    void Widget_impl::addOnYScroll(const std::function<void(double)>& cb)
    {
        //TODO : need to check the event listener in dom
    }

    double Widget_impl::scrollX() const
    {
        return em::scrollLeft(*_dom);
    }

    double Widget_impl::scrollY() const
    {
        return em::scrollTop(*_dom);
    }
}
