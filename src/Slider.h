
#pragma once
#include "./Input.h"
#include "./entries_macros.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/Slider_impl.h"
#else
#include "./gtk/Slider_impl.h"
#endif

namespace ml
{
    class Slider : public Input
    {
        public : 
            Slider();
            virtual ~Slider() = default;
            virtual void init() override;

            std::shared_ptr<ml::Slider_impl> slider(){return std::static_pointer_cast<Slider_impl>(_impl);}

            NB_ENTRY_GET_SET(slider);
    };
}
