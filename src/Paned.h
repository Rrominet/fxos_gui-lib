#pragma once
#include <memory>
#include "./enums.h"

//See PanelsManager to know to use this.

//TODO : should be serializable so the user can retreive its workspace even if he close the app.

namespace ml
{
    class Box;
    class Panel;
    class Menu;
    class PanelInfos;
    class Paned 
    {
        public : 
            Paned(Box* parent);
            virtual ~Paned();

            Panel* createFirst();
            Panel* createSecond();

            Panel* createFirstFromInfos(PanelInfos* infos);
            Panel* createSecondFromInfos(PanelInfos* infos);

            void setOrient(Orient orient);

            void removeFirst();
            void removeSecond();

            // swap the first and second panel
            void swap();
            void changeOrient();

            // will create the second panel that will be used as a copy as the firt panelInfos
            // if no PanelInfos was used to create the first one, it will be just empty.
            // if the first panel is nullptr and not the second, the first will becreate from the second one Infos
            // if the second panel has already beed created, it will replace the hovered Paneld with another Paned and split it again.
            void split();

            // keep the active panel, remove the other one.
            void merge();

            void setRatio(float ratio);

            // could return nullptr if no active
            Panel* active();

        protected : 
            std::shared_ptr<Box> _box; //bp cg
            std::shared_ptr<Panel> _first = nullptr; //bp cg
            std::shared_ptr<Panel> _second = nullptr; //bp cg
            std::shared_ptr<Menu> _ctx; //bp cg
            Orient _orient = HORIZONTAL; //bp cg

            float _ratio = 0.5; //bp cg
            void _setEvents();
            bool _aPanelHovered();

            std::shared_ptr<Panel> _createPanel();
            void _remove(Panel* panel);

            bool _dragging = false;

            // 0 for first, 1 for second
            int _active = -1;

        public : 
            #include "./Paned_gen.h"
    };
}
