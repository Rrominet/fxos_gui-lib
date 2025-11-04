
#pragma once
#include "./Input.h"
#include "./entries_macros.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/Entry_impl.h"
#else
#include "./gtk/Entry_impl.h"
#endif

namespace ml
{
    class Entry : public Input
    {
        public : 
            Entry();
            virtual ~Entry() = default;
            virtual void init() override;

            std::shared_ptr<ml::Entry_impl> entry(){return std::static_pointer_cast<Entry_impl>(_impl);}
            std::shared_ptr<ml::Entry_impl> entry() const{return std::static_pointer_cast<Entry_impl>(_impl);}

            void insertText(const std::string& text, int position){this->entry()->insertText(text, position);}
            void deleteText(unsigned int start, unsigned int end){this->entry()->deleteText(start, end);}
            void setCursorPosition(unsigned int position){this->entry()->setCursorPosition(position);}
            int getCursorPosition() const {return this->entry()->getCursorPosition();}

            ENTRY_GET_SET(entry)
    };
}
