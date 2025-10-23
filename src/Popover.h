
#pragma once
#include "./Widget.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/Popover_impl.h"
#else
#include "./gtk/Popover_impl.h"
#endif

namespace ml
{
    class Box;
    class Scrollable;
    class AbsoluteBox;
#include "./Widget_types_widgets_classes_gen.h"

    class Popover : public Widget
    {
        public : 
            Popover();
            virtual ~Popover() = default;
            virtual void init() override;

            std::shared_ptr<ml::Popover_impl> popover(){return std::static_pointer_cast<Popover_impl>(_impl);}
            void setChild(std::shared_ptr<ml::Widget> child);
            void setPosition(float x, float y){this->popover()->setPosition(x, y);}

            void setAutoHide(bool v=true){this->popover()->setAutoHide(v);}
            void setModal(bool v=true){this->popover()->setAutoHide(v);}

        private : 
            std::shared_ptr<ml::Scrollable> _content; //bp cg

        public : 
#include "./Popover_gen.h"
#include "./Widget_creators_gen.h"
#include "./Container_creators_gen.h"
    };
}
