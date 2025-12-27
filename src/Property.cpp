#include "./Property.h"
#include "./props_utils.h"

#include "./Box.h"
#include "./Box.hpp"
namespace ml
{
    void Property::set(const std::any& value, Observer* observer , bool preventUpdate )
    {
        lg("Property::set(" << props::valueAsString(value) << ")");
        if (this->type() == STRING)
            _value = value;

        else if (this->type() == BOOL)
        {
            if (value.type() == typeid(bool))
                _value = value;
            else
                _value = std::any((bool)std::any_cast<double>(value));
        }

        else if (this->type() == INT)
        {
            if (value.type() == typeid(int))
                _value = value;
            else
                _value = std::any((int)std::any_cast<double>(value));
        }

        else if (this->type() == FLOAT)
        {
            if (value.type() == typeid(float))
                _value = value;
            else
                _value = std::any((float)std::any_cast<double>(value));
        }

        else if (this->type() == DOUBLE)
        {
            if (value.type() == typeid(double))
                _value = value;
            else
                _value = std::any(std::any_cast<double>(value));
        }

        if (!preventUpdate)
        {
            lg("Property notify");
            this->notify("value", value, observer);
            lg("Property notify done");
        }
    }

    void Property::hide()
    {
        for (const auto& w : _widgetsConnected)
            w->hide();
        _visible = false;
    }
    void Property::show()
    {
        for (const auto& w : _widgetsConnected)
            w->show();
        _visible = true;
    }

    bool Property::visible() const{return _visible;}

    #include "./props_impl_gen.h"    
}
