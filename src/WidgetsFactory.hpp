#include "./WidgetsFactory.h"
#include "./Canvas.h"
#include "./Box.h"
#include "./Box.hpp"
#include "./App.h"

#ifdef __EMSCRIPTEN__
#include "./em/Canvas_impl.h"
#else
#include "./gtk/Canvas_impl.h"
#endif

namespace ml
{
    template <typename W, typename... Args>
        std::shared_ptr<W> WidgetsFactory::createCanvas(ml::Box* parent, Args&&... args)
        {
            ml::app()->checker().set("can-construct-widget", true);
            auto widget = std::make_shared<W>();
            widget->_impl = std::make_shared<Canvas_impl>(widget.get());
            widget->_impl->_createWidget();
            widget->_impl->_createBasicEvents();
            ml::app()->checker().set("can-construct-widget", false);
            widget->setParent(parent);
            parent->append(widget);
            widget->init();
            widget->setEvents();
            return widget;
        }

    template <typename W, typename... Args>
        std::shared_ptr<W> WidgetsFactory::createCanvas(ml::AbsoluteBox* parent, Args&&... args)
        {
            ml::app()->checker().set("can-construct-widget", true);
            auto widget = std::make_shared<W>();
            widget->_impl = std::make_shared<Canvas_impl>(widget.get());
            widget->_impl->_createWidget();
            widget->_impl->_createBasicEvents();
            ml::app()->checker().set("can-construct-widget", false);
            widget->setParent(parent);
            parent->append(widget);
            widget->init();
            widget->setEvents();
            return widget;
        }

    template <typename W, typename... Args>
        std::shared_ptr<W> WidgetsFactory::createCanvas(ml::Scrollable* parent, Args&&... args)
        {
            ml::app()->checker().set("can-construct-widget", true);
            auto widget = std::make_shared<W>();
            widget->_impl = std::make_shared<Canvas_impl>(widget.get());
            widget->_impl->_createWidget();
            widget->_impl->_createBasicEvents();
            ml::app()->checker().set("can-construct-widget", false);
            widget->setParent(parent);
            parent->append(widget);
            widget->init();
            widget->setEvents();
            return widget;
        }
}
