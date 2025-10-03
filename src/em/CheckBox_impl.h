
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class CheckBox;
    class CheckBox_impl : public Widget_impl
    {
        public:
            CheckBox_impl(CheckBox* win);
            virtual ~CheckBox_impl();

            virtual void _createWidget() override;
            
            void setValue(bool value);
            bool value();

            void setText(const std::string& text) override;
            std::string text() override;

        private : 
            std::shared_ptr<emval> _checkbox;
            std::shared_ptr<emval> _label;
    };
}
