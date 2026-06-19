#pragma once
#include "./App.h"
#include "./Widget.h"
#include "./Scrollable.h"
#include "./Box.h"
#include "./Fixed.h"
#include "./AbsoluteBox.h"
#include "./Popover.h"

namespace ml
{
    namespace containers
    {
        template<typename C> 
            void append(C& container, std::shared_ptr<ml::Widget> child, bool prepend = false)
            {
                child->unparent();
                ml::app()->checker().set("can-set-window", true);
                if (container.hasWindow())
                {
                    child->setWindow(container.window());
                }
                if constexpr (std::is_same_v<C, ml::Fixed>)
                {
                    container.fixed()->append(child);
                }
                else if constexpr (std::is_same_v<C, ml::AbsoluteBox>)
                {
                    container.absolute_box()->append(child);
                }
                else
                {
                    if (prepend)
                    {
                        container.box()->prepend(child);
                    }
                    else 
                    {
                        container.box()->append(child);
                    }
                }
                child->setParent(&container);
                container.children().push_back(child);

                if (container.hasWindow())
                {
                    child->events().emit("appended");
                    if (child->containerType() == CONTAINER_NONE)
                    {
                        ml::app()->checker().set("can-set-window", false);
                        return;
                    }
                    ml::Vec<std::shared_ptr<Widget>> children;
                    if (auto b = dynamic_cast<ml::Box*>(child.get()))
                    {
                        children = b->deepChildren();
                    }
                    else if (auto b = dynamic_cast<ml::Fixed*>(child.get()))
                    {
                        children = b->deepChildren();
                    }
                    else if (auto b = dynamic_cast<ml::AbsoluteBox*>(child.get()))
                    {
                        children = b->deepChildren();
                    }
                    else if (auto b = dynamic_cast<ml::Scrollable*>(child.get()))
                    {
                        children = b->deepChildren();
                    }
                    else if (auto b = dynamic_cast<ml::Popover*>(child.get()))
                    {
                        children = b->deepChildren();
                    }

                    for (auto& c : children)
                    {
                        c->setWindow(container.window());
                        c->events().emit("appended");
                    }
                }

                ml::app()->checker().set("can-set-window", false);
            }

        template<typename C> 
            ml::Vec<std::shared_ptr<Widget>> deepChildren(const C& container)
            {
                ml::Vec<std::shared_ptr<Widget>> res; 
                for (auto&c : container.children())
                {
                    res.push_back(c);
                    if (c->containerType() != CONTAINER_NONE)
                    {
                        if (auto b = dynamic_cast<ml::Box*>(c.get()))
                            res.concat(b->deepChildren());
                        else if(auto b = dynamic_cast<ml::Fixed*>(c.get()))
                            res.concat(b->deepChildren());
                        else if(auto b = dynamic_cast<ml::AbsoluteBox*>(c.get()))
                            res.concat(b->deepChildren());
                        else if(auto b = dynamic_cast<ml::Scrollable*>(c.get()))
                            res.concat(b->deepChildren());
                        else if (auto b = dynamic_cast<ml::Popover*>(c.get()))
                            res.concat(b->deepChildren());
                    }
                }

                //TODO : Still need to add the _composedChildren;

                return res;
            }
    }
}
