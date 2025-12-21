
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class Fixed;
    class Fixed_impl : public Widget_impl
    {
        public:
            Fixed_impl(Fixed* win);
            virtual ~Fixed_impl();

            virtual void _createWidget() override;
    };
}
