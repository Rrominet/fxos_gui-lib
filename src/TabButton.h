#pragma once
#include <memory>


namespace ml
{
    class Box;
    class Label;
    class Tabs;
    class TabButton
    {
        public : 
            TabButton(Tabs* tabs, const std::string& text, std::shared_ptr<Box> body);
            virtual ~TabButton() = default;

            // this show or hide its content too.
            void setActive(bool active);
        protected : 
            bool _active = false; //pb cg
            std::shared_ptr<Box> _body; //bp cg 
            std::shared_ptr<Box> _button; //bp cg
            std::shared_ptr<Label> _label; //bp cg
                                  
        public : 
#include "./TabButton_gen.h"
    };
}

