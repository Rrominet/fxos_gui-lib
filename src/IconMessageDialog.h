#pragma once
#include "./MessageDialog.h"

namespace ml
{
    class Box;
    class IconMessageDialog : public MessageDialog
    {
        public:
            IconMessageDialog(App* app) : MessageDialog(app){}
            IconMessageDialog(App* app, ml::Window* parent) : MessageDialog(app, parent){}
            virtual ~IconMessageDialog() = default;

            virtual void init() override;
            virtual void createMessage() override;

        protected : 
            std::string _iconName = "info";
            std::shared_ptr<Box> _message_box = nullptr;

        public : 
    };

    class InfoDialog : public IconMessageDialog
    {
        public:
            InfoDialog(App* app) : IconMessageDialog(app){}
            InfoDialog(App* app, ml::Window* parent) : IconMessageDialog(app, parent){}
            virtual ~InfoDialog() = default;
    };

    class WarningDialog : public IconMessageDialog
    {
        public:
            WarningDialog(App* app) : IconMessageDialog(app){_iconName = "warning";}
            WarningDialog(App* app, ml::Window* parent) : IconMessageDialog(app, parent){_iconName = "warning";}
            virtual ~WarningDialog() = default;
    };

    class ErrorDialog : public IconMessageDialog
    {
        public:
            ErrorDialog(App* app) : IconMessageDialog(app){_iconName = "error";}
            ErrorDialog(App* app, ml::Window* parent) : IconMessageDialog(app, parent){_iconName = "error";}
            virtual ~ErrorDialog() = default;
    };
}
