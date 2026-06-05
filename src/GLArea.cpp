#include "./GLArea.h"

namespace ml
{
    GLArea::GLArea() : Widget()
    {

    }
    void GLArea::init()
    {
        this->addCssClass("gLArea");
        this->setHExpand();
        this->setVExpand();
    }
}
