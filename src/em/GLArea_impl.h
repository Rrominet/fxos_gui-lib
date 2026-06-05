
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class GLArea;
    class GLArea_impl : public Widget_impl
    {
        public:
            GLArea_impl(GLArea* win);
            virtual ~GLArea_impl();

            virtual void _createWidget() override;
    };
}
