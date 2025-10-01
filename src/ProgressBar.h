
#pragma once
#include "./Input.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/ProgressBar_impl.h"
#else
#include "./gtk/ProgressBar_impl.h"
#endif

namespace ml
{
    class ProgressBar : public Input
    {
        public : 
            ProgressBar();
            virtual ~ProgressBar() = default;
            virtual void init() override;

            std::shared_ptr<ml::ProgressBar_impl> progressBar(){return std::static_pointer_cast<ProgressBar_impl>(_impl);}

            double value(){return progressBar()->value();}
            virtual std::any valueAsAny() override { return this->value(); }
            virtual void setValue(double value) override;
            virtual void setValue(const std::string& value) override {this->setValue(std::stod(value));}

            std::string text() override {return progressBar()->text();}
            void setText(const std::string& text) override {progressBar()->setText(text);}

            virtual void setRange(double min, double max) override;

        protected : 
            double _min=0, _max=1;
    };
}
