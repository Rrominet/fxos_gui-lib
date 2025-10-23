#pragma once
#include "./Input.h"
#include "enums.h"

#ifdef __EMSCRIPTEN__
#include "./em/Label_impl.h"
#else
#include "./gtk/Label_impl.h"
#endif

namespace ml
{
    class Label : public Input
    {
        public : 
            Label();
            virtual ~Label() = default;

            std::shared_ptr<ml::Label_impl> label(){return std::static_pointer_cast<Label_impl>(_impl);}
            virtual void init() override;

            virtual void setText(const std::string& text)override {this->label()->setText(text);}
            virtual std::string text() override{return this->label()->text();}
            std::string value(){return this->label()->text();}

            virtual std::any valueAsAny() override {return this->value();}

            virtual void setValue(double value) override{this->setValue(std::to_string(value));}
            virtual void setValue(const std::string& text) override{this->label()->setText(text);}

            void setWrap(bool wrap=true){this->label()->setWrap(wrap);}
            void setSelectable(bool sel=true){this->label()->setSelectable(sel);}

            void setEllipsizeMode(EllipsizeMode mode);
            EllipsizeMode ellipsizeMode();

            void setHtml(const std::string& html){this->label()->setHtml(html);}
            void setWordWrap(bool wrap){this->label()->setWordWrap(wrap);}

        protected : 
    };
}
