
#pragma once
#include <gtkmm/checkbutton.h>
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class CheckBox;
    class CheckBox_impl : public Widget_impl
    {
        public:
            CheckBox_impl(CheckBox* abstract);
            virtual ~CheckBox_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::CheckButton> checkBox(){return std::static_pointer_cast<Gtk::CheckButton>(_gtk);}

            void setText(const std::string& text){checkBox()->set_label(text);}
            std::string text(){return checkBox()->get_label();}

            void setValue(bool value){checkBox()->set_active(value);}
            bool value(){return checkBox()->get_active();}

        protected : 
            virtual void _addOnChange(Event event, const std::function<void (EventInfos&)>& callback) override; 
    };
}
