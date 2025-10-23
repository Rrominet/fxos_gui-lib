
#include "./Switch_impl.h"
#include "../Switch.h"
#include "../EventInfos.h"

namespace ml
{
    Switch_impl::Switch_impl(Switch* abstract) : Widget_impl((Widget*)abstract)
    {
    }
    void Switch_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::Switch>();
        // implement sepecific stuff here if necessecary.
    }

    void Switch_impl::_addOnChange(Event event, const std::function<void (EventInfos&)>& callback)
    {
        this->_switch()->signal_state_set().connect([callback](bool){
            EventInfos e;
            callback(e);
            return false;
        }, false);
    }
}
