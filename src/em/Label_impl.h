#pragma once
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
            virtual ~Label_impl();

            virtual void _createWidget() override;

            void setText(const std::string& text) override { (*_dom).set("innerText", text); }
            std::string text() override { return (*_dom)["innerText"].as<std::string>(); }

            virtual void setHAlign(HAlignment align) override;
            void setTextJustify(HAlignment align);
            void setWrap(bool wrap = true);
            void setSelectable(bool sel = true);
            void setEllipsizeMode(EllipsizeMode mode);
            EllipsizeMode ellipsizeMode();
            void setHtml(const std::string& html);
            void setWordWrap(bool wrap);

        private:
            EllipsizeMode _ellipsizeMode = ELLIPSIZE_NONE;
    };
}
