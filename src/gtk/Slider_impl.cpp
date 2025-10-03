
#include "./Slider_impl.h"
#include "../Slider.h"
#include "../EventInfos.h"

namespace ml
{
    Slider_impl::Slider_impl(Slider* abstract) : Widget_impl((Widget*)abstract)
    {
    }
    void Slider_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::Scale>();
        // implement sepecific stuff here if necessecary.
    }
    void Slider_impl::_addOnChange(Event event, const std::function<void (EventInfos&)>& callback)
    {
        this->slider()->signal_value_changed().connect([callback](){
            EventInfos e;
            callback(e);
        });
    }
}
