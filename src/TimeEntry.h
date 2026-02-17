#pragma once
#include "./Entry.h"

namespace ml
{
    class TimeEntry : public Entry
    {
        public : 
            TimeEntry();
            virtual ~TimeEntry() = default;
            virtual void init() override;

            void _setEvents();

            void setFromTime(int64_t time);
            int64_t asTime();
    };
}
