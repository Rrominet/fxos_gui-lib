#include "./props_utils.h"
#include "./Property.h"
#include "./Box.h"
#include "./ComboBox.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace ml
{
    namespace props
    {
        std::string valueAsString(const std::any& a)
        {
            if (a.type() == typeid(std::string))
                return std::any_cast<std::string>(a);
            else if (a.type() == typeid(double))
                return std::to_string(std::any_cast<double>(a));
            else if (a.type() == typeid(bool))
                return std::to_string(std::any_cast<bool>(a));
            else if (a.type() == typeid(float))
                return std::to_string(std::any_cast<float>(a));
            else if (a.type() == typeid(Color<double>))
            {
                Color<double> c = std::any_cast<Color<double>>(a);
                return c.serialize().dump();
            }
            else if (a.type() == typeid(json))
                return std::any_cast<json>(a).dump();
            else
                return std::to_string(std::any_cast<int>(a));
        }

        std::shared_ptr<Widget> propInput(Property* prop, ml::Box* inputContainer)
        {
            std::shared_ptr<Widget> _r;
            if (inputContainer->children().size() == 1)
                _r = inputContainer->children()[0];
            else if (inputContainer->children().size() >= 2)
                _r = inputContainer->children()[1];

            return _r;
        }

        void connectComboBox(EnumProperty* prop, ComboBox* input)
        {
            prop->addObserver(input, "choices-changed");
            input->addOnUpdate("choices-changed", [input, prop](const std::any& a){
                    input->blockEvents();
                    input->setItems(prop->choices());
                    input->allowEvents();
            });
        }
    }
}
