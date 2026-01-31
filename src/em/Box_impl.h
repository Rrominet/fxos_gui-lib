
#pragma once
#include "./em.h"
#include <memory>
#include "./enums.h"
#include "./Widget_impl.h"
#include "./Widget.h"

namespace ml
{
    class Box;
    class Box_impl : public Widget_impl
    {
        public:
            Box_impl(Box* win);
            virtual ~Box_impl() = default;

            virtual void _createWidget() override;

            std::shared_ptr<emval> box(){assert(_dom); return _dom;}

            void setOrient(Orient orient);
            void append(std::shared_ptr<ml::Widget> child);
            void prepend(std::shared_ptr<ml::Widget> child);

            void remove(ml::Widget* child);

            void moveChild(size_t from, size_t to);
            void setSpacing(int space);
            int spacing() const;
    };
}
