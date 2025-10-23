
#include "./ToggleButton_impl.h"
#include "../ToggleButton.h"
#include "../EventInfos.h"

namespace ml
{
    ToggleButton_impl::ToggleButton_impl(ToggleButton* abstract) : Widget_impl((Widget*)abstract)
    {
    }
    void ToggleButton_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::ToggleButton>();
        // implement sepecific stuff here if necessecary.
    }
    void ToggleButton_impl::_addOnMouseUp(Event event, const std::function<void (EventInfos&)>& callback)
    {
        this->toggleButton()->signal_clicked().connect([callback](){
            EventInfos e;
            callback(e);
        });
    }

    void ToggleButton_impl::_addOnLeftUp(Event event, const std::function<void (EventInfos&)>& callback)
    {
        this->toggleButton()->signal_clicked().connect([callback](){
            EventInfos e;
            callback(e);
        });
    }

    void ToggleButton_impl::_addOnChange(Event event, const std::function<void (EventInfos&)>& callback)
    {
        this->toggleButton()->signal_toggled().connect([callback](){
            EventInfos e;
            callback(e);
        });
    }
}
