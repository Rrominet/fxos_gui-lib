
#include "./Popover.h"
#include "./App.h"

namespace ml
{
    Popover::Popover() : Widget()
    {

    }

    void Popover::init()
    {
        this->addCssClass("popover");
        _content = ml::app()->widgetsFactory().createScrollable(this);
    }

    void Popover::setChild(std::shared_ptr<ml::Widget> child)
    {
        ml::app()->checker().set("can-set-window", true);
        if (this->hasWindow())
            child->setWindow(this->window());
        ml::app()->checker().set("can-set-window", false);
        this->popover()->setChild(child);
        child->setParent(&_content->content());
    }

}

#include "./creators_implpopover_gen.h"
