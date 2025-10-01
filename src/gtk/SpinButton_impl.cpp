
#include "./SpinButton_impl.h"
#include "../SpinButton.h"
#include "../EventInfos.h"

namespace ml
{
    SpinButton_impl::SpinButton_impl(SpinButton* abstract) : Widget_impl((Widget*)abstract)
    {
    }
    void SpinButton_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::SpinButton>();
        // implement sepecific stuff here if necessecary.
    }

    void SpinButton_impl::_addOnChange(Event event, const std::function<void (EventInfos&)>& callback)
    {
        this->spinButton()->signal_value_changed().connect([callback](){
            EventInfos e;
            callback(e);
        });
    }
}
