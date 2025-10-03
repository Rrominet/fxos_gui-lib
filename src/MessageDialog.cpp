#include "./MessageDialog.h"
#include "./Label.h"
#include "./Button.h"
#include "./EventInfos.h"

namespace ml
{
    void MessageDialog::init()
    {
        Dialog::init();
        this->setTitle("Message");
        this->addCssClass("message");
        this->createMessage();
        this->createFooter();
    }

    void MessageDialog::createMessage()
    {
        _message = _main->createLabel();
        _message->addCssClass("dialog-message");
        _message->setVExpand(true);
        _message->setVAlign(VCENTER);
    }

    void MessageDialog::createFooter()
    {
        _ok = _foot->createButton(_okBtnText);
        _ok->addCssClass("dialog-ok");
        _ok->setHAlign(FILL);
        _ok->setHExpand(true);
        auto f = [this](EventInfos& e)
        {
            _events.emit("ok");
            this->destroy();
        };
        _ok->addEventListener(MOUSE_UP, f);
        this->addEventListener(KEY_DOWN, [this, f](EventInfos&e)
                {
                    if (e.key == "Return")
                        f(e);
                });

        _foot->setVAlign(BOTTOM);
        _foot->setHAlign(FILL);
    }

    void MessageDialog::setMessage(const std::string& message)
    {
        _message->setText(message);
        this->fitToContent();
    }

    json MessageDialog::serialize() const
    {
        json _r = Window::serialize();
        _r["message"] = _message->text();
        return _r;
    }

    void MessageDialog::deserialize(const json& j)
    {
        Window::deserialize(j);
        if (j.contains("message"))
            this->setMessage(j["message"].get<std::string>());
    }
}
