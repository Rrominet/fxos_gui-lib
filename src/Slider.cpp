
#include "./Slider.h"

namespace ml
{
    Slider::Slider() : Input()
    {

    }
    void Slider::init()
    {
        this->addCssClass("slider");
        this->addCssClass("input");

        this->setRange(0, 100);
        this->setStep(1);
        this->setCursor("grab");
    }
}
