#include "./MultilineEntry_impl.h"
#include "../EventInfos.h"

namespace ml
{
    MultilineEntry_impl::MultilineEntry_impl(MultilineEntry* abstract) : Widget_impl((Widget*)abstract) {} 

    void MultilineEntry_impl::_createWidget()
    {
        _buffer = Gtk::TextBuffer::create();
        _gtk = std::make_shared<Gtk::TextView>();
        this->textview()->set_buffer(_buffer);
    }

    void MultilineEntry_impl::_addOnChange(Event event, const std::function<void (EventInfos&)>& callback)
    {
        _buffer->signal_changed().connect([callback](){
            EventInfos e;
            callback(e);
        });
    }

    void MultilineEntry_impl::_addOnValid(Event event, const std::function<void (EventInfos&)>& callback)
    {
        _addOnKeyDown(event, [this, callback](EventInfos& e){
            if(e.key == "Return" && e.ctrl == true && e.alt == false && e.super == false && e.shift == false) 
            {
                e.preventDefault = true;
                callback(e);
                return;
            }

            e.preventDefault = false;
        });
    }
}
