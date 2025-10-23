
#pragma once
#include <gtkmm/spinbutton.h>
#include <gtkmm/adjustment.h>
#include <memory>
#include "./Widget_impl.h"
#include "../entries_macros.h"

namespace ml
{
    class SpinButton;
    class SpinButton_impl : public Widget_impl
    {
        public:
            SpinButton_impl(SpinButton* abstract);
            virtual ~SpinButton_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::SpinButton> spinButton(){return std::static_pointer_cast<Gtk::SpinButton>(_gtk);}

            NB_ENTRY_GET_SET_GTK(spinButton, double);

        protected : 
            virtual void _addOnChange(Event event, const std::function<void (EventInfos&)>& callback) override ;
    };
}
