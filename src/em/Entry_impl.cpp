
#include "./Entry_impl.h"
#include "../Entry.h"

namespace ml
{
    Entry_impl::Entry_impl(Entry* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    Entry_impl::~Entry_impl()
    {
    }

    void Entry_impl::_createWidget()
    {
        auto domWidget = em::createElement("input");
        domWidget.set("type", "text");

        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "entry");
    }

    void Entry_impl::insertText(const std::string& text,int position)
    {
        //TODO : Need to check how to do this in js
    }

    void Entry_impl::deleteText(unsigned int start,unsigned int end)
    {

        //TODO : Need to check how to do this in js
    }

    void Entry_impl::setCursorPosition(unsigned int position)
    {

        //TODO : Need to check how to do this in js
    }

    int Entry_impl::getCursorPosition() const
    {

        //TODO : Need to check how to do this in js
    }

}
