#pragma once
#include <gdkmm/pixbuf.h>
#include "files.2/ResourcesManager.h"
#include "../enums.h"
//this class is only a Resource that represent an image in gtk (specially a pixbuf)
//

namespace ml
{
    class ImageResource : public Resource
    {
        public:
            virtual void load(const std::string& filepath) override;
            Glib::RefPtr<Gdk::Pixbuf> buf() 
            {
                if (!_loaded) throw std::runtime_error("ImageResource::buf(), Resource not loaded yet.");
                return _buf;
            }

            ImageState state() const
            {
                return _state;
            }

        protected : 
            Glib::RefPtr<Gdk::Pixbuf> _buf;
            ImageState _state = IMG_NORMAL;

    };
}
