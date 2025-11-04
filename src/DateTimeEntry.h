
#pragma once
#include "./Entry.h"

namespace ml
{
    class DateTimeEntry : public Entry
    {
        public : 
            DateTimeEntry();
            virtual ~DateTimeEntry() = default;
            virtual void init() override;

            void _setEvents();
    };
}
