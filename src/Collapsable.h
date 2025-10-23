#pragma once
#include <memory>
#include "./ComposedWidget.h"

namespace ml
{
    class Box;
    class Image;
    class Label;
    class Collapsable : public ComposedWidget
    {
        public : 
            Collapsable(Box* parent, const std::string& name, bool collapsed=false);

            void toggle();
            void collapse();
            void expand();

            bool collapsed();

            virtual void addEventListener(Event event, const std::function<void(EventInfos&)>& callback) override;

        protected : 
            std::shared_ptr<Box> _box; //bp cg
            std::shared_ptr<Box> _header; //bp cg
            std::shared_ptr<Label> _label; //bp cg
            std::shared_ptr<Box> _body; //bp cg
            std::shared_ptr<Image> _collapsedIcon;
            std::shared_ptr<Image> _uncollapsedIcon;

            void _setEvents();

        public : 
#include "./Collapsable_gen.h"
    };
}
