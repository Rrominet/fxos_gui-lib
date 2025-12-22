
#pragma once
#include "./Widget.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/WebView_impl.h"
#else
#include "./gtk/WebView_impl.h"
#endif

namespace ml
{
    class WebView : public Widget
    {
        public : 
            WebView();
            virtual ~WebView() = default;
            virtual void init() override;

            std::shared_ptr<ml::WebView_impl> webView(){return std::static_pointer_cast<WebView_impl>(_impl);}
            std::shared_ptr<ml::WebView_impl> webView()const {return std::static_pointer_cast<WebView_impl>(_impl);}

            void setURI(const std::string& uri){this->webView()->setURI(uri);}
            void readFile(const std::string& path){this->webView()->readFile(path);}
    };
}
