#pragma once
#include "./MessageDialog.h"
#include "./ProgressBar.h"

namespace ml
{
    class ProgressDialog : public MessageDialog    
    {
        friend class WindowsFactory;

        public:
            ProgressDialog(App* app) : MessageDialog(app) {}
            ProgressDialog(App* app, ml::Window* parent) : MessageDialog(app, parent) {}
            virtual ~ProgressDialog() = default;

            virtual void init() override;
            virtual void createFooter() override;

            virtual json serialize() const override;
            virtual void deserialize(const json& j) override;

            void createProgress();
            void setProgress(double value){_progress->setValue(value);}
            double progress() const{return _progress->value();}

            virtual void setMessage(const std::string& message) override;

        protected : 
            std::shared_ptr<ProgressBar> _progress = nullptr;

            std::string _cancelBtnText = "Cancel";
            std::shared_ptr<Button> _cancel = nullptr;
    };
}
