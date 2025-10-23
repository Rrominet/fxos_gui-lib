
#include "./CheckBox.h"

namespace ml
{
    CheckBox::CheckBox() : Input()
    {

    }
    void CheckBox::init()
    {
        this->addCssClass("checkBox");
        this->addCssClass("input");
        this->setCursor("pointer");
    }
}
