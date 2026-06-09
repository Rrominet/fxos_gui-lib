#pragma once
#include "./ComposedWidget.h"

namespace ml
{
    class Box;
    class Label;
    class Spinner;
    class Scrollable;
    class Popover;

    class ComposedButton : public ComposedWidget
    {
        public:
            ComposedButton(Box* parent, const std::string& label="");
            ComposedButton(Scrollable* parent, const std::string& label="");
            ComposedButton(Popover* parent, const std::string& label="");
            ~ComposedButton() {}

            void setText(const std::string& text);
            void setValue(const std::string& text);
            std::string text();
            std::string value();

            void mkLoading();
            void stopLoading();
            bool isLoading();
            void toggleLoading();

        protected : 
            std::shared_ptr<ml::Box> _box;
            std::shared_ptr<ml::Label> _label;
            std::shared_ptr<ml::Spinner> _spinner;

            void __construct(Box* parent, const std::string& label="");
    };
}
