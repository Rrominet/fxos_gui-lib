#include "./DateEntry.h"
#include "./enums.h"
#include "mlTime.h"

#include "./App.h"
#include "./App.hpp"
#include "str.h"
#include "./EventInfos.h"
#include "./EventBlocker.h"
#include "mlTime.h"

namespace ml
{
    DateEntry::DateEntry(): Entry()
    {

    }

    void DateEntry::init()
    {
        Entry::init();
        this->addCssClass("date");
        this->setHelp("Date format: YYYY-MM-DD");
        _setEvents();
    }

    void DateEntry::_setEvents()
    {
        auto kdwn = [this](EventInfos& e)
        {
            {
                EventBlocker b(this);
                if (e.key == "BackSpace" || e.ctrl || e.alt || e.key == "Delete")
                {
                    e.preventDefault = false;
                    return;
                }
                else if (e.key.size() > 1)
                    return;

                if (this->getCursorPosition() == 4 || 
                        this->getCursorPosition() == 7)
                {
                    this->deleteText(this->getCursorPosition(), this->getCursorPosition() + 1);
                    this->insertText("-", this->getCursorPosition());
                    this->setCursorPosition(this->getCursorPosition() + 1);
                }

                if (str::isANumber(e.key))
                {
                    this->deleteText(this->getCursorPosition(), this->getCursorPosition() + 1);
                    this->insertText(e.key, this->getCursorPosition());
                    this->setCursorPosition(this->getCursorPosition() + 1);
                }

                if (this->value().size() > 10)
                    this->deleteText(9, this->value().size() - 1);
            }
            this->triggerEvent(CHANGE, e);
        };
        this->addEventListener(KEY_DOWN, kdwn);
    }

    void DateEntry::setFromTime(int64_t time)
    {
        this->setValue(ml::time::asString(time, "%Y-%m-%d")); 
    }

    int64_t DateEntry::asTime()
    {
        return ml::time::fromString(this->value(), "%Y-%m-%d");        
    }

}
