#pragma once
#include "./Entry.h"

namespace ml
{
    class DateEntry : public Entry
    {
        public : 
            DateEntry();
            virtual ~DateEntry() = default;
            virtual void init() override;

            void _setEvents();
            void setFromTime(int64_t time);
            int64_t asTime();
    };
}
