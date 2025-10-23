
#pragma once
#include "./Input.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/CheckBox_impl.h"
#else
#include "./gtk/CheckBox_impl.h"
#endif

namespace ml
{
    class CheckBox : public Input
    {
        public : 
            CheckBox();
            virtual ~CheckBox() = default;
            virtual void init() override;

            std::shared_ptr<ml::CheckBox_impl> checkBox(){return std::static_pointer_cast<CheckBox_impl>(_impl);}

            void setText(const std::string& text) override {checkBox()->setText(text);}
            std::string text() override {return checkBox()->text();}

            virtual void setValue(double value) override {checkBox()->setValue(value);}
            virtual void setValue(const std::string& value) override {this->setValue(std::stod(value));}
            bool value(){return checkBox()->value();}
            virtual std::any valueAsAny() override { return this->value(); }
    };
}
