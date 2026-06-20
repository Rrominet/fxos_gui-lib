#include "./Widget_impl.h"
#include "../Widget.h"
#include "./em.h"
#include "../EventInfos.h"

namespace ml
{
    Widget_impl::Widget_impl(Widget* abstract) : _abstract(abstract)
    {
        //FIXME : This doesn't work because if the element is appended in an element that not in the dom yet, it's gonna be true and should be false.
        //See the popover Menu that goes fucked up because of this.
        _abstract->events().add("appended", [this]{this->_onAppended();});
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
        std::string classes_str = str::join(classes, " ");
        em::addClasses(*_dom, classes_str); 
    }


    bool Widget_impl::hadCssClass(const std::string& cls)
    {
        return em::containsClasses(*_dom, cls);
    }

    ml::Ret<> Widget_impl::addCss(const std::string& css)
    {
        auto tmp = str::split(css, ":");
        if(tmp.size() != 2)
            return ml::ret::fail("Invalid CSS : " + css);
        em::setCss(*_dom, tmp[0], tmp[1]);
        return ml::ret::success();
    }

    void Widget_impl::addCss(const std::string& attr, const std::string& value)
    {
        em::setCss(*_dom, attr, value);
    }

    void Widget_impl::show()
    {
        em::show(*_dom);
        _visible = true;

        for (const auto& cb : _onShown)
        {
            EventInfos infos;
            infos.type = SHOWN;
            infos.visible = true;
            cb.callback(infos);
        }
    }

    void Widget_impl::hide()
    {
        em::hide(*_dom);
        _visible = false;
        for (const auto& cb : _onHidden)
        {
            EventInfos infos;
            infos.type = HIDDEN;
            infos.visible = false;
            cb.callback(infos);
        }
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
        if(align == FILL)
        {
            this->addCss("margin-left", "0");
            this->addCss("margin-right", "0");
            this->addCss("width", "stretch");
        }

        else if (align == LEFT)
        {
            this->addCss("text-align", "left");
            this->addCss("margin-left", "0");
            this->addCss("margin-right", "auto");
            this->addCss("width", "initial");
        }

        else if (align == RIGHT)
        {
            this->addCss("text-align", "right");
            this->addCss("margin-left", "auto");
            this->addCss("margin-right", "0");
            this->addCss("width", "initial");
        }

        else if (align == CENTER)
        {
            this->addCss("text-align", "center");
            this->addCss("margin-left", "auto");
            this->addCss("margin-right", "auto");
            this->addCss("width", "initial");
        }
    }

    void Widget_impl::setVAlign(VAlignment align)
    {
        if(align == VFILL)
        {
            this->addCss("margin-top", "0");
            this->addCss("margin-bottom", "0");
            this->addCss("height", "stretch");
        }

        else if (align == TOP)
        {
            this->addCss("margin-top", "0");
            this->addCss("margin-bottom", "auto");
            this->addCss("height", "initial");
        }

        else if (align == BOTTOM)
        {
            this->addCss("margin-top", "auto");
            this->addCss("margin-bottom", "0");
            this->addCss("height", "initial");
        }

        else if (align == VCENTER)
        {
            this->addCss("margin-top", "auto");
            this->addCss("margin-bottom", "auto");
            this->addCss("height", "initial");
        }
    }

    void Widget_impl::setHExpand(bool value)
    {
        //TODO (css class)
        lg("Widget_impl::setHExpand not implemented in emscripten");
    }

    void Widget_impl::setVExpand(bool value)
    {
        //TODO (css class)
        lg("Widget_impl::setVExpand not implemented in emscripten");
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
        if (wrap)
            em::setCss(*_dom, "word-wrap", "break-word");
        else
            em::setCss(*_dom, "word-wrap", "normal");
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
        em::removeClasses(*_dom, "ellipsize-start,ellipsize-middle,ellipsize-end");
        if (mode == ELLIPSIZE_START)
            this->addCssClass("ellipsize-start");
        else if (mode == ELLIPSIZE_MIDDLE)
            this->addCssClass("ellipsize-middle");
        else if (mode == ELLIPSIZE_END)
            this->addCssClass("ellipsize-end");
    }

    EllipsizeMode Widget_impl::ellipsizeMode() const
    {
        return _ellipsizeMpde;
    }

    void Widget_impl::setHelp(const std::string& help)
    {
        _dom->set("title", help);
    }

    std::string Widget_impl::help()
    {
        return (*_dom)["title"].as<std::string>();
    }

    void Widget_impl::_createBasicEvents()
    {
        this->addEventListener(MOUSE_ENTER, [this](EventInfos&){ _hovered = true; });
        this->addEventListener(MOUSE_LEAVE, [this](EventInfos&){ _hovered = false; });
    }

    geometry::Point<double> Widget_impl::position() const
    {
        double x = em::x(*_dom);
        double y = em::y(*_dom);
        return geometry::Point<double>(x, y);
    }

