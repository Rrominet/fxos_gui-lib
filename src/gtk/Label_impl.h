#pragma once
#include <cassert>
#include <gtkmm/label.h>
#include <memory>
#include "./Widget_impl.h"
#include "../enums.h"

namespace ml
{
    class Label;
    class Label_impl : public Widget_impl
    {
        public:
            Label_impl(Label* abstract);
            virtual ~Label_impl() = default;

            std::shared_ptr<Gtk::Label> label()
            {
                return std::static_pointer_cast<Gtk::Label>(_gtk);
            }
            virtual void _createWidget() override;

            void setText(const std::string& text);
            std::string text();

            virtual void setHAlign(HAlignment align) override;
            void setTextJustify(HAlignment align);
            void setWrap(bool wrap=true);
            void setSelectable(bool sel=true);

            void setEllipsizeMode(EllipsizeMode mode);
            EllipsizeMode ellipsizeMode();

            void setHtml(const std::string& html);
            void setWordWrap(bool wrap);

        private : 
            EllipsizeMode _ellipsizeMode = ELLIPSIZE_NONE;
            bool _wrapBuffer = false;
    };
}
