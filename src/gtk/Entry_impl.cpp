
#include "./Entry_impl.h"
#include "../Entry.h"
#include "../EventInfos.h"

namespace ml
{
    Entry_impl::Entry_impl(Entry* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    void Entry_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::Entry>();
        // implement sepecific stuff here if necessecary.
    }

    void Entry_impl::_addOnChange(Event event, const std::function<void (EventInfos&)>& callback)
    {
        this->entry()->signal_changed().connect([callback](){
            EventInfos e;
            callback(e);
        });
    }

    void Entry_impl::_addOnValid(Event event, const std::function<void (EventInfos&)>& callback)
    {
        lg("gtk impl : Entry_impl::_addOnValid");
        this->entry()->signal_activate().connect([callback](){
            EventInfos e;
            callback(e);
        });
    }
}
