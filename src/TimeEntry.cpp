#include "./TimeEntry.h"

#include "./EventInfos.h"
#include "./EventBlocker.h"
#include "./str.h"

namespace ml
{
    TimeEntry::TimeEntry(): Entry()
    {

    }

    void TimeEntry::init()
    {
        Entry::init();
        this->addCssClass("time");
        this->setHelp("Time format: HH:MM:SS");
        _setEvents();
    }

    void TimeEntry::_setEvents()
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

                if (this->getCursorPosition() == 2 || 
                        this->getCursorPosition() == 5)
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

                if (this->value().size() > 8)
                    this->deleteText(7, this->value().size() - 1);
            }
            this->triggerEvent(CHANGE, e);
        };
        this->addEventListener(KEY_DOWN, kdwn);
    }
}
