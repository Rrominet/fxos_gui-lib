
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class Image;
    class Image_impl : public Widget_impl
    {
        public:
            Image_impl(Image* win);
            virtual ~Image_impl();

            virtual void _createWidget() override;

            // this is executed on the mainthread and is async.
            // it use the ResourcesManager::get() function.
            // callback will be executed on the mainthread
            void load(const std::string& filepath, const std::function<void()>& callback = 0);

            //this is sync
            void loadFromMemory(const std::vector<unsigned char>& buf, ImageFormat format);

            ImageState state() const;

            virtual void setWidth(int w) override;
    };
}
