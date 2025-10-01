
#pragma once
#include <gtkmm/togglebutton.h>
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class ToggleButton;
    class ToggleButton_impl : public Widget_impl
    {
        public:
            ToggleButton_impl(ToggleButton* abstract);
            virtual ~ToggleButton_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::ToggleButton> toggleButton(){return std::static_pointer_cast<Gtk::ToggleButton>(_gtk);}

            void setText(const std::string& text){toggleButton()->set_label(text);}
            std::string text(){return toggleButton()->get_label();}

            void setValue(bool value){toggleButton()->set_active(value);}
            bool value(){return toggleButton()->get_active();}

        protected : 
            virtual void _addOnMouseUp(Event event, const std::function<void (EventInfos&)>& callback) override ;
            virtual void _addOnLeftUp(Event event, const std::function<void (EventInfos&)>& callback) override ;
            virtual void _addOnChange(Event event, const std::function<void (EventInfos&)>& callback) override ;
    };
}
