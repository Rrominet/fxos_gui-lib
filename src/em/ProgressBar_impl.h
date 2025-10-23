
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class ProgressBar;
    class ProgressBar_impl : public Widget_impl
    {
        public:
            ProgressBar_impl(ProgressBar* win);
            virtual ~ProgressBar_impl(){}

            virtual void _createWidget() override;
            double value();
            void setValue(const double& value);

            std::string text() override ;
            void setText(const std::string& text) override;
    };
}
