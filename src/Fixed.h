#pragma once
#include "./Widget.h"
#include"geometry.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/Fixed_impl.h"
#else
#include "./gtk/Fixed_impl.h"
#endif

namespace ml
{
    class ComposedWidget;
    class Box;
    class AbsoluteBox;
    class Scrollable;
    class Popover;

#include "./Widget_types_widgets_classes_gen.h"
    class Fixed : public Widget
    {
        public : 
            Fixed();
            virtual ~Fixed() = default;
            virtual void init() override;

            std::shared_ptr<ml::Fixed_impl> fixed(){return std::static_pointer_cast<Fixed_impl>(_impl);}
            std::shared_ptr<ml::Fixed_impl> fixed() const{return std::static_pointer_cast<Fixed_impl>(_impl);}

            void append(std::shared_ptr<ml::Widget> child);
            void removeChild(std::shared_ptr<ml::Widget> child);
            void removeChild(ml::Widget* child);
            void removeChild(ml::ComposedWidget* child);

            template <typename W>
                std::shared_ptr<W> child(size_t i);

            size_t childrenCount() const {return _children.size(); + _composedChildren.size();}

            bool containsChild(Widget* child);
            int childIndex(ml::Widget* child);
            void clear();

            void moveChild(std::shared_ptr<ml::Widget> w, double x, double y){this->fixed()->move(w.get(),x,y);}
            geometry::Point<double> widgetPos(std::shared_ptr<ml::Widget> w){return this->fixed()->widgetPos(w.get());}

            void moveChild(ml::Widget* w, double x, double y){this->fixed()->move(w,x,y);}
            geometry::Point<double> widgetPos(ml::Widget* w){return this->fixed()->widgetPos(w);}

        protected : 
            ml::Vec<std::shared_ptr<ml::Widget>> _children; //bp cg
            ml::Vec<std::shared_ptr<ml::ComposedWidget>> _composedChildren; //bp cg

        public : 
#include "./Fixed_gen.h"
#include "./Widget_creators_gen.h"
#include "./Container_creators_gen.h"
    };
}
