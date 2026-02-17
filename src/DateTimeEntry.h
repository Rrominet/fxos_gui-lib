
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
            void setFromTime(int64_t time);
            int64_t asTime();
    };
}
