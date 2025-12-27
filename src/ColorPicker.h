#pragma once
#include "./ComposedWidget.h"
#include "Events.h"
#include "Color.h"

namespace ml
{
    class Box;
    class Slider;
    class ColorPicker : public ComposedWidget
    {
        public:
            ColorPicker(ml::Box* parent);
            virtual ~ColorPicker(){}

            void draw(ml::Box* parent);
            void set(const Color<double>& color){_color = color; _updateGuiFromColor();}
            std::string css();

        private : 
            Events _events; //bp cg
            Color<double> _color; //bp cg
            
            ml::Box* _main;
            ml::Box* _colorBox;
            ml::Box* _rgbaBox;
            ml::Slider* _r;
            ml::Slider* _g;
            ml::Slider* _b;
            ml::Slider* _a;

            void _onSlidersChange();
            void _updateGuiFromColor();

        public : 
#include "./ColorPicker_gen.h"
    };
}
