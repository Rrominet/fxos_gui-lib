#pragma once
#include "./PropertyGroup.h"
#include "./ConfirmDialog.h"

namespace ml
{
    class AskPropertyGroupDialog : public ConfirmDialog
    {
        public : 
            // you can use prop = nullptr to force the Dialog to create it and own it (create it and delete it when the dialog is destroyed.)
            // if not, the prop will just be drawn and not deleted when the dialog is.
            AskPropertyGroupDialog(App* app);
            AskPropertyGroupDialog(App* app, ml::Window* parent);
            virtual ~AskPropertyGroupDialog();

            void set(PropertyGroup* prop);

            // should be called after all is setted.
            // after the init() call from its parent class and after the set() call
            // if uoi don't call it the prop will not be shown in the dialog.
            void drawProp();

            PropertyGroup* prop()const {return _prop;}

        protected : 
            bool _setCalled = false;
            PropertyGroup* _prop = nullptr;
    };
}
