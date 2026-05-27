#pragma once
#include "./ComposedWidget.h"
#include "./Label.h"

namespace ml
{
    class Box;
    class LabelValue : public ComposedWidget 
    {
        public:
            LabelValue(Box* parent, const std::string& label="", const std::string& value="");
            virtual ~LabelValue() = default;

            void setLabel(const std::string& label){_label->setText(label);}
            void setValue(const std::string& value){_value->setText(value);}

            void addToValue(double value);

        protected : 
            ml::Box* _box;
            ml::Label* _label;
            ml::Label* _value;
    };
}
