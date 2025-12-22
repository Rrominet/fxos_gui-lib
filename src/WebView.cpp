
#include "./WebView.h"

namespace ml
{
    WebView::WebView() : Widget()
    {

    }
    void WebView::init()
    {
        this->addCssClass("webView");
        this->setHExpand();
        this->setVExpand();
    }
}
