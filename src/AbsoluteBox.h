#pragma once
#include "./Widget.h"

#ifdef __EMSCRIPTEN__
#include "./em/AbsoluteBox_impl.h"
#else
#include "./gtk/AbsoluteBox_impl.h"
#endif

namespace ml
{
    class App;
    class Property;
    class PropertyGroup;
    class Command;
    class ComboBox;
    class EnumProperty;
    class Scrollable;
    class ComposedWidget;
    class Popover;
    class Canvas;
    class Box;
    class Fixed;
#include "./Widget_types_widgets_classes_gen.h"

    //the name here is a bit missleading.
    //It's in fact an overlay (Gtk::Overlay) not a Fixed (Gtk::Fixed) like "Absolute" could suggest
    //The Absolute is for the Box position itself not its children
    //If you want to have a fixed/absolute position for your children, use Fixed
    class AbsoluteBox : public Widget
    {
        public:
            AbsoluteBox(){}
            virtual ~AbsoluteBox() = default;

            std::shared_ptr<ml::AbsoluteBox_impl> absolute_box(){return std::static_pointer_cast<AbsoluteBox_impl>(_impl);}
            std::shared_ptr<ml::AbsoluteBox_impl> absolute_box() const{return std::static_pointer_cast<AbsoluteBox_impl>(_impl);}

            void append(std::shared_ptr<ml::Widget> child);
            void prepend(std::shared_ptr<ml::Widget> child);

            void removeChild(std::shared_ptr<ml::Widget> child);
            void removeChild(ml::Widget* child);
            void removeChild(ml::ComposedWidget* child);

            size_t childrenCount() const {return _children.size() + _composedChildren.size();}

            virtual void init() override;
            virtual void init(ml::Scrollable* scrollable);

            std::shared_ptr<ml::Button> appendCommand(Command* cmd);
            std::shared_ptr<ml::Button> appendCommand(const std::string& id);
            std::shared_ptr<ml::Image> createIconFromName(const std::string& name){return this->createIcon(name);}
            // it's an allias for createIconFromName
            std::shared_ptr<ml::Image> createIcon(const std::string& name);

            std::shared_ptr<ml::Image> createIconFromPath(const std::string& filepath);

            template <typename W, typename... Args>
                std::shared_ptr<ml::ComposedWidget> createComposedWidget(Args&&... args);

            template <typename W=ml::Canvas, typename... Args>
                std::shared_ptr<W> createCanvas(Args&&... args);

            int childIndex(ml::Widget* child);

            // remove all children in it (deleting their memory)
            void clear();

            void setBackground(std::shared_ptr<ml::Widget> c){this->absolute_box()->setBackground(c);}
            void removeBackground(){this->absolute_box()->removeBackground();}
            void sendToFront(std::shared_ptr<ml::Widget> c){this->absolute_box()->sendToFront(c.get());}
            void sendToBack(std::shared_ptr<ml::Widget> c){this->absolute_box()->sendToBack(c.get());}
            void moveDepth(std::shared_ptr<ml::Widget> c,unsigned int x){this->absolute_box()->moveDepth(c.get(),x);}

            void setBackground(ml::Widget* c){this->absolute_box()->setBackground(c);}
            void sendToFront(ml::Widget* c){this->absolute_box()->sendToFront(c);}
            void sendToBack(ml::Widget* c){this->absolute_box()->sendToBack(c);}
            void moveDepth(ml::Widget* c,unsigned int x){this->absolute_box()->moveDepth(c,x);}

        protected : 
            ml::Vec<std::shared_ptr<ml::Widget>> _children; //bp cg
            ml::Vec<std::shared_ptr<ml::ComposedWidget>> _composedChildren; //bp cg

        public : 
#include "./AbsoluteBox_gen.h"
#include "./Widget_creators_gen.h"
#include "./Container_creators_gen.h"
    };
}
