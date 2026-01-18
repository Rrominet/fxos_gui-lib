#pragma once

//the Input equivalent with a CompoasedWidget
#include "./ComposedWidget.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

template<class T>
    class Color;
namespace ml
{
    class ComposedInput : public ComposedWidget
    {
        public : 
            ComposedInput() : ComposedWidget() {}
            virtual ~ComposedInput() {}
            
            virtual void setValue(const std::string& value) = 0;
            virtual void setValue(double value) = 0;
            virtual std::any valueAsAny() = 0;
            virtual void setValue(const Color<double>& value){}
            virtual void setValue(const json& value){}

            virtual void setRange(double min, double max){}
            virtual void setPrecision(unsigned int precision){}
            virtual void setStep(double step){}
    };
}
