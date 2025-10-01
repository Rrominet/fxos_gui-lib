#pragma once
#include <memory>
#include <string>

// a simple box that can be docked in a "Panels" container
// see class Panels.h
// Don't call it directly, use the factory method(s) in Panels
// You can represent a Panel with PanelInfos class that can be used to create model of a Panel that can be instanced anywhere by the user
// see PanelsManager and Paned for more infos.

namespace ml
{
    class Box;
    class Paned;
    class PanelInfos;
    class Image;
    class SearchableMenu;
    
    class Panel
    {
        friend class Panels;
        friend class Paned;

        public : 
            Panel(Paned* parent);
            ~Panel();
            Paned* _parent;

            void drawFromInfos(PanelInfos* infos);

            // create a paned in its box and create 2 new Panel in it with the current _infos
            // if !_infos, the new panel will we empty.
            void split();

            bool splitted(){return _paned != nullptr;}
            void createPanelsChooserMenu();

        protected : 
            std::shared_ptr<Box> _box; //bp cg

            // could be nullptr, specially if _infos is nullptr
            std::shared_ptr<Box> _header; //bp cg
            std::shared_ptr<Image> _changeIcon; //bp cg

            // used if you want to split the panel in 2 panels
            std::unique_ptr<Paned> _paned;

            // we'll be setted in drawFromInfos
            PanelInfos* _infos = nullptr; //bp cg

            std::shared_ptr<SearchableMenu> _panelsChooser; //bp cg

        public: 
#include "./Panel_gen.h"
    };
}
