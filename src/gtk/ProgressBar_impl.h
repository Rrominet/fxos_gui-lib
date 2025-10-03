
#pragma once
#include <gtkmm/progressbar.h>
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class ProgressBar;
    class ProgressBar_impl : public Widget_impl
    {
        public:
            ProgressBar_impl(ProgressBar* abstract);
            virtual ~ProgressBar_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::ProgressBar> progressBar(){return std::static_pointer_cast<Gtk::ProgressBar>(_gtk);}

            double value(){return progressBar()->get_fraction();}
            void setValue(const double& value){progressBar()->set_fraction(value);}

            std::string text(){return progressBar()->get_text();}
            void setText(const std::string& text){progressBar()->set_text(text);}
    };
}
