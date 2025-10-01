
#pragma once
#include "debug.h"
#include <gtkmm/passwordentry.h>
#include <memory>
#include "./Widget_impl.h"
#include "../entries_macros.h"

namespace ml
{
    class PasswordEntry;
    class PasswordEntry_impl : public Widget_impl
    {
        public:
            PasswordEntry_impl(PasswordEntry* abstract);
            virtual ~PasswordEntry_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::PasswordEntry> passwordEntry(){return std::static_pointer_cast<Gtk::PasswordEntry>(_gtk);}

            std::string placeholder(){return "";}
            void setPlaceholder(const std::string& placeholder){lg("not implemented for passwords..");}

            ENTRY_GET_SET_GTK(passwordEntry, std::string)

        protected : 
            virtual void _addOnChange(Event event, const std::function<void (EventInfos&)>& callback) override ;
    };
}
