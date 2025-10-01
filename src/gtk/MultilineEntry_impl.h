#pragma once
#include <gtkmm/textview.h>
#include <gtkmm/textbuffer.h>
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class MultilineEntry;
    class MultilineEntry_impl : public Widget_impl
    {
        public : 
            MultilineEntry_impl(MultilineEntry* abstract);
            virtual ~MultilineEntry_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::TextView> textview(){return std::static_pointer_cast<Gtk::TextView>(_gtk);};

            std::string placeholder(){return this->help();}
            void setPlaceholder(const std::string& placeholder){this->setHelp(placeholder);}

            std::string value(){return _buffer->get_text();}
            void setValue(const std::string& value){_buffer->set_text(value);}

        protected : 
            Glib::RefPtr<Gtk::TextBuffer> _buffer;
            virtual void _addOnChange(Event event, const std::function<void (EventInfos&)>& callback) override;
            virtual void _addOnValid(Event event, const std::function<void (EventInfos&)>& callback) override;
    };
}
