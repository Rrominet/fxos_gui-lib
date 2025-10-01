#pragma once
#include "./MessageDialog.h"

namespace ml
{
    class Spinner;
    class WorkDialog : public MessageDialog    
    {
        friend class WindowsFactory;

        public:
            enum State
            {
                NOT_LOADING = 0,
                LOADING,
            };

            WorkDialog(App* app) : MessageDialog(app) {}
            WorkDialog(App* app, ml::Window* parent) : MessageDialog(app, parent) {}
            virtual ~WorkDialog() = default;

            virtual void init() override;
            virtual void createFooter() override;

            virtual json serialize() const override;
            virtual void deserialize(const json& j) override;

            State state() const {return _state;}
            void setState(State state);

            void createSpinner();
            void adaptUI();

        protected : 
            std::shared_ptr<Spinner> _spinner = nullptr;

            std::string _cancelBtnText = "Cancel";
            std::shared_ptr<Button> _cancel = nullptr;

            State _state = NOT_LOADING;
    };
}
