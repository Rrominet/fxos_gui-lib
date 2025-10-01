#pragma once
#include "./Widget.h"

//represent all the widget that can call setValue(...)
//logicly all the widget that can have a value written in them by the user (+ Label)

namespace ml
{
    class Input : public Widget 
    {
        public : 
            Input() : Widget() {}
            virtual ~Input(){}

            virtual void setValue(const std::string& value) = 0;
            virtual void setValue(double value) = 0;
            virtual std::any valueAsAny() = 0;

            virtual void setRange(double min, double max){}
            virtual void setPrecision(unsigned int precision){}
            virtual void setStep(double step){}
    };
}
