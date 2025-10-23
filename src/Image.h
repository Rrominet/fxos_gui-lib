
#pragma once
#include "./Widget.h"
#include "./enums.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/Image_impl.h"
#else
#include "./gtk/Image_impl.h"
#endif

namespace ml
{
    class Image : public Widget
    {
        public : 
            //if icon is true, It will use Gtk::Image in gtk backend
            //Gtk::Image help with icon display, having them always square and optimized.
            //if not it will use Gtk::Picture
            //
            //In em, we'll try to implement the same behavior
            Image(bool icon=true);

            virtual ~Image() = default;
            virtual void init() override;

            //callback will allways be executed on the mainthread.
            void load(const std::string& filepath, const std::function<void()>& callback = 0);
            std::shared_ptr<ml::Image_impl> image(){return std::static_pointer_cast<Image_impl>(_impl);}
            std::shared_ptr<ml::Image_impl> image() const{return std::static_pointer_cast<Image_impl>(_impl);}

            void invert(){this->addCssClass("invert");}

            //this is sync
            void loadFromMemory(const std::vector<unsigned char>& buf, ImageFormat format){this->image()->loadFromMemory(buf, format); _empty = false;}

            bool isIcon(){return _icon;}

        protected : 
            bool _icon = true;
            std::string _filepath; //bp cg
            ImageState _state = IMG_NORMAL; //bp cg
            bool _empty = true; //bp cg

        public : 
#include "./Image_gen.h"
    };
}
