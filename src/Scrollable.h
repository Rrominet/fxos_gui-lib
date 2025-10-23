#pragma once
#include "./Box.h"

#ifdef __EMSCRIPTEN__
#include "./em/Scrollable_impl.h"
#else
#include "./gtk/Scrollable_impl.h"
#endif

namespace ml
{
    class Scrollable : public Widget
    {
        public:
            Scrollable();
            virtual ~Scrollable() = default;

            virtual void init() override;

            std::shared_ptr<ml::Box_impl> box(){return _box.box();}
            std::shared_ptr<ml::Scrollable_impl> scrollable(){return std::static_pointer_cast<ml::Scrollable_impl>(_impl);}
            std::shared_ptr<ml::Scrollable_impl> scrollable() const {return std::static_pointer_cast<ml::Scrollable_impl>(_impl);}

            void setOrient(Orient orient){_box.setOrient(orient);}

            void append(std::shared_ptr<ml::Widget> child){_box.append(child);}
            void prepend(std::shared_ptr<ml::Widget> child){_box.prepend(child);}

            void removeChild(std::shared_ptr<ml::Widget> child){_box.removeChild(child);}
            void removeChild(ml::Widget* child){_box.removeChild(child);}

            template <typename W>
                std::shared_ptr<W> child(size_t i);

            template <typename Prop>
                std::shared_ptr<PropertyWidget<Prop>> appendProp(Prop* prop, DrawType type = AUTO);

            template <typename Prop>
                std::shared_ptr<ComposedPropertyWidget<Prop>> appendComposedProp(Prop* prop, DrawType type = AUTO);

            void setChild(ml::Widget& child);
            std::shared_ptr<ml::Button> appendCommand(Command* cmd){return _box.appendCommand(cmd);}
            std::shared_ptr<ml::Button> appendCommand(const std::string& id){return _box.appendCommand(id);}

            Box& content(){return _box;}

            std::shared_ptr<ml::Image> createIcon(const std::string& name){return _box.createIcon(name);}
            std::shared_ptr<ml::Box> createSeparator(){return _box.createSeparator();}

            std::shared_ptr<ml::Box> appendPropBaseClass(Property* prop){return _box.appendPropBaseClass(prop);}
            std::shared_ptr<ml::Box> appendPropertyGroup(PropertyGroup* prop){return _box.appendPropertyGroup(prop);}

            std::shared_ptr<ComposedPropertyWidget<EnumProperty>> appendEnumProp(EnumProperty* prop){return _box.appendEnumProp(prop);}

            template <typename W, typename... Args>
                std::shared_ptr<W> createComposedWidget(Args&&... args);

            template <typename W=ml::Canvas, typename... Args>
                std::shared_ptr<W> createCanvas(Args&&... args);

            void scrollDown(double amount){scrollable()->scrollDown(amount);}
            void scrollUp(double amount){scrollable()->scrollUp(amount);}
            void scrollLeft(double amount){scrollable()->scrollLeft(amount);}
            void scrollRight(double amount){scrollable()->scrollRight(amount);}

            void addOnXScroll(const std::function<void(double)>& cb){_onXScroll.push_back(cb);}
            void addOnYScroll(const std::function<void(double)>& cb){_onYScroll.push_back(cb);}

            void clearOnXScroll(){_onXScroll.clear();}
            void clearOnYScroll(){_onYScroll.clear();}

            double scrollX()const {return scrollable()->scrollX();}
            double scrollY()const {return scrollable()->scrollY();}

        protected : 
            ml::Vec<std::function<void(double)>> _onXScroll;
            ml::Vec<std::function<void(double)>> _onYScroll;

        private : 
            Box _box;

        public: 
#include "./Widget_creators_gen.h"
#include "./Container_creators_gen.h"
    };
}
