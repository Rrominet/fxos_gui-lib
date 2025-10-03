
#include "./Spinner_impl.h"
#include "../Spinner.h"

namespace ml
{
    Spinner_impl::Spinner_impl(Spinner* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    void Spinner_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::Spinner>();
        this->spinner()->start(); 
        // implement sepecific stuff here if necessecary.
    }

    void Spinner_impl::show()
    {
        Widget_impl::show();	
        this->spinner()->start();
    }


    void Spinner_impl::hide()
    {
        Widget_impl::hide();	
        this->spinner()->stop();
    }

}
