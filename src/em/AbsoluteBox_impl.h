#pragma once
#include "./Widget_impl.h"
#include "./em.h"

namespace ml
{
    class Box;
    class AbsoluteBox_impl : public Widget_impl
    {
        public : 
            AbsoluteBox_impl(Box* win);
            virtual ~AbsoluteBox_impl() = default;

            virtual void _createWidget() override;

            std::shared_ptr<emval> overlay(){assert(_dom); return _dom;}

            void append(std::shared_ptr<ml::Widget> c);
            void prepend(std::shared_ptr<ml::Widget> c);
            void remove(ml::Widget* c);

            void setBackground(std::shared_ptr<ml::Widget> c);
            void setBackground(ml::Widget* c);
            void removeBackground();

            void sendToFront(ml::Widget* c);
            void sendToBack(ml::Widget* c);
            void moveDepth(ml::Widget* c, unsigned int x);

        private : 
            std::shared_ptr<emval> _background;
            ml::Vec<std::shared_ptr<emval>> _children;
    };
}
