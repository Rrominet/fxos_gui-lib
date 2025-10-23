#include "./ProgressDialog.h"
#include "./Button.h"
#include "./EventInfos.h"
#include "./enums.h"
#include "./Label.h"

namespace ml
{
    void ProgressDialog::init()
    {
        Dialog::init();
        this->setTitle("Working...");
        this->addCssClass("progress");
        this->createMessage();
        this->createProgress();
        this->createFooter();

        this->setSize(640, 230);
    }

    void ProgressDialog::createProgress()
    {
        _progress = _main->createProgressBar();
        _progress->setHAlign(FILL);
        _progress->setVAlign(VCENTER);
    }

    void ProgressDialog::createFooter()
    {
        _cancel = _foot->createButton(_cancelBtnText);
        _cancel->addCssClass("dialog-cancel");
        _cancel->setHAlign(FILL);
        auto f = [this](EventInfos& e)
        {
            _events.emit("cancel");
            this->destroy();
        };
        _cancel->addEventListener(MOUSE_UP, f);
        this->addEventListener(KEY_DOWN, [this, f](EventInfos&e)
                {
                    if (e.key == "Esc")
                        f(e);
                });

        _foot->setVAlign(BOTTOM);
        _foot->setHAlign(FILL);
    }

    json ProgressDialog::serialize() const
    {
        json _r = MessageDialog::serialize();
        _r["value"] = _progress->value();
        return _r;
    }

    void ProgressDialog::deserialize(const json& j)
    {
        MessageDialog::deserialize(j);
        if (j.contains("value"))
            this->setProgress(j["value"].get<double>());
    }

    void ProgressDialog::setMessage(const std::string& message)
    {
        _message->setText(message);
    }
}
