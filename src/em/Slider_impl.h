
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"
#include "./entries_macros.h"

namespace ml
{
    class Slider;
    class Slider_impl : public Widget_impl
    {
        public:
            Slider_impl(Slider* win);
            virtual ~Slider_impl();

            virtual void _createWidget() override;

            NB_ENTRY_GET_SET_EM(double);
    };
}
