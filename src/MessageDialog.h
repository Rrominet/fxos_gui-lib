#pragma once
#include "./Dialog.h"
#include "Events.h"

// you can add event to the event "ok" fired when the user click on the button or enter on the keyboard

namespace ml
{
    class MessageDialog : public Dialog
    {
        friend class WindowsFactory;

        public:
            MessageDialog(App* app) : Dialog(app){}
            MessageDialog(App* app, ml::Window* parent) : Dialog(app, parent){}
            virtual ~MessageDialog() = default;

            virtual void init() override;
            virtual void setMessage(const std::string& message);

            virtual void createMessage();
            virtual void createFooter();

            virtual json serialize() const override;
            virtual void deserialize(const json& j) override;

        protected : 
            std::shared_ptr<Label> _message = nullptr;

            std::string _okBtnText = "Got it !";
            std::shared_ptr<Button> _ok = nullptr;

            Events _events; //bp cg

        public : 
#include "./MessageDialog_gen.h"
    };
}
