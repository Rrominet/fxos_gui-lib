
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

            void insertText(const std::string& text, int position);
            void deleteText(unsigned int start, unsigned int end);
            void setCursorPosition(unsigned int position);
            int getCursorPosition() const;

            ENTRY_GET_SET_EM(std::string)
    };
}
