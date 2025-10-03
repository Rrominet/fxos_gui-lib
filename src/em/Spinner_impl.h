
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class Spinner;
    class Spinner_impl : public Widget_impl
    {
        public:
            Spinner_impl(Spinner* win);
            virtual ~Spinner_impl();

            virtual void _createWidget() override;
    };
}
