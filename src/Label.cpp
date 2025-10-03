#include "./Label.h"
namespace ml
{
    Label::Label() : Input(){}

    void Label::init()
    {
        this->addCssClass("label");
        this->setHAlign(ml::LEFT);
        this->setWrap();
    }

    void Label::setEllipsizeMode(EllipsizeMode mode)
    {
        this->label()->setEllipsizeMode(mode);
    }

    EllipsizeMode Label::ellipsizeMode()
    {
        return this->label()->ellipsizeMode();
    }
}
