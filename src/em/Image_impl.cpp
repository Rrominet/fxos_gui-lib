
#include "./Image_impl.h"
#include "../Image.h"
#include "em/em.h"

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

    void Image_impl::load(const std::string& filepath, const std::function<void()>& callback)
    {
        //TODO : Check how to add the addeventlistener on load
        _dom->set("src", filepath);
    }

    //this is sync
    void Image_impl::loadFromMemory(const std::vector<unsigned char>& buf, ImageFormat format)
    {
        //TODO check if it's possible in js ???
    }

    ImageState state()
    {

    }

    void Image_impl::setWidth(int w)
    {
        em::setCss(*_dom, "width", std::to_string(w) + "px")
    }
}
