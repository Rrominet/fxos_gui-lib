
#include "./PasswordEntry_impl.h"
#include "../PasswordEntry.h"
#include "../EventInfos.h"

namespace ml
{
    PasswordEntry_impl::PasswordEntry_impl(PasswordEntry* abstract) : Widget_impl((Widget*)abstract)
    {
    }
    void PasswordEntry_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::PasswordEntry>();
        // implement sepecific stuff here if necessecary.
    }

    void PasswordEntry_impl::_addOnChange(Event event, const std::function<void (EventInfos&)>& callback)
    {
        this->passwordEntry()->signal_changed().connect([callback](){
            EventInfos e;
            callback(e);
        });
    }
}
