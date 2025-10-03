#pragma once
#include <memory>
#include "./Box.h"
#include "./Scrollable.h"
#include "./Label.h"
#include "./Image.h"
#include "./ComposedWidget.h"

namespace ml
{
    class Image;
    class IconButton : public ComposedWidget
    {
        public : 
            IconButton(Box* parent, const std::string& icon, const std::string& label="", bool inverted=false, bool reversed=false);
            IconButton(Scrollable* parent, const std::string& icon, const std::string& label="", bool inverted=false, bool reversed=false);

            template<typename C>
                void __construct(C* parent, const std::string& icon, const std::string& label="", bool inverted=false, bool reversed=false)
                {
                     _btn = parent->createBox();
                     _btn->setVExpand(false);

                     _btn->addCssClass("button");
                     _btn->addCssClass("icon");
                     _btn->setOrient(Orient::HORIZONTAL);
                     _btn->setFocusable(true);
                     _btn->setCursor("pointer");

                     if (!reversed)
                     {
                         _icon = _btn->createIcon(icon);
                         _label = _btn->createLabel(label);
                     }
                     else 
                     {
                         _label = _btn->createLabel(label);
                         _icon = _btn->createIcon(icon);
                     }

                     _btn->setHAlign(CENTER);

                     if (inverted)
                         _icon->invert();

                     _composed.push_back(_btn.get());
                     _composed.push_back(_icon.get());
                     _composed.push_back(_label.get());
                }


            virtual void addEventListener(Event event, const std::function<void(EventInfos&)>& callback) override;
            virtual void setHAlign(HAlignment align) override;
            virtual void setHExpand(bool value=true) override;

        protected : 
            std::shared_ptr<Box> _btn; //bp cg
            std::shared_ptr<Image> _icon; //bp cg
            std::shared_ptr<Label> _label; //bp cg
        public : 
#include "./IconButton_gen.h"
    };
}
