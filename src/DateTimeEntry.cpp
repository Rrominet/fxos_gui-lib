#include "./DateTimeEntry.h"

#include "./EventInfos.h"
#include "./EventBlocker.h"
#include "str.h"
#include "mlTime.h"

namespace ml
{

    DateTimeEntry::DateTimeEntry(): Entry()
    {

    }

    void DateTimeEntry::init()
    {
        Entry::init();
        this->addCssClass("time");
        this->setHelp("DateTime format: YYYY-MM-DD - HH:MM:SS");
        _setEvents();
    }

    void DateTimeEntry::_setEvents()
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
                        this->getCursorPosition() == 7 || 
                        this->getCursorPosition() == 11)
                {
                    this->deleteText(this->getCursorPosition(), this->getCursorPosition() + 1);
                    this->insertText("-", this->getCursorPosition());
                    if (this->getCursorPosition() == 11)
                        this->setCursorPosition(this->getCursorPosition() + 2);
                    else
                        this->setCursorPosition(this->getCursorPosition() + 1);
                }

                //YYYY-DD-MM - HH:MM:SS
                else if (this->getCursorPosition() == 10 || this->getCursorPosition() == 12)
                {
                    this->deleteText(this->getCursorPosition(), this->getCursorPosition() + 1);
                    this->insertText(" ", this->getCursorPosition());
                    if (this->getCursorPosition() == 10)
                        this->setCursorPosition(this->getCursorPosition() + 3);
                    else 
                        this->setCursorPosition(this->getCursorPosition() + 1);
                }
                else if (this->getCursorPosition() == 15 || 
                        this->getCursorPosition() == 18)
                {
                    this->deleteText(this->getCursorPosition(), this->getCursorPosition() + 1);
                    this->insertText(":", this->getCursorPosition());
                    this->setCursorPosition(this->getCursorPosition() + 1);
                }

                if (str::isANumber(e.key))
                {
                    this->deleteText(this->getCursorPosition(), this->getCursorPosition() + 1);
                    this->insertText(e.key, this->getCursorPosition());
                    this->setCursorPosition(this->getCursorPosition() + 1);
                }

                if (this->value().size() > 21)
                    this->deleteText(20, this->value().size() - 1);
            }
            this->triggerEvent(CHANGE, e);
        };
        this->addEventListener(KEY_DOWN, kdwn);
    }

    void DateTimeEntry::setFromTime(int64_t time)
    {
        this->setValue(ml::time::asString(time, "%Y-%m-%d - %H:%M:%S")); 
    }

    int64_t DateTimeEntry::asTime()
    {
        return ml::time::fromString(this->value(), "%Y-%m-%d - %H:%M:%S"); 
    }
}
