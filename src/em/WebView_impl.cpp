
#include "./WebView_impl.h"
#include "../WebView.h"

namespace ml
{
    WebView_impl::WebView_impl(WebView* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    WebView_impl::~WebView_impl()
    {
    }

    void WebView_impl::_createWidget()
    {
        auto domWidget = em::createElement("webView");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "webView");
    }
}
