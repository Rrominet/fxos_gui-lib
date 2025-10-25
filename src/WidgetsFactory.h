#pragma once
#include <memory>
#include <string>

namespace ml
{
    class Window;
    class Widget;
    class Canvas;
#include "./Widget_types_classes_gen.h"
    class WidgetsFactory
    {
        public : 
            WidgetsFactory() = default;
            virtual ~WidgetsFactory() = default;

            // to be used for highlevel widgets (not he one that have a different implementations for gtk ans em if doubt just check the file ./WidgetsFactory_types_gen.h)
            // all T type should have an init() function that will be called after the constructor (that let you write inheritance stuffs in it)
            // the returned shared_pointer need to be permanent if you don't want your widget to die just after this function call.
            template <typename T, typename... Args>
                std::shared_ptr<T> create(Args&&... args)
                {
                    auto w = std::make_shared<T>(std::forward<Args>(args)...);
                    w->init();
                    return w;
                }

            std::shared_ptr<ml::Image> createImage(bool icon, ml::Box* parent);

            template <typename W=ml::Canvas, typename... Args>
                std::shared_ptr<W> createCanvas(ml::Box* parent, Args&&... args);

            template <typename W=ml::Canvas, typename... Args>
                std::shared_ptr<W> createCanvas(ml::AbsoluteBox* parent, Args&&... args);

            template <typename W=ml::Canvas, typename... Args>
                std::shared_ptr<W> createCanvas(ml::Scrollable* parent, Args&&... args);

        public : 
#include "./WidgetsFactory_types_gen.h"

    };
}
