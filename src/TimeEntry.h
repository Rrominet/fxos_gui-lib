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
    };
}
