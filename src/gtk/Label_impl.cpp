#include "./Label_impl.h"
#include "../Label.h"
#include "enums.h"
#include "gtkmm/enums.h"
#include "pangomm/layout.h"

namespace ml
{
    Label_impl::Label_impl(Label* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    void Label_impl::_createWidget()
    {
        lg("Label_impl::_createWidget(gtk)");
        _gtk = std::make_shared<Gtk::Label>();
        lg("Label_impl::_createWidget(gtk) -- doned.");
        lg(_gtk);
    }

    void Label_impl::setText(const std::string& text)
    {
        this->label()->set_text(text);	
    }

    std::string Label_impl::text()
    {
        return this->label()->get_text();	
    }

    void Label_impl::setHAlign(HAlignment align)
    {
        Widget_impl::setHAlign(align);	
        if (align == ml::LEFT)
            this->label()->set_xalign(0);
        else if (align == ml::CENTER)
            this->label()->set_xalign(0.5);
        else if (align == ml::RIGHT)
            this->label()->set_xalign(1);
    }

    void Label_impl::setTextJustify(HAlignment align)
    {
        if (align == ml::LEFT)
            this->label()->set_justify(Gtk::Justification::LEFT);
        else if (align == ml::CENTER)
            this->label()->set_justify(Gtk::Justification::CENTER);
        else if (align == ml::RIGHT)
            this->label()->set_justify(Gtk::Justification::RIGHT);
    }

    void Label_impl::setWrap(bool wrap)
    {
        this->label()->set_wrap(wrap);	
        _wrapBuffer = wrap;
    }

    void Label_impl::setSelectable(bool sel)
    {
        this->label()->set_selectable(sel);
    }

    void Label_impl::setEllipsizeMode(EllipsizeMode mode)
    {
        _ellipsizeMode = mode;
        if (_ellipsizeMode == ELLIPSIZE_NONE)
        {
            this->label()->set_ellipsize(Pango::EllipsizeMode::NONE);
            this->setWrap(_wrapBuffer);
        }
        else if (_ellipsizeMode == ELLIPSIZE_START)
        {
            this->label()->set_ellipsize(Pango::EllipsizeMode::START);
            this->label()->set_wrap(false);
            this->label()->set_max_width_chars(0);
            this->label()->set_width_chars(-1);
        }
        else if (_ellipsizeMode == ELLIPSIZE_MIDDLE)
        {
            this->label()->set_ellipsize(Pango::EllipsizeMode::MIDDLE);
            this->label()->set_wrap(false);
            this->label()->set_max_width_chars(0);
            this->label()->set_width_chars(-1);
        }
        else if (_ellipsizeMode == ELLIPSIZE_END)
        {
            this->label()->set_ellipsize(Pango::EllipsizeMode::END);
            this->label()->set_wrap(false);
            this->label()->set_max_width_chars(0);
            this->label()->set_width_chars(-1);
        }
    }

    EllipsizeMode Label_impl::ellipsizeMode()
    {
        return _ellipsizeMode;
    }

    void Label_impl::setHtml(const std::string& html)
    {
        this->label()->set_markup(html);
    }

    void Label_impl::setWordWrap(bool wrap)
    {
        this->label()->set_wrap(wrap);
    }
}

