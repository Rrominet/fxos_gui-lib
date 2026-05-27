#include "./LabelValue.h"
#include "./Box.h"
#include "mlMath.h"

#include "./Box.hpp"

namespace ml
{
    LabelValue::LabelValue(Box* parent,const std::string& label,const std::string& value)
    {
        _box = parent->createBox().get()    ;
        _composed.push(_box);
        _box->addCssClass("label-value");
        _box->setOrient(ml::HORIZONTAL);

        _label = _box->createLabel(label + " :").get();
        _label->setHAlign(ml::LEFT);
        _label->addCssClass("label");
        _value = _box->createLabel(value).get();
        _value->setHAlign(ml::RIGHT);
        _value->setHExpand();
        _value->addCssClass("value");
    }

    void LabelValue::addToValue(double value)
    {
        try
        {
            double val = std::stod(_value->text());
            _value->setText(math::round(val + value));
        }
        catch(const std::exception& e)
        {
            ml::app()->error("LabelValue::addToValue() :\nCan't transform " + _value->text() + " to a number.");
        }
    }
}
