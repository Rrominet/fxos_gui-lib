#include "./MultilineEntry.h"
#include "Input.h"

namespace ml
{
    MultilineEntry::MultilineEntry() : Input()
    {
    }

    void MultilineEntry::init()
    {
        this->addCssClass("multiline-entry");
        this->addCssClass("input");

        this->setHExpand();
        this->setHAlign(ml::FILL);
        this->setVExpand();
    }
}
