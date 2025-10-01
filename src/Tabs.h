#pragma once
#include "vec.h"

namespace ml
{
    class Box;
    class Scrollable;
    class TabButton;
    class Tabs    
    {
        public : 
            Tabs(Box* parent);
            Tabs(Scrollable* parent);
            virtual ~Tabs();

            TabButton* createTab(const std::string& label);
            void removeTab(TabButton* tab);
            void removeTab(const std::string& label);

            void hideAll();
            void show(unsigned int index);

        protected : 
            std::shared_ptr<Box> _header; //bp cg
            std::shared_ptr<Scrollable> _body; //bp cg
            ml::Vec<std::unique_ptr<TabButton>> _tabs;

            void __construct();
            
        public : 
#include "./Tabs_gen.h"
    };
}
