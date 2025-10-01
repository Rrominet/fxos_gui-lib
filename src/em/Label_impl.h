#pragma once
#include <memory>
#include "./Widget_impl.h"
#include "../enums.h"

namespace ml
{
    class Label;
    class Label_impl : public Widget_impl
    {
        public:
            Label_impl(Label* abstract);
            virtual ~Label_impl();

            virtual void _createWidget() override;
    };
}
