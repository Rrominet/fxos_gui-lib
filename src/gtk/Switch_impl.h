
#pragma once
#include <gtkmm/switch.h>
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class Switch;
    class Switch_impl : public Widget_impl
    {
        public:
            Switch_impl(Switch* abstract);
            virtual ~Switch_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::Switch> _switch(){return std::static_pointer_cast<Gtk::Switch>(_gtk);}

            void setValue(bool value){_switch()->set_active(value);}
            bool value(){return _switch()->get_active();}

        protected : 
            virtual void _addOnChange(Event event, const std::function<void (EventInfos&)>& callback) override ;
    };
}