    bool Widget_impl::isEditable() const
    {
        std::string tag = (*_dom)["tagName"].as<std::string>();
        return (tag == "INPUT" || tag == "TEXTAREA");
    }

    bool Widget_impl::isOnelineEditable() const
    {
        std::string tag = (*_dom)["tagName"].as<std::string>();
        return (tag == "INPUT");
    }

    bool Widget_impl::isMultilineEditable() const
    {
        std::string tag = (*_dom)["tagName"].as<std::string>();
        return (tag == "TEXTAREA");
    }

    bool Widget_impl::focused() const
    {
        emval active = em::dom()["activeElement"];
        return (*_dom == active);
    }

    bool Widget_impl::containsFocus() const
    {
        return _dom->call<bool>("contains", em::dom()["activeElement"]);
    }

    void Widget_impl::enable()
    {
        _enabled = true;
        _dom->set("disabled", false);
        this->removeCssClass("disabled");
    }

    void Widget_impl::disable()
    {
        _enabled = false;
        _dom->set("disabled", true);
        this->addCssClass("disabled");
    }

    bool Widget_impl::enabled() const
    {
        return _enabled;
    }

    void Widget_impl::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        lg("Widget_impl::addEventListener(" << event << ", " << &callback << ") : ID -> " << this->id());
        EventCallback ec;
        ec.event.type = event;
        ec.callback = callback;

        if (event == ml::Event::CLICK ||
                event == ml::Event::DOUBLE_CLICK || 
                event == ml::Event::MOUSE_DOWN ||
                event == ml::Event::MOUSE_UP ||
                event == ml::Event::LEFT_DOWN ||
                event == ml::Event::RIGHT_UP ||
                event == ml::Event::RIGHT_DOWN || 
                event == ml::Event::MIDDLE_UP ||
                event == ml::Event::MIDDLE_DOWN || 
                event == ml::Event::MOUSE_MOVE ||
                event == ml::Event::MOUSE_ENTER ||
                event == ml::Event::MOUSE_LEAVE || 
                event == ml::Event::WHEEL)
        {
            lg("Event pused as EventCallback in Widget_impl::_onMouseEvent) : ID -> " << this->id());
            _onMouseEvent.push(ec);
        }

        //necessary for the Button_impl override because of how works the button elmt in the dom.
        else if (event == ml::Event::LEFT_UP)
            _addOnLeftUp(callback);

        else if (event == ml::Event::KEY_DOWN || event == ml::Event::KEY_UP)
        {
            lg("Event pused as EventCallback in Widget_impl::_onKeyEvent : ID -> " << this->id());
            _onKeyEvent.push(ec);
        }

        else if (event == ml::Event::SHOWN)
        {
            lg("Event pused as EventCallback in Widget_impl::_onShownEvent : ID -> " << this->id());
            _onShown.push(ec);
        }

        else if (event == ml::Event::HIDDEN)
        {
            lg("Event pused as EventCallback in Widget_impl::_onHiddenEvent : ID -> " << this->id());
            _onHidden.push(ec);
        }

        else if (event == ml::Event::RESIZE)
        {
            lg("Event pused as EventCallback in Widget_impl::_onResizeEvent : ID -> " << this->id());
            _onResize.push(ec);
        }

        else if (event == ml::Event::FOCUS || 
                event == ml::Event::UNFOCUS || 
                event == ml::Event::VALID)
        {
            lg("Event pused as EventCallback in Widget_impl::_onGeneralEvent : ID -> " << this->id());
            _onGeneralEvents.push(ec);
        }

        //necessary for the Swicth_impl and ToggleButton_impl override.
        else if (event == ml::Event::CHANGE)
            _addOnChange(callback);

