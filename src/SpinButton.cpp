
#include "./SpinButton.h"

namespace ml
{
    SpinButton::SpinButton() : Input()
    {

    }
    void SpinButton::init()
    {
        this->addCssClass("spinButton");
        this->addCssClass("input");

        this->setRange(0, 100);
        this->setStep(1);
    }
}
