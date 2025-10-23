
#pragma once
#include "./Input.h"
#include "./entries_macros.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/SpinButton_impl.h"
#else
#include "./gtk/SpinButton_impl.h"
#endif

namespace ml
{
    class SpinButton : public Input
    {
        public : 
            SpinButton();
            virtual ~SpinButton() = default;
            virtual void init() override;

            std::shared_ptr<ml::SpinButton_impl> spinButton(){return std::static_pointer_cast<SpinButton_impl>(_impl);}

            NB_ENTRY_GET_SET(spinButton);
    };
}
