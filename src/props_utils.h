#pragma once
#include <any>
#include <string>
#include <memory>
#include "./enums.h"
#include "./EventInfos.h"

namespace ml
{
    class Widget;
    class Box;
    class Property;
    class EnumProperty;
    class ComboBox;
    class ColorPicker;
    class ColorButton;
    class ColorProperty;
    namespace props
    {
        std::string valueAsString(const std::any& a);

        // the input container should be the box() return by the PropertyWidget
        std::shared_ptr<Widget> propInput(Property* prop, ml::Box* inputContainer);
        template <typename Prop, typename Input>    
            void connect (Prop* prop, Input* input)
            {
                // property -> input
                prop->addObserver(input, "value");
                input->addOnUpdate("value", [input, prop](const std::any& a){
                        input->blockEvents();  
                        input->setValue(props::valueAsString(a)); 
                        input->allowEvents();
                        prop->onUpdate().exec();
                        });

                // input -> property
                input->addEventListener(Event::CHANGE, [input, prop](EventInfos &e)
                        {
                            auto val = input->valueAsAny();
                            prop->set(val, input);
                            prop->onUpdate().exec();
                        });

                input->addEventListener(VALID, [input, prop](EventInfos &e)
                        {
                            prop->onValid().exec();
                        });


                //TODO should also connect changes on prop settings (like name, description, etc.)
                //That being said, it can only be doned by code now, so not that important.
                //But if I want to be able to serialize/deserialize properties, I should do it.
            }
        
        void connectComboBox(EnumProperty* prop, ComboBox* input);
    }
}
