
#include "./CheckBox_impl.h"
#include "../CheckBox.h"
#include "../EventInfos.h"

namespace ml
{
    CheckBox_impl::CheckBox_impl(CheckBox* abstract) : Widget_impl((Widget*)abstract)
    {
    }
    void CheckBox_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::CheckButton>();
        // implement sepecific stuff here if necessecary.
    }

    void CheckBox_impl::_addOnChange(Event event, const std::function<void (EventInfos&)>& callback)
    {
        this->checkBox()->signal_toggled().connect([callback](){
            EventInfos e;
            callback(e);
        });
    }
}
