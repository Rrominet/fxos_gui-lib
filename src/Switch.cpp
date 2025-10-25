#include "./Switch.h"

namespace ml
{
    Switch::Switch() : Input()
    {

    }
    void Switch::init()
    {
        this->addCssClass("switch");
        this->addCssClass("input");
        this->setHAlign(ml::RIGHT);
        this->setVAlign(ml::VCENTER);
    }
}
