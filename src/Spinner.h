
#pragma once
#include "./Widget.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/Spinner_impl.h"
#else
#include "./gtk/Spinner_impl.h"
#endif

namespace ml
{
    class Spinner : public Widget
    {
        public : 
            Spinner();
            virtual ~Spinner() = default;
            virtual void init() override;

            std::shared_ptr<ml::Spinner_impl> spinner(){return std::static_pointer_cast<Spinner_impl>(_impl);}
    };
}
