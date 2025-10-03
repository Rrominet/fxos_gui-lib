
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class Switch;
    class Switch_impl : public Widget_impl
    {
        public:
            Switch_impl(Switch* win);
            virtual ~Switch_impl();

            virtual void _createWidget() override;

            void setValue(bool value);
            bool value();

            virtual void setEvents() override;

        private : 
            std::shared_ptr<emval> _switchButton = nullptr;
            std::function<void(EventInfos&)> _onChange = 0;

            virtual void _addOnChange(Event event, const std::function<void(EventInfos&)>& callback) override;
    };
}
