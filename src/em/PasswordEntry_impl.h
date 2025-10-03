
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"
#include "../entries_macros.h"

namespace ml
{
    class PasswordEntry;
    class PasswordEntry_impl : public Widget_impl
    {
        public:
            PasswordEntry_impl(PasswordEntry* win);
            virtual ~PasswordEntry_impl();

            virtual void _createWidget() override;
            ENTRY_GET_SET_EM(std::string)
    };
}
