
#pragma once
#include "./Input.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/Switch_impl.h"
#else
#include "./gtk/Switch_impl.h"
#endif

namespace ml
{
    class Switch : public Input
    {
        public : 
            Switch();
            virtual ~Switch() = default;
            virtual void init() override;

            std::shared_ptr<ml::Switch_impl> _switch(){return std::static_pointer_cast<Switch_impl>(_impl);}

            virtual void setValue(double value) override {_switch()->setValue(value);}
            bool value(){return _switch()->value();}
            virtual std::any valueAsAny() override {return this->value();}

            virtual void setValue(const std::string& value) override {this->setValue(std::stod(value));}
    };
}
