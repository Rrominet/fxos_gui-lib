
#include "./Entry.h"

namespace ml
{
    Entry::Entry(): Input()
    {

    }

    void Entry::init()
    {
        this->addCssClass("entry");
        this->addCssClass("input");
    }
}
