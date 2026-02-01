
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"
#include "geometry.h"

namespace ml
{
    class Fixed;
    class Fixed_impl : public Widget_impl
    {
        public:
            Fixed_impl(Fixed* win);
            virtual ~Fixed_impl();

            virtual void _createWidget() override;

            void append(std::shared_ptr<ml::Widget> child);
            void remove(ml::Widget* child);

            //setPosition equivalent(it does not add to the existing translation)
            void move(ml::Widget* w, double x, double y);

            geometry::Point<double> widgetPos(ml::Widget* w);

        protected : 
            ml::Vec<std::shared_ptr<emval>> _children;

    };
}
