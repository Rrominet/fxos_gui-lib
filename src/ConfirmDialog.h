#pragma once
#include "./IconMessageDialog.h"

//_events emit two events : 
// - ok : fired when the user click on the button _ok or enter on the keyboard
// - cancel : fired when the user click on the button _cancel or hit esc on the keyboard

namespace ml
{
    class ConfirmDialog : public IconMessageDialog    
    {
        public:
            ConfirmDialog(App* app) : IconMessageDialog(app){ _iconName = "question"; _okBtnText = "Yes";}
            ConfirmDialog(App* app, ml::Window* parent) : IconMessageDialog(app, parent){ _iconName = "question"; _okBtnText = "Yes";}
            virtual ~ConfirmDialog() = default;

            virtual void init() override;
            virtual void createFooter() override;

        protected : 
            std::string _cancelBtnText = "Cancel";
            std::shared_ptr<Button> _cancel = nullptr;
    };
}
