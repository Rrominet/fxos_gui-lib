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
    }

    void ConfirmDialog::createFooter() 
    {
        _cancel = _foot->createButton(_cancelBtnText);
        _cancel->addCssClass("dialog-cancel");
        _cancel->setHAlign(LEFT);

        // this create the OK button.
        MessageDialog::createFooter(); 

        _ok->setHAlign(RIGHT);

        auto cancelf = [this](EventInfos& e)
        {
            _events.emit("cancel");
            this->destroy();
        };

        _cancel->addEventListener(MOUSE_UP, cancelf);
        this->addEventListener(KEY_DOWN, [this, cancelf](EventInfos& e)
                {
                    if (e.key == "Escape")
                        cancelf(e);
                });
    }
}
