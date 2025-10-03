#include "./IconMessageDialog.h"
#include "./Image.h"

namespace ml
{
    void IconMessageDialog::init()
    {
        MessageDialog::init();
        this->addCssClass("icon");
    }
    void IconMessageDialog::createMessage()
    {
        _message_box = _main->createBox();
        _message_box->addCssClass("dialog-message");
        _message_box->setVExpand(true);
        _message_box->setVAlign(VCENTER);
        _message_box->setHExpand(true);
        _message_box->setOrient(HORIZONTAL);
        auto icon = _message_box->createIcon(_iconName);
        icon->setWidth(48);
        if (_iconName == "info" || _iconName == "question")
            icon->invert();
        _message = _message_box->createLabel();
    }
}
