#pragma once

#include <cassert>
#include <memory>
#include "./Widget.h"
#include "vec.h"
#include "./enums.h"


#ifdef __EMSCRIPTEN__
#include "./em/Box_impl.h"
#else
#include "./gtk/Box_impl.h"
#endif

namespace ml
{
    class App;
    class Property;
    class PropertyGroup;
    class Command;
    class ComboBox;
    class Canvas;
    template <typename Prop>
        class PropertyWidget;

    template <typename Prop>
        class ComposedPropertyWidget;

    class EnumProperty;
    class ColorProperty;
    class Scrollable;
    class ComposedWidget;
    class Popover;
    class AbsoluteBox;
    class Fixed;
#include "./Widget_types_widgets_classes_gen.h"

    class Box : public Widget
    {
        public : 
            Box();
            virtual ~Box() = default;

            std::shared_ptr<ml::Box_impl> box(){return std::static_pointer_cast<Box_impl>(_impl);}
            std::shared_ptr<ml::Box_impl> box() const{return std::static_pointer_cast<Box_impl>(_impl);}

            void setOrient(Orient orient){this->box()->setOrient(orient);}

            void append(std::shared_ptr<ml::Widget> child);
            void prepend(std::shared_ptr<ml::Widget> child);

            void removeChild(std::shared_ptr<ml::Widget> child);
            void removeChild(ml::Widget* child);
            void removeChild(ml::ComposedWidget* child);

            template <typename Prop>
                std::shared_ptr<PropertyWidget<Prop>> appendProp(Prop* prop, DrawType type = AUTO);

            template <typename Prop>
                std::shared_ptr<ComposedPropertyWidget<Prop>> appendComposedProp(Prop* prop, DrawType type=AUTO);

            // will return nullptr if the child of the type asked is not founded.
            template <typename W>
                std::shared_ptr<W> child(size_t i);

            std::shared_ptr<ml::Box> appendPropertyGroup(ml::PropertyGroup* group);

            // if the type of your prop is NONE, the return ptr will be nullptr
            std::shared_ptr<ml::Box> appendPropBaseClass(Property* prop);

            size_t childrenCount() const {return _children.size() + _composedChildren.size();}

            // swap the order of 2 children;
            // for now, lg if i and j are out of bounds and does nothing
            void swap(size_t i, size_t j);
            void moveChildTop(Widget* child);
            void moveChildBottom(Widget* child);

            bool containsChild(Widget* child);

            virtual void init() override;
            virtual void init(ml::Scrollable* scrollable);

            std::shared_ptr<ml::Button> appendCommand(Command* cmd, const std::string& overrideButtonText="");
            std::shared_ptr<ml::Button> appendCommand(const std::string& id, const std::string& overrideButtonText="");
            std::shared_ptr<ml::Button> addCommand(Command* cmd, const std::string& overrideButtonText=""){return this->appendCommand(cmd, overrideButtonText);}
            std::shared_ptr<ml::Button> addCommand(const std::string& id, const std::string& overrideButtonText=""){return this->appendCommand(id, overrideButtonText);}

            std::shared_ptr<ml::Image> createIconFromName(const std::string& name){return this->createIcon(name);}
            // it's an allias for createIconFromName
            std::shared_ptr<ml::Image> createIcon(const std::string& name);

            std::shared_ptr<ml::Image> createImage(bool icon);

            std::shared_ptr<ml::Image> createIconFromPath(const std::string& filepath);
            std::shared_ptr<ml::Box> createSeparator();

            template <typename W, typename... Args>
                std::shared_ptr<W> createComposedWidget(Args&&... args);

            template <typename W=ml::Canvas, typename... Args>
                std::shared_ptr<W> createCanvas(Args&&... args);

            int childIndex(ml::Widget* child);

            // set the space in pixel in between children
            void setSpacing(int space) {this->box()->setSpacing(space);}
            int spacing() const {return this->box()->spacing();}

            // remove all children in it (deleting their memory)
            void clear();

            std::shared_ptr<ComposedPropertyWidget<EnumProperty>> appendEnumProp(EnumProperty* prop);
            std::shared_ptr<ComposedPropertyWidget<ColorProperty>> appendColorProp(ColorProperty* prop, DrawType type=COLOR_BUTTON);

        protected : 
            ml::Vec<std::shared_ptr<ml::Widget>> _children; //bp cg
            ml::Vec<std::shared_ptr<ml::ComposedWidget>> _composedChildren; //bp cg

        public : 
#include "./Box_gen.h"
#include "./Widget_creators_gen.h"
#include "./Container_creators_gen.h"
    };
}
