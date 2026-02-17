#pragma once
#include "Color.h"

namespace ml
{
    class ColorProperty : public Property
    {
        public : 
            ColorProperty(const std::string& name, const std::string& description ="", const Color<double>& value={0, 0, 0, 1} ) : Property(name, description, value) {}
            virtual ~ColorProperty() = default;

            virtual bool isColor() const override {return true;}
            Color<double> value() const {return std::any_cast<Color<double>>(_value);}
    };
}
