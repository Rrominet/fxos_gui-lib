
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class Scrollable;
    class Scrollable_impl : public Widget_impl
    {
        public:
            Scrollable_impl(Scrollable* win);
            virtual ~Scrollable_impl(){}

            virtual void _createWidget() override;

            void setChild(ml::Widget& child);
    };
}
