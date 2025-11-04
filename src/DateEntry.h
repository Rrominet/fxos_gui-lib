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
    };
}
