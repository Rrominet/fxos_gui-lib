#include "./Scrollable.h"
#include "./App.h"

namespace ml
{
    Scrollable::Scrollable() : Widget()
    {

    }

    void Scrollable::init()
    {
        _box.init(this);
        this->addCssClass("scrollable");

        scrollable()->addOnXScroll([this](double amount){
                    for (auto cb : _onXScroll)
                        cb(amount);
                });

        scrollable()->addOnYScroll([this](double amount){
                    for (auto cb : _onYScroll)
                        cb(amount);
                });
    }

    void Scrollable::setChild(ml::Widget& child)
    {
        child.removeWindow();
        ml::app()->checker().set("can-set-window", true);
        if (this->hasWindow())
            child.setWindow(this->window());
        ml::app()->checker().set("can-set-window", false);
        this->scrollable()->setChild(child);
    }

#include "./Widget_creators_implsc_gen.h"
#include "./Container_creators_implsc_gen.h"
}
