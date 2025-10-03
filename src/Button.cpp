#include "./Button.h"
namespace ml
{
    Button::Button() : Widget(){}
    void Button::init()
    {
        this->addCssClass("button");
        this->setHAlign(ml::CENTER);
    }
}
