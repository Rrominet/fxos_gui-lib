#pragma once
#include "./App.h"
#include "./Widget.h"

namespace ml
{
    namespace containers
    {
        template<typename C> 
            void append(C& container, std::shared_ptr<ml::Widget> child, bool prepend = false)
            {
                lg("a");
                child->unparent();
                lg("a");
                ml::app()->checker().set("can-set-window", true);
                lg("a");
                if (container.hasWindow())
                {
                    lg("a");
                    child->setWindow(container.window());
                    lg("a");
                }
                lg("a");
                ml::app()->checker().set("can-set-window", false);
                lg("a");
                if constexpr (std::is_same_v<C, ml::Fixed>)
                {
                    lg("a");
                    container.fixed()->append(child);
                    lg("a");
                }
                else if constexpr (std::is_same_v<C, ml::AbsoluteBox>)
                {
                    lg("a");
                    container.absolute_box()->append(child);
                    lg("a");
                }
                else
                {
                    lg("a");
                    if (prepend)
                    {
                        lg("a");
                        container.box()->prepend(child);
                        lg("a");
                    }
                    else 
                    {
                        lg("a");
                        container.box()->append(child);
                        lg("a");
                    }
                }
                lg("a");
                child->setParent(&container);
                lg("a");
                container.children().push_back(child);
                lg("a");

                child->events().emit("appended");
                lg("a");
            }
    }
}
