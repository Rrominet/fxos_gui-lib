
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
        if (callback) {
            em::addEventListener(*_dom, "load", [callback](emval event) {
                callback();
            });
        }
        _dom->set("src", filepath);
    }

    //this is sync
    void Image_impl::loadFromMemory(const std::vector<unsigned char>& buf, ImageFormat format)
    {
        //TODO check if it's possible in js ???
    }

    ImageState Image_impl::state()
    {
        // Check if image has loaded by checking if naturalWidth > 0
        int naturalWidth = (*_dom)["naturalWidth"].as<int>();
        if (naturalWidth > 0) {
            return ImageState::Loaded;
        }
        // Check if there's an error
        bool complete = (*_dom)["complete"].as<bool>();
        if (complete && naturalWidth == 0) {
            return ImageState::Error;
        }
        return ImageState::Loading;
    }

    void Image_impl::setWidth(int w)
    {
        em::setCss(*_dom, "width", std::to_string(w) + "px");
    }
}
