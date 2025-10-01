#pragma once
#include <memory>
#include "./Box.h"
#include "./Property.h"
#include "./Widget_types_includes_gen.h"
#include "./props_utils.h"
#include "Switch.h"
#include "enums.h"
#include "gtkmm/dialog.h"


//TODO This should be under a subclass wrapper like other widgets, we should not have this kind of conditionnal include here
//BUT  Iwould like to do it with my fxplorer, so let's do this for now.
#ifdef __EMISCRIPTEN__
#else 
#include <gtkmm/filechoosernative.h>
#endif

namespace ml
{
    // there is no need to keep this object around, just constuct it and all is good. (no need for smart pointer,  or anything)
    template <typename Prop>
    class PropertyWidget
    {
        public:
            template <typename Container=ml::Box>
            PropertyWidget(Container* parent, Prop* prop, DrawType drawType = AUTO) : _prop(prop), _drawType(drawType)
        {
            this->createUI(parent);
            this->connect();
        }
            virtual ~PropertyWidget() = default;

            DrawType defaultDraw()
            {
                if (_prop->type() == Property::BOOL)
                    return DrawType::TOGGLEBUTTON;
                else if (_prop->type() == Property::INT || _prop->type() == Property::FLOAT || _prop->type() == Property::DOUBLE)
                    return DrawType::SPINBUTTON;
                else 
                    return DrawType::ENTRY;
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
                switch (this->drawType())
                {
                    case DrawType::LABEL:
                        _input = _box->createLabel();
                        break;
                    case DrawType::ENTRY:
                        _input = _box->createEntry();
                        break;
                    case DrawType::SLIDER:
                        _input = _box->createSlider();
                        _input->setRange(_prop->min(), _prop->max());
                        break;
                    case DrawType::PROGRESS:
                        _input = _box->createProgressBar();
                        _input->setRange(_prop->min(), _prop->max());
                        break;
                    case DrawType::CHECKBOX:
                        _input = _box->createCheckBox(_prop->name());
                        break;
                    case DrawType::SWITCH:
                        _input = _box->createSwitch();
                        break;
                    case DrawType::SPINBUTTON:
                        _input = _box->createSpinButton();
                        _input->setRange(_prop->min(), _prop->max());
                        _input->setWidth(250);
                        break;
                    case DrawType::TOGGLEBUTTON:
                        _input = _box->createToggleButton(_prop->name());
                        break;
                    case DrawType::PASSWORD:
                        _input = _box->createPasswordEntry();
                        break;
                    case DrawType::MULTILINE_ENTRY:
                        _input = _box->createMultilineEntry();
                        _input->setHAlign(FILL);
                        break;
                    case DrawType::FILE_PATH:
                        _input = _box->createEntry();
                        _input->addCssClass("file-path");
                        this->createFileChooserButton();
                        break;
                    case DrawType::DIR_PATH:
                        _input = _box->createEntry();
                        _input->addCssClass("dir-path");
                        this->createDirChooserButton();
                        break;
                    default:
                        _input = _box->createEntry();
                        break;
                }

                _input->setHelp(_prop->description());
                if (this->drawType() == PROGRESS || this->drawType() == SLIDER || this->drawType() == MULTILINE_ENTRY || this->drawType() == ENTRY || this->drawType() == FILE_PATH || this->drawType() == DIR_PATH)
                    _input->setHAlign(ml::FILL);
                else if (this->drawType() == TOGGLEBUTTON || this->drawType() == CHECKBOX)
                    _input->setHAlign(ml::CENTER);
                else 
                    _input->setHAlign(ml::RIGHT);

                if (this->drawType() == PROGRESS || this->drawType() == SLIDER || this->drawType() == SPINBUTTON)
                {
                    if (_prop->type() == Property::INT)
                        _input->setPrecision(0);
                    else if (_prop->type() == Property::FLOAT)
                        _input->setPrecision(3);
                    else if (_prop->type() == Property::DOUBLE)
                        _input->setPrecision(6);
                }
                _input->setHExpand(true);
                _input->setValue(_prop->value());
            }

            void createButton(const std::string& text, const std::function<void(EventInfos& e)>& callback)
            {
                _change_action = _box->createButton(text);
                _change_action->addEventListener(LEFT_UP, callback);
                _change_action->setHAlign(RIGHT);
                _change_action->setCursor("pointer");
                _change_action->setHExpand(false);
                _change_action->setHExpandSet(true);
            }

            void createFileChooserButton()
            {
                // TODO temp, should work for emiscripten too.
#ifdef __EMSCRIPTEN__
                return;
#endif
                auto prop = _prop;
                auto cb = [prop](EventInfos& e) {
                    auto fd = Gtk::FileChooserNative::create("Select a file", Gtk::FileChooser::Action::OPEN, "Select", "Cancel");
                    fd->show();
                    
                    auto set_file = [fd, prop](int res){
                        if (res == Gtk::ResponseType::ACCEPT)
                            prop->set(fd->get_files2()[0]->get_path());
                    };

                    fd->signal_response().connect(set_file);
                };
                this->createButton("...", cb);
            }

            void createDirChooserButton()
            {
                // TODO temp, should work for emiscripten too.
#ifdef __EMSCRIPTEN__
                return;
#endif
                auto prop = _prop;
                auto cb = [prop](EventInfos& e) {
                    auto fd = Gtk::FileChooserNative::create("Select a Directory", Gtk::FileChooser::Action::SELECT_FOLDER, "Select", "Cancel");
                    fd->show();
                    
                    auto set_file = [fd, prop](int res){
                        if (res == Gtk::ResponseType::ACCEPT)
                            prop->set(fd->get_files2()[0]->get_path());
                    };

                    fd->signal_response().connect(set_file);
                };
                this->createButton("...", cb);
            }

            template <typename Container=ml::Box>
            void createUI(Container* parent)
            {
                _box = parent->createBox();
                _box->addCssClass("prop");

                if (this->drawType() == TOGGLEBUTTON || this->drawType() == CHECKBOX)
                    this->createInput();
                else 
                {
                    this->createLabel();
                    this->createInput();

                    if (this->drawType() == PROGRESS || this->drawType() == SLIDER || this->drawType() == MULTILINE_ENTRY)
                        _box->setOrient(Orient::VERTICAL);
                    else 
                        _box->setOrient(Orient::HORIZONTAL);
                }
            }

            void connect()
            {
                assert (_input && "PropertyWidget::connect : no input created.");
                props::connect(_prop, _input.get());
                _prop->widgetsConnected().push(_box);
            }

            std::shared_ptr<Box> box(){return _box;}
            std::shared_ptr<Label> label(){return _label;}
            std::shared_ptr<Input> input(){return _input;}

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
            std::shared_ptr<Input> _input = nullptr;
            std::shared_ptr<Button> _change_action = nullptr;
    };
}
