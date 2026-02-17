
#include "./WebView_impl.h"
#include "../WebView.h"

namespace ml
{
    WebView_impl::WebView_impl(WebView* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    void WebView_impl::_createWidget()
    {
        GtkWidget* c_webview = webkit_web_view_new();
        _gtk.reset(Glib::wrap(c_webview, false));
#ifdef mydebug
        auto* settings = webkit_web_view_get_settings(this->webView());
        g_object_set(G_OBJECT(settings), "enable-developer-extras", TRUE, NULL);
#endif
        // implement sepecific stuff here if necessecary.
    }

    void WebView_impl::setURI(const std::string& uri)
    {
        webkit_web_view_load_uri(this->webView(), uri.c_str()); 
    }

    void WebView_impl::readFile(const std::string& path)
    {
        this->setURI("file://" + path); 
    }
}
