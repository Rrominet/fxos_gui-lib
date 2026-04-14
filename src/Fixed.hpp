#include "./Fixed.h"
#include "./App.h"

namespace ml
{
    template <typename W, typename... Args>
        std::shared_ptr<W> Fixed::createCanvas(Args&&... args)
        {
            return ml::app()->widgetsFactory().createCanvas<W>(this, std::forward<Args>(args)...);
        }
}
