#pragma once
#include "./Box.h"
#include "./ColorPicker.h"
#include "Color.h"

namespace ml
{
    class Popover;
    class ColorButton : public ml::ComposedInput
    {
        public:
            ColorButton(ml::Box* parent);
            virtual ~ColorButton() = default;

            void draw(ml::Box* parent);
            void setSize(double w, double h){_clickable->setSize(w, h);}

            Color<double>& color(){return _colorPicker->color();}
            Events& events(){return _colorPicker->events();}

            virtual std::any valueAsAny() override;
            virtual void setValue(const std::string& value) override;
            virtual void setValue(double value) override;
            virtual void setValue(const Color<double>& value) override;
            virtual void setValue(const json& value) override;
            

            virtual void addEventListener(Event event, const std::function<void(EventInfos&)>& callback) override;
            virtual void setHelp(const std::string& help) override {_clickable->setHelp(help);}
            virtual void setHAlign(HAlignment align) override {_clickable->setHAlign(align);}
            virtual void setVAlign(VAlignment align) override {_clickable->setVAlign(align);}
            virtual void setHExpand(bool value=true) override {_clickable->setHExpand(value);}
            virtual void setVExpand(bool value=true) override {_clickable->setVExpand(value);}

        private : 
            ml::Box* _clickable;
            ml::Popover* _popover;
            ml::ColorPicker* _colorPicker;
    };
}
