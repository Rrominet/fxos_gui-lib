
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"
#include "../entries_macros.h"

namespace ml
{
    class Entry;
    class Entry_impl : public Widget_impl
    {
        public:
            Entry_impl(Entry* win);
            virtual ~Entry_impl();

            virtual void _createWidget() override;
            ENTRY_GET_SET_EM(std::string)
    };
}
