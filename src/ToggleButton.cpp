
#include "./ToggleButton.h"

namespace ml
{
    ToggleButton::ToggleButton() : Input()
    {

    }
    void ToggleButton::init()
    {
        this->addCssClass("button");
        this->addCssClass("toggle");
        this->setHAlign(ml::CENTER);
        this->setCursor("pointer");
    }
}
