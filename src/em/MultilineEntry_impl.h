#pragma once
#include "./Widget_impl.h"

namespace ml
{
    class MultilineEntry;
    class MultilineEntry_impl : public Widget_impl
    {
        public : 
            MultilineEntry_impl(MultilineEntry* abstract);
            virtual ~MultilineEntry_impl() = default;

            virtual void _createWidget() override;

            std::string placeholder();
            void setPlaceholder(const std::string& placeholder);

            std::string value();
            void setValue(const std::string& value);
    };
}
