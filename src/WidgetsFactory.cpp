#include "./WidgetsFactory.h"
#include "./App.h"
#include "./Box.h"
#include "./Scrollable.h"
#include "./Widget_types_includes_gen.h"

// this changed again.

namespace ml
{
    std::shared_ptr<ml::Image> WidgetsFactory::createImage(bool icon,ml::Box* parent)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Image>(icon);
        widget->_impl = std::make_shared<ml::Image_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        parent->append(widget);
        widget->init();
        widget->setEvents();
        return widget;
    }

#include "./WidgetsFactory_types_impl_gen.h"
}
