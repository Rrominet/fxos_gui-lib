#pragma once
#include "./Property.h"
#include "./PropertyWidget.h"
#include "./ComposedPropertyWidget.h"
#include "./App.h"

namespace ml
{
    template <typename W>
        std::shared_ptr<W> Box::child(size_t i)
        {
            if(i >= _children.size())
                return nullptr;

            return std::dynamic_pointer_cast<W>(_children[i]);
        }

    template <typename Prop>
        std::shared_ptr<PropertyWidget<Prop>> Box::appendProp(Prop* prop, DrawType type)
        {
            return std::make_shared<PropertyWidget<Prop>>(this, prop, type);
        }

    template <typename Prop>
        std::shared_ptr<ComposedPropertyWidget<Prop>> Box::appendComposedProp(Prop* prop, DrawType type)
        {
            return std::make_shared<ComposedPropertyWidget<Prop>>(this, prop, type);
        }

    template <typename W, typename... Args>
        std::shared_ptr<W> Box::createComposedWidget(Args&&... args)
        {
            auto w = std::make_shared<W>(std::forward<Args>(args)...); 
            if (w->composed().size() == 0)
                assert(false && "You forget to add your widgets to the _composed list in your child class from ComposedWidget.");
            _composedChildren.push_back(w);
            return w;
        }

    template <typename W, typename... Args>
        std::shared_ptr<W> Box::createCanvas(Args&&... args)
        {
            return ml::app()->widgetsFactory().createCanvas<W>(this, std::forward<Args>(args)...);
        }
}

#include "./WidgetsFactory.hpp"
