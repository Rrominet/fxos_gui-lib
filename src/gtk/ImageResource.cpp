#include "./ImageResource.h"
#include "debug.h"
#include <glibmm/fileutils.h>

namespace ml 
{
    void ImageResource::load(const std::string& filepath)
    {
        try
        {
            _buf = Gdk::Pixbuf::create_from_file(filepath);
        }
        catch(const Glib::FileError& e)
        {
            lg("FileError not founded ("<< filepath << ") : " << e.what());
            _state = FILE_NOT_FOUND;
        }
        catch(const Gdk::PixbufError& e)
        {
            lg("Gdk::PixbufError wrong format ("<< filepath << ") : " << e.what());
            _state = WRONG_FORMAT;
        }
        catch(const std::exception& e)
        {
            lg2("can't figure what happens but loading this image failed : ", e.what());
            return;
        }
        _loaded = true;
        _events.emit("loaded", this);
    }
}
