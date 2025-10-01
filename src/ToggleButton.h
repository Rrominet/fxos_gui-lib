
#pragma once
#include "./Input.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/ToggleButton_impl.h"
#else
#include "./gtk/ToggleButton_impl.h"
#endif

namespace ml
{
    class ToggleButton : public Input
    {
        public : 
            ToggleButton();
            virtual ~ToggleButton() = default;
            virtual void init() override;

            std::shared_ptr<ml::ToggleButton_impl> toggleButton(){return std::static_pointer_cast<ToggleButton_impl>(_impl);}

            void setText(const std::string& text) override {toggleButton()->setText(text);}
            std::string text() override {return toggleButton()->text();}

            bool value(){return toggleButton()->value();}
            virtual std::any valueAsAny() override { return this->value(); }

            virtual void setValue(double value) override {toggleButton()->setValue(value);}
            virtual void setValue(const std::string& value) override {this->setValue(std::stod(value));}
    };
}
