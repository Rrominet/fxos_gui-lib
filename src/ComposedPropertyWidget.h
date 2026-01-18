#pragma once
#include "./Box.h"
#include "./Property.h"
#include "./Label.h"
#include "./ComposedInput.h"
#include "./props_utils.h"
#include "enums.h"
#include "./ComboBox.h"
#include "./ColorButton.h"

// exactly the same thing as PropertyWidget.h but with a ComposedInput in place of the Input.

namespace ml
{
    // there is no need to keep this object around, just constuct it and all is good. (no need for smart pointer,  or anything)
    template <typename Prop>
        class ComposedPropertyWidget
        {
            public:
                template <typename Container=ml::Box>
                    ComposedPropertyWidget(Container* parent, Prop* prop, DrawType drawType = AUTO) : _prop(prop), _drawType(drawType)
                {
#ifdef mydebug
                    this->checkDrawType();
#endif
                    this->createUI(parent);
                    this->connect();
                }
                virtual ~ComposedPropertyWidget() = default;
                
                // assert if the drawtype is meant for a PropertyWidget (not a Compoased one)
                void checkDrawType()
                {
                    if (_drawType == LABEL || _drawType == ENTRY || _drawType == MULTILINE_ENTRY || _drawType == SLIDER || _drawType == PROGRESS || _drawType == CHECKBOX || _drawType == SWITCH || _drawType == SPINBUTTON || _drawType == TOGGLEBUTTON || _drawType == PASSWORD) 
                        assert(false && "PropertyWidget::checkDrawType : _drawType is meant for a PropertyWidget (not a composed one).");
                }

                DrawType defaultDraw()
                {
                    return DrawType::COMBOBOX;
                }

                DrawType drawType()
                {
                    if (_drawType == AUTO)
                        return this->defaultDraw();
                    else
                        return _drawType;
                }

                void createLabel()
                {
                    assert(_box && "PropertyWidget::createLabel : no box for the container created.");
                    _label = _box->createLabel(_prop->name() + " : ");
                    _label->setHelp(_prop->description());
                    _label->setHAlign(ml::LEFT);
                }

                void createInput()
                {
                    assert(_box && "PropertyWidget::createInput : no box for the container created.");
                    auto dtype = this->drawType();
                    if(dtype == COMBOBOX)
                    {

                        _input = std::static_pointer_cast<ComposedInput>(_box->createComposedWidget<ComboBox>(_box.get(), std::vector<std::string>()));
                        EnumProperty* _enum = dynamic_cast<EnumProperty*>(_prop);
                        if (_enum)
                        {
                            auto cb = std::static_pointer_cast<ComboBox>(_input);
                            lg("ComposedPropertyWidget::createInput : Set items : " << _enum->choices().size());
                            cb->setItems(_enum->choices());
                            lg("ComboBox Items: " << cb->items().size());
                        }
                    }
                    else if (dtype  == COLOR_BUTTON)
                        _input = std::static_pointer_cast<ComposedInput>(_box->createComposedWidget<ColorButton>(_box.get()));
                    else if (dtype == COLOR_PICKER)
                        _input = std::static_pointer_cast<ComposedInput>(_box->createComposedWidget<ColorPicker>(_box.get()));
                    else 
                        assert(false && "PropertyWidget::createInput : unknown draw type.");

                    _input->setHelp(_prop->description());
                    _input->setValue(_prop->value());
                    _input->setHAlign(RIGHT);
                    _input->setHExpand(true);
                }

                template <typename Container=ml::Box>
                    void createUI(Container* parent)
                    {
                        _box = parent->createBox();
                        _box->addCssClass("prop");
                        this->createLabel();
                        this->createInput();
                        _box->setOrient(HORIZONTAL);
                    }

                void connect()
                {
                    assert (_input && "PropertyWidget::connect : no input created.");
                    props::connect(_prop, _input.get());
                    _prop->widgetsConnected().push(_box);
                }


                std::shared_ptr<Box> box(){return _box;}
                std::shared_ptr<Label> label(){return _label;}
                std::shared_ptr<ComposedInput> input(){return _input;}

                void hideLabel()
                {
                    if (_label)
                        _label->hide();
                }

            private : 
                Prop* _prop = nullptr;
                DrawType _drawType;
                std::shared_ptr<Box> _box = nullptr;
                std::shared_ptr<Label> _label = nullptr;
                std::shared_ptr<ComposedInput> _input = nullptr;
        };
}
