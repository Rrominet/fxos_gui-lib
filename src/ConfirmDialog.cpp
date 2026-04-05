#include "./ConfirmDialog.h"
#include "./Button.h"
#include "./EventInfos.h"

namespace ml
{
    void ConfirmDialog::init() 
    {
        IconMessageDialog::init();
        this->setTitle("Confirmation"); //changed
        this->addCssClass("confirm");

        _oncancel = [this](EventInfos&e)
        {
            _events.emit("cancel");
            if (!this->doHideOnClose())
                this->destroy();
            else 
                this->hide();
        };
    }

    void ConfirmDialog::createFooter() 
    {
        _cancel = _foot->createButton(_cancelBtnText);
        _cancel->addCssClass("dialog-cancel");
        _cancel->setHAlign(LEFT);

        // this create the OK button.
        MessageDialog::createFooter(); 

        _ok->setHAlign(RIGHT);
        _cancel->addEventListener(MOUSE_UP, _oncancel);
        this->addEventListener(KEY_DOWN, [this](EventInfos& e)
                {
                    if (e.key == "Escape")
                        _oncancel(e);
                });
    }
}
