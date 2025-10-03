#pragma once
#include "./SearchableWidget.h"
#include "./Box.h"
#include <memory>
#include <functional>
#include <string>

namespace ml
{
    class Box;
    class Label;
    class Scrollable;
    class MenuButton : public SearchableWidget
    {
        public : 
            MenuButton(ml::Scrollable* box, const std::string& text="", const std::function<void()>& onClick=0, const std::string& keybind="");
            MenuButton(ml::Box* box, const std::string& text="", const std::function<void()>& onClick=0, const std::string& keybind="");

            virtual ~MenuButton();

            std::string text() const;
            void setText(const std::string& text);

            std::string keybind() const ;
            void setKeybind(const std::string& text);

            void remove();

            //What is the text that is returned by this widget to be searched
            virtual std::string asText() const override;

            virtual void searchMatch() override {_button->show();}
            virtual void searchDontMatch() override {_button->hide();}

        protected : 
            std::function<void()> _onClick = 0; //bp cgs
            std::shared_ptr<Box> _button; //bp cg
            std::shared_ptr<Label> _label; //bp cg
            std::shared_ptr<Label> _keybind; 

            void __construct(const std::string& text, const std::function<void()>& onClick=0, const std::string& keybind="");

        public : 
#include "./MenuButton_gen.h"
    };
}
