#include "./Scrollable.h"
#include "./Box.hpp"

namespace ml
{
    template <typename W>
        std::shared_ptr<W> Scrollable::child(size_t i)
        {
            return _box.child<W>(i);
        }

    template <typename Prop>
        std::shared_ptr<PropertyWidget<Prop>> Scrollable::appendProp(Prop* prop, DrawType type)
        {
            return _box.appendProp(prop, type);
        }

    template <typename W, typename... Args>
        std::shared_ptr<W> Scrollable::createComposedWidget(Args&&... args)
        {
            return _box.createComposedWidget<W>(std::forward<Args>(args)...);
        }

    template <typename Prop>
        std::shared_ptr<ComposedPropertyWidget<Prop>> Scrollable::appendComposedProp(Prop* prop, DrawType type)
        {
            return std::make_shared<ComposedPropertyWidget<Prop>>(&_box, prop, type);
        }

    template <typename W, typename... Args>
        std::shared_ptr<W> Scrollable::createCanvas(Args&&... args)
        {
            return ml::app()->widgetsFactory().createCanvas<W>(this, std::forward<Args>(args)...);
        }

}
