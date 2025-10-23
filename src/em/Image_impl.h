
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class Image;
    class Image_impl : public Widget_impl
    {
        public:
            Image_impl(Image* win);
            virtual ~Image_impl();

            virtual void _createWidget() override;
    };
}
