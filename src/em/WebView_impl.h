
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class WebView;
    class WebView_impl : public Widget_impl
    {
        public:
            WebView_impl(WebView* win);
            virtual ~WebView_impl();

            virtual void _createWidget() override;
    };
}
