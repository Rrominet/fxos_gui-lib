#include "./IconButton.h"
#include "ComposedWidget.h"

namespace ml
{
    IconButton::IconButton(Box* parent,const std::string& icon, const std::string& label, bool inverted, bool reversed) : ComposedWidget()
    {
        __construct(parent,icon, label, inverted, reversed);	
    }

    IconButton::IconButton(Scrollable* parent,const std::string& icon, const std::string& label, bool inverted, bool reversed) : ComposedWidget()
    {
        __construct(parent,icon, label, inverted, reversed);	
    }

    void IconButton::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        _btn->addEventListener(event, callback);
    }

    void IconButton::setHAlign(HAlignment align)
    {
        _btn->setHAlign(align);
    }

    void IconButton::setHExpand(bool value)
    {
        _btn->setHExpand(value);
    }

}
