
#pragma once
#include <gtkmm/entry.h>
#include <memory>
#include "./Widget_impl.h"
#include "../entries_macros.h"

namespace ml
{
    class Entry;
    class Entry_impl : public Widget_impl
    {
        public:
            Entry_impl(Entry* abstract);
            virtual ~Entry_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::Entry> entry(){return std::static_pointer_cast<Gtk::Entry>(_gtk);}
            std::shared_ptr<Gtk::Entry> entry() const{return std::static_pointer_cast<Gtk::Entry>(_gtk);}

            std::string placeholder(){return entry()->get_placeholder_text();}
            void setPlaceholder(const std::string& placeholder){entry()->set_placeholder_text(placeholder);}

            void insertText(const std::string& text, int position);
            void deleteText(unsigned int start, unsigned int end);
            void setCursorPosition(unsigned int position);
            int getCursorPosition() const;

            ENTRY_GET_SET_GTK(entry, std::string)

        protected : 
            virtual void _addOnChange(Event event, const std::function<void (EventInfos&)>& callback) override ;
            virtual void _addOnValid(Event event, const std::function<void (EventInfos&)>& callback) override ;
    };
}
