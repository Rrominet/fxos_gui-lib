
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class Button;
    class Button_impl : public Widget_impl
    {
        public:
            Button_impl(Button* win);
            virtual ~Button_impl();

            virtual void _createWidget() override;

        protected:
            virtual void _addOnLeftUp(Event event, const std::function<void(EventInfos&)>& callback) override ;
    };
}

