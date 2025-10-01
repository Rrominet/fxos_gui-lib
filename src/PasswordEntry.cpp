
#include "./PasswordEntry.h"

namespace ml
{
    PasswordEntry::PasswordEntry() : Input()
    {

    }
    void PasswordEntry::init()
    {
        this->addCssClass("passwordEntry");
        this->addCssClass("input");
    }
}
