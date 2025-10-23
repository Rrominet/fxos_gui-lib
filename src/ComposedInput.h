#pragma once

//the Input equivalent with a CompoasedWidget
#include "./ComposedWidget.h"

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

            virtual void setRange(double min, double max){}
            virtual void setPrecision(unsigned int precision){}
            virtual void setStep(double step){}
    };
}
