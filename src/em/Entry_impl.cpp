
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

    //insert text at the given position in the html "input" that is contains in the _dom
    void Entry_impl::insertText(const std::string& text,int position)
    {
        std::string currentValue = (*_dom)["value"].as<std::string>();
        std::string newValue = currentValue.substr(0, position) + text + currentValue.substr(position);
        _dom->set("value", newValue);
    }

    void Entry_impl::deleteText(unsigned int start,unsigned int end)
    {
        std::string currentValue = (*_dom)["value"].as<std::string>();
        if (start >= currentValue.length()) return;
        if (end > currentValue.length()) end = currentValue.length();
        std::string newValue = currentValue.substr(0, start) + currentValue.substr(end);
        _dom->set("value", newValue);
    }

    void Entry_impl::setCursorPosition(unsigned int position)
    {
        (*_dom).call<void>("setSelectionRange", position, position);
    }

    int Entry_impl::getCursorPosition() const
    {
        return (*_dom)["selectionStart"].as<int>();
    }

}
