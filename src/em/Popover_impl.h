
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class Popover;
    class Popover_impl : public Widget_impl
    {
        public:
            Popover_impl(Popover* win);
            virtual ~Popover_impl();

            virtual void _createWidget() override;
    };
}
