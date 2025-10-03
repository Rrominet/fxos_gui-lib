#include "./TabButton.h"
#include "./Tabs.h"
#include "./Label.h"
#include "./Box.hpp"

namespace ml
{
    TabButton::TabButton(Tabs* tabs, const std::string& text, std::shared_ptr<Box> body)
    {
        _button = tabs->header()->createBox();
        _button->addCssClass("tab-button");
        _button->setOrient(ml::Orient::HORIZONTAL);
        _label = _button->createLabel(text);
        _label->setHAlign(ml::LEFT);
        _label->addCssClass("tab-button-label");
        _button->setCursor("pointer");

        _body = body;
        _body->hide();
    }

    void TabButton::setActive(bool active)
    {
        if (active)
        {
            _button->addCssClass("active");
            _body->show();
        }
        else
        {
            _button->removeCssClass("active");
            _body->hide();
        }
    }
}
