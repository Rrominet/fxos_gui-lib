
#pragma once
#include "./Input.h"
#include "./entries_macros.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/PasswordEntry_impl.h"
#else
#include "./gtk/PasswordEntry_impl.h"
#endif

namespace ml
{
    class PasswordEntry : public Input
    {
        public : 
            PasswordEntry();
            virtual ~PasswordEntry() = default;
            virtual void init() override;

            std::shared_ptr<ml::PasswordEntry_impl> passwordEntry(){return std::static_pointer_cast<PasswordEntry_impl>(_impl);}

            ENTRY_GET_SET(passwordEntry)
    };
}
