#pragma once
#include "./Input.h"
#include "./entries_macros.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/MultilineEntry_impl.h"
#else
#include "./gtk/MultilineEntry_impl.h"
#endif

namespace ml
{
    class MultilineEntry : public Input
    {
        public : 
            MultilineEntry();
            virtual ~MultilineEntry() = default;
            virtual void init() override;

            std::shared_ptr<ml::MultilineEntry_impl> entry(){return std::static_pointer_cast<MultilineEntry_impl>(_impl);}

            ENTRY_GET_SET(entry)
    };
}
