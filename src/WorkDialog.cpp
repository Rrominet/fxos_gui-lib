#include "./WorkDialog.h"
#include "./Spinner.h"
#include "./Button.h"
#include "./EventInfos.h"
#include "./enums.h"
#include "./Label.h"

namespace ml
{
    void WorkDialog::init()
    {
        Dialog::init();
        this->setTitle("Working...");
        this->addCssClass("work");
        this->createMessage();
        this->createSpinner();
        this->createFooter();
        this->adaptUI();
    }

    void WorkDialog::createSpinner()
    {
        _spinner = _main->createSpinner();
        _spinner->setHAlign(RIGHT);
        _spinner->setVAlign(VCENTER);
        _spinner->setRightMargin(30);
        _spinner->hide();
    }

    void WorkDialog::adaptUI()
    {
        _main->setOrient(ml::HORIZONTAL);
        _message->setHExpand();
        _message->setHAlign(LEFT);
    }

    void WorkDialog::createFooter()
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

    json WorkDialog::serialize() const
    {
        json _r = MessageDialog::serialize();
        if (_state == LOADING)
            _r["state"] = "loading";
        else
            _r["state"] = "not-loading";
        return _r;
    }

    void WorkDialog::deserialize(const json& j)
    {
        MessageDialog::deserialize(j);
        if (j.contains("state"))
        {
            if (j["state"].get<std::string>() == "loading")
                this->setState(LOADING);
            else
                this->setState(NOT_LOADING);
        }
    }

    void WorkDialog::setState(State state)
    {
        _state = state;
        if (_state == LOADING)
            _spinner->show();
        else
            _spinner->hide();

        this->fitToContent();
    }
}
