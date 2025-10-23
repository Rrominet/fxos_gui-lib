
#include "./Spinner.h"

namespace ml
{
    Spinner::Spinner() : Widget()
    {

    }
    void Spinner::init()
    {
        this->addCssClass("spinner");
    }
}
