
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

    void Entry_impl::insertText(const std::string& text,int position)
    {
        this->entry()->insert_text(text, text.length(), position);
    }

    void Entry_impl::deleteText(unsigned int start,unsigned int end)
    {
        this->entry()->delete_text(start, end);
    }

    void Entry_impl::setCursorPosition(unsigned int position)
    {
        this->entry()->set_position(position);
    }

    int Entry_impl::getCursorPosition() const
    {
        return this->entry()->get_position();
    }
}
