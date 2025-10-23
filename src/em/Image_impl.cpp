
#include "./Image_impl.h"
#include "../Image.h"

namespace ml
{
    Image_impl::Image_impl(Image* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    Image_impl::~Image_impl()
    {
    }

    void Image_impl::_createWidget()
    {
        auto domWidget = em::createElement("image");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "image");
    }
}
