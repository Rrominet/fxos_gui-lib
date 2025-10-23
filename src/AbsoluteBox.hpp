#pragma once
#include "./ComposedWidget.h"
#include "./App.h"

namespace ml
{
    template <typename W, typename... Args>
        std::shared_ptr<ml::ComposedWidget> AbsoluteBox::createComposedWidget(Args&&... args)
        {
            auto w = std::make_shared<W>(std::forward<Args>(args)...); 
            if (w->composed().size() == 0)
                assert(false && "You forget to add your widgets to the _composed list in your child class from ComposedWidget.");
            _composedChildren.push_back(w);
            return std::static_pointer_cast<ComposedWidget>(w);
        }


    template <typename W, typename... Args>
        std::shared_ptr<W> AbsoluteBox::createCanvas(Args&&... args)
        {
            return ml::app()->widgetsFactory().createCanvas<W>(this, std::forward<Args>(args)...);
        }
}
