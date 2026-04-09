#include "./Label_impl.h"
#include "../Label.h"

namespace ml
{
    Label_impl::Label_impl(Label* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    Label_impl::~Label_impl()
    {
    }

    void Label_impl::_createWidget()
    {
        auto domWidget  = em::createElement("label");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "label");
    }

    void Label_impl::setHAlign(HAlignment align)
    {
        Widget_impl::setHAlign(align);
        if (align == ml::LEFT)
            em::setCss(*_dom, "text-align", "left");
        else if (align == ml::CENTER)
            em::setCss(*_dom, "text-align", "center");
        else if (align == ml::RIGHT)
            em::setCss(*_dom, "text-align", "right");
        else if (align == ml::FILL)
            em::setCss(*_dom, "text-align", "justify");
    }

    void Label_impl::setTextJustify(HAlignment align)
    {
        if (align == ml::LEFT)
            em::setCss(*_dom, "text-align", "left");
        else if (align == ml::CENTER)
            em::setCss(*_dom, "text-align", "center");
        else if (align == ml::RIGHT)
            em::setCss(*_dom, "text-align", "right");
        else if (align == ml::FILL)
            em::setCss(*_dom, "text-align", "justify");
    }

    void Label_impl::setWrap(bool wrap)
    {
        if (wrap)
            em::setCss(*_dom, "white-space", "normal");
        else
            em::setCss(*_dom, "white-space", "nowrap");
    }

    void Label_impl::setSelectable(bool sel)
    {
        if (sel)
            em::setCss(*_dom, "user-select", "text");
        else
            em::setCss(*_dom, "user-select", "none");
    }

    void Label_impl::setEllipsizeMode(EllipsizeMode mode)
    {
        _ellipsizeMode = mode;
        if (mode == ELLIPSIZE_NONE)
        {
            em::setCss(*_dom, "overflow", "visible");
            em::setCss(*_dom, "text-overflow", "clip");
            em::setCss(*_dom, "white-space", "normal");
        }
        else
        {
            em::setCss(*_dom, "overflow", "hidden");
            em::setCss(*_dom, "white-space", "nowrap");
            em::setCss(*_dom, "text-overflow", "ellipsis");
        }
    }

    EllipsizeMode Label_impl::ellipsizeMode()
    {
        return _ellipsizeMode;
    }

    void Label_impl::setHtml(const std::string& html)
    {
        (*_dom).set("innerHTML", html);
    }

    void Label_impl::setWordWrap(bool wrap)
    {
        this->setWrap(wrap);
    }
}
