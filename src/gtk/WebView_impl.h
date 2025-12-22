#pragma once
#include <memory>
#include "./Widget_impl.h"
#include <webkit/webkit.h>
#include "str.h"

//If the web process crash, on hte client you need to : 
// cat /proc/sys/kernel/apparmor_restrict_unprivileged_userns
// sudo sysctl -w kernel.apparmor_restrict_unprivileged_userns=0
// echo "kernel.apparmor_restrict_unprivileged_userns=0" | sudo tee /etc/sysctl.d/99-apparmor-userns.conf
// sudo sysctl --system
// 
//
// or for releases : 
//
// APP=/full/path/to/your_app
// NAME=your_app
// 
// sudo tee /etc/apparmor.d/$NAME >/dev/null <<EOF
// abi <abi/4.0>,
// include <tunables/global>
// 
// profile $NAME $APP flags=(unconfined) {
//   userns,
// }
// EOF
// 
// sudo apparmor_parser -r /etc/apparmor.d/$NAME
//

namespace ml
{
    class WebView;
    class WebView_impl : public Widget_impl
    {
        public:
            WebView_impl(WebView* abstract);
            virtual ~WebView_impl() = default;

            virtual void _createWidget() override;
            WebKitWebView* webView(){return (WebKitWebView*)_gtk->gobj();}
            WebKitWebView* webView() const{return (WebKitWebView*)_gtk->gobj();}

            void setURI(const std::string& uri);
            void readFile(const std::string& path);
    };
}
