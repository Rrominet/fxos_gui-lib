
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"
#include "./entries_macros.h"

namespace ml
{
    class SpinButton;
    class SpinButton_impl : public Widget_impl
    {
        public:
            SpinButton_impl(SpinButton* win);
            virtual ~SpinButton_impl();

            virtual void _createWidget() override;


            NB_ENTRY_GET_SET_EM(double);
    };
}
