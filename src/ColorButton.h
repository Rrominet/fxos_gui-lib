#pragma once
#include "./Box.h"
#include "./ColorPicker.h"
#include "Color.h"

namespace ml
{
    class Popover;
    class ColorButton : public ml::ComposedWidget
    {
        public:
            ColorButton(ml::Box* parent);
            virtual ~ColorButton() = default;

            void draw(ml::Box* parent);
            void setSize(double w, double h){_clickable->setSize(w, h);}

            Color<double>& color(){return _colorPicker->color();}
            Events& events(){return _colorPicker->events();}

        private : 
            ml::Box* _clickable;
            ml::Popover* _popover;
            ml::ColorPicker* _colorPicker;
    };
}
