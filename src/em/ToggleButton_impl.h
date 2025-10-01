
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class ToggleButton;
    class ToggleButton_impl : public Widget_impl
    {
        public:
            ToggleButton_impl(ToggleButton* win);
            virtual ~ToggleButton_impl(){}

            virtual void _createWidget() override;

            //this is called after the domelement has been parented (its necessarry because the addEventlistener call querySelector under the hood so the elmt must already be parented to something)
            virtual void setEvents() override ;

            void setValue(bool value);
            bool value();

        protected : 
            std::function<void(EventInfos&)> _onChange = 0;
            virtual void _addOnChange(Event event, const std::function<void(EventInfos&)>& callback) override;
    };
}
