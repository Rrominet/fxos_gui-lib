
#include "./ProgressBar_impl.h"
#include "../ProgressBar.h"

namespace ml
{
    ProgressBar_impl::ProgressBar_impl(ProgressBar* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    void ProgressBar_impl::_createWidget()
    {
        auto domWidget  = em::createElement("progress");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "progressBar");
    }

    double ProgressBar_impl::value()
    {
        return (*_dom)["value"].as<double>();	
    }

    void ProgressBar_impl::setValue(const double& value)
    {
        return _dom->set("value", value);
    }

    std::string ProgressBar_impl::text()
    {
        //return nothing to mimic the gtk implementation
        return "";
    }

    void ProgressBar_impl::setText(const std::string& text)
    {
        // does nothing to mimic the gtk implementation
    }

}
