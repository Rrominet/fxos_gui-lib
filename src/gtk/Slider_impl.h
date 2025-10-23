
#pragma once
#include <gtkmm/scale.h>
#include <gtkmm/adjustment.h>
#include <memory>
#include "./Widget_impl.h"
#include "../entries_macros.h"

namespace ml
{
    class Slider;
    class Slider_impl : public Widget_impl
    {
        public:
            Slider_impl(Slider* abstract);
            virtual ~Slider_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::Scale> slider(){return std::static_pointer_cast<Gtk::Scale>(_gtk);}

            NB_ENTRY_GET_SET_GTK(slider, double);

        protected : 
            virtual void _addOnChange(Event event, const std::function<void (EventInfos&)>& callback) override ;
    };
}
