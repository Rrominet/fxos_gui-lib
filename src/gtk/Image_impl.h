
#pragma once
#include <gtkmm/image.h>
#include <gtkmm/picture.h>
#include <memory>
#include "./Widget_impl.h"
#include "./ImageResource.h"
#include "../enums.h"

namespace ml
{
    class Image;
    class Image_impl : public Widget_impl
    {
        public:
            Image_impl(Image* abstract);
            virtual ~Image_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::Image> image();
            std::shared_ptr<Gtk::Picture> picture();

            // this is executed on the mainthread and is async.
            // it use the ResourcesManager::get() function.
            // callback will be executed on the mainthread
            void load(const std::string& filepath, const std::function<void()>& callback = 0);

            //this is sync
            void loadFromMemory(const std::vector<unsigned char>& buf, ImageFormat format);

            ImageState state() const {return _resource->state();}

            virtual void setWidth(int w) override;

        protected : 
            bool _icon = true;
            std::shared_ptr<ImageResource> _resource = nullptr;
    };
}
