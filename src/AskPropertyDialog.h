#pragma once
#include "./Property.h"
#include "./ConfirmDialog.h"

namespace ml
{
    class AskPropertyDialog : public ConfirmDialog
    {
        public : 
            // you can use prop = nullptr to force the Dialog to create it and own it (create it and delete it when the dialog is destroyed.)
            // if not, the prop will just be drawn and not deleted when the dialog is.
            AskPropertyDialog(App* app);
            AskPropertyDialog(App* app, ml::Window* parent);
            virtual ~AskPropertyDialog();
            std::any value();

            void set(Property::PropertyType type, const std::string&propname, const std::string& propdesc="");
            void set(Property* prop);

            // should be called after all is setted.
            // after the init() call from its parent class and after the set() call
            // if uoi don't call it the prop will not be shown in the dialog.
            void drawProp();

            Property* prop()const {return _prop;}

            virtual void init() override;

        protected : 
            bool _setCalled = false;
            bool _ownProp = true;
            Property* _prop = nullptr;
    };
}
