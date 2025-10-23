
#include "./ProgressBar_impl.h"
#include "../ProgressBar.h"

namespace ml
{
    ProgressBar_impl::ProgressBar_impl(ProgressBar* abstract) : Widget_impl((Widget*)abstract)
    {
    }
    void ProgressBar_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::ProgressBar>();
        // implement sepecific stuff here if necessecary.
    }
}
