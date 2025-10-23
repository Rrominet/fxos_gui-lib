
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class Canvas;
    class Canvas_impl : public Widget_impl
    {
        public:
            Canvas_impl(Canvas* win);
            virtual ~Canvas_impl();

            virtual void _createWidget() override;
    };
}
