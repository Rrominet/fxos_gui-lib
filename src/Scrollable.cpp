#include "./Scrollable.h"
#include "./App.h"

namespace ml
{
    Scrollable::Scrollable() : Widget()
    {
        _containerType = CONTAINER_SCROLLABLE;
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

    std::shared_ptr<ml::LabelValue> Scrollable::labelValue(const std::string& label, const std::string& value){return _box.labelValue(label, value);}

#include "./Widget_creators_implsc_gen.h"
#include "./Container_creators_implsc_gen.h"
}