        if (_wasOneTimeInDom)
        {
            lg("_wasOneTimeInDom == true, so calling _addEventToDOMElement() directly : ID -> " << this->id());
            _addEventToDOMElement();
        }
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
        em::scrollBy(*_dom, -amount, 0);
    }

    void Widget_impl::scrollRight(double amount)
    {
        em::scrollBy(*_dom, amount, 0);
    }

    void Widget_impl::addOnXScroll(const std::function<void(double)>& cb)
    {
        //TODO : 
        //To implement
        lg("Widget_impl::addOnXScroll not implemented");
    }

    void Widget_impl::addOnYScroll(const std::function<void(double)>& cb)
    {
        //TODO : 
        //To implement
        lg("Widget_impl::addOnYScroll not implemented");
    }

    double Widget_impl::scrollX() const
    {
        return em::scrollLeft(*_dom);
    }

    double Widget_impl::scrollY() const
    {
        return em::scrollTop(*_dom);
    }

    geometry::Point<double> Widget_impl::computedPosition(ml::Widget* coordonatesSrc) const
    {
        //TODO :         
        lg("Widget_impl::computedPosition not implemented");
        return geometry::Point<double>(0, 0);
    }

    void Widget_impl::setOverflow(Overflow overflow)
    {
        if (overflow == OVERFLOW_HIDDEN)
        {
            em::setCss(*_dom, "overflow-x", "hidden");
            em::setCss(*_dom, "overflow-y", "hidden");
        }
        else if (overflow == OVERFLOW_VISIBLE)
        {
            em::setCss(*_dom, "overflow-x", "auto");
            em::setCss(*_dom, "overflow-y", "auto");
        }
    }

    void Widget_impl::_onAppended()
    {
        lg("Widget_impl::_onAppended : ID -> " << this->id());
        if (_wasOneTimeInDom)        
        {
            lg("Widget_impl::_onAppended : already in dom");
            lg("abort appended event.");
            return;
        }

        if (em::isInDom(*_dom))
        {
            _wasOneTimeInDom = true;
            _addEventToDOMElement();
        }
    }

    void Widget_impl::_addMouseEvent(bool clear)
    {
        lg("Widget_impl::_addMouseEvent(" << clear << ") : ID -> " << this->id());
        lg("Adding " << _onMouseEvent.size() << " mouse events");
        for (auto& cb : _onMouseEvent)
        {
            auto mouse_cb = [cb](const emval& dom, const EmscriptenMouseEvent* event) mutable
            {
                cb.event.x = event->clientX;
                cb.event.y = event->clientY;
                cb.callback(cb.event);
                return cb.event.preventDefault;
            };

            em::addEventListener(*_dom, cb.event.type, mouse_cb);
        }

        if (clear)
        {
            lg("clear == true, clearing _onMouseEvent");
            _onMouseEvent.clear();
        }
    }

    void Widget_impl::_addKeyEvent(bool clear)
    {
        lg("Widget_impl::_addKeyEvent(" << clear << ") : ID -> " << this->id());
        lg("Adding " << _onKeyEvent.size() << " key events");
        for (auto& cb : _onKeyEvent)
        {
            auto key_cb = [cb](const emval& dom, const EmscriptenKeyboardEvent* event) mutable
            {
                cb.event.key = event->key;
                cb.callback(cb.event);
                return cb.event.preventDefault;
            };

            em::addEventListener(*_dom, cb.event.type, key_cb);
        }

        if (clear)
            _onKeyEvent.clear();
    }

    void Widget_impl::_addResizeEvent(bool clear)
    {
        //TODO !
        lg("Warning : _addResizeEvent not implemented yet.");
//         for (auto& cb : _onResize)
//         {
//             auto f = [cb, this](const emval& dom, const EmscriptenUiEvent* event)
//             {
//                 EventInfos infos;
//                 infos.type = cb.event.type;
//                 infos.width = em::width(*_dom);
//                 infos.height = em::height(*_dom);
//                 if (_oldWidth == infos.width && _oldHeight == infos.height)
//                     return;
//                 infos.visible = _visible;
//                 cb.callback(infos);
//                 _oldWidth = infos.width;
//                 _oldHeight = infos.height;
//             };
//             em::addEventListener(*_dom, cb.event.type, f);
//         }
// 
//         if (clear) _onResize.clear();
    }

    void Widget_impl::_addGeneralEvent(bool clear)
    {
        lg("Widget_impl::_addGeneralEvent(" << clear << ") : ID -> " << this->id());
        for (auto & ec : _onGeneralEvents)
        {
            auto f = [ec]() mutable
            {
                ec.callback(ec.event);
                return false;
            };
            em::addEventListener(*_dom, ec.event.type, f);
        }

        if (clear) _onGeneralEvents.clear();
    }

    void Widget_impl::_addOnChange(const std::function<void(EventInfos&)>& callback)
    {
        lg("Widget_impl::addOnChange) : ID -> " << this->id());
        EventCallback ec;
        ec.event.type = ml::Event::CHANGE;
        ec.callback = callback;
        lg("EventCall back pused in Widget_impl::_onGeneralEvents");
        _onGeneralEvents.push(ec);
    }

    void Widget_impl::_addOnLeftUp(const std::function<void(EventInfos&)>& callback)
    {
        lg("Widget_impl::_addOnLeftUp) : ID -> " << this->id());
        EventCallback ec;
        ec.event.type = ml::Event::LEFT_UP;
        ec.callback = callback;

        lg("EventCall back pused in Widget_impl::_onMouseEvent");
        _onMouseEvent.push(ec);
    }

    void Widget_impl::_addEventToDOMElement(bool clear)
    {
        lg("Widget_impl::_addEventToDOMElement(" << clear << ") : ID -> " << this->id());
        _addMouseEvent(clear);
        _addKeyEvent(clear);
        _addResizeEvent(clear);
        _addGeneralEvent(clear);
    }

    std::string Widget_impl::id() const
    {
        auto& dom = *_dom;
        return dom["id"].as<std::string>();
    }
}
