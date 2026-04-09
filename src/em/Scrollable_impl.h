
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class Scrollable;
    class Scrollable_impl : public Widget_impl
    {
        public:
            Scrollable_impl(Scrollable* win);
            virtual ~Scrollable_impl(){}

            virtual void _createWidget() override;

            void setChild(ml::Widget& child);

            void scrollDown(double amount);
            void scrollUp(double amount);
            void scrollLeft(double amount);
            void scrollRight(double amount);

            void addOnXScroll(const std::function<void(double)>& cb);
            void addOnYScroll(const std::function<void(double)>& cb);

            double scrollX() const;
            double scrollY() const;
    };
}
