#include "./Image_impl.h"
#include "../Image.h"
#include "../App.h"
#include "enums.h"
#include <gdkmm/pixbufloader.h>

namespace ml
{
    Image_impl::Image_impl(Image* abstract) : Widget_impl((Widget*)abstract)
    {
        _icon = abstract->isIcon();
    }

    void Image_impl::_createWidget()
    {
        lg("Creating the GTK Image/Picture Widget...");
        if (_icon)
        {
            lg("We're an icon, creating a Gtk::Image.");
            _gtk = std::make_shared<Gtk::Image>();
        }
        else 
        {
            lg("We're not an icon, creating a Gtk::Picture.");
            _gtk = std::make_shared<Gtk::Picture>();
            this->picture()->set_keep_aspect_ratio();
            this->picture()->set_halign(Gtk::Align::FILL);
            this->picture()->set_valign(Gtk::Align::FILL);
            this->picture()->set_can_shrink();
            this->picture()->set_content_fit(Gtk::ContentFit::CONTAIN);
        }
    }

    std::shared_ptr<Gtk::Image> Image_impl::image()
    {
        if (_icon)
            return std::static_pointer_cast<Gtk::Image>(_gtk);
        else 
            throw std::runtime_error("Trying to return a Gtk::Image when icon is false.\nReturn a Gtk::Picture instead with picture() method.");
    }
    std::shared_ptr<Gtk::Picture> Image_impl::picture()
    {
        if (!_icon)
            return std::static_pointer_cast<Gtk::Picture>(_gtk);
        else 
            throw std::runtime_error("Trying to return a Gtk::Picture when icon is true.\nReturn a Gtk::Image instead with image() method.");
    }

    void Image_impl::load(const std::string& filepath, const std::function<void()>& callback )
    {
        auto mainthread = [this, callback]()
        {
            lg("Image loaded, excuting callback on mainthread.");
            lg2("_resource", _resource.get());
            if (_icon)
                this->image()->set(_resource->buf());
            else 
                this->picture()->set_pixbuf(_resource->buf());
            if (callback)
                callback();
        };
        auto f = [this, mainthread](Resource* r){
            lg2("Resource in threaded callback", r);
            ml::app()->queue(mainthread);
        };
        _resource = ml::app()->impl().resources().get<ImageResource>(filepath, f);
    }

    void Image_impl::loadFromMemory(const std::vector<unsigned char>& buf, ImageFormat format)
    {
        //TODO do the other format
        if (format == JPEG)
        {
            auto loader = Gdk::PixbufLoader::create("jpeg");
            try
            {
                loader->write(&buf[0], buf.size());
                loader->close();
                if (_icon)
                    this->image()->set(loader->get_pixbuf());
                else 
                    this->picture()->set_pixbuf(loader->get_pixbuf());
            }
            catch(const std::exception& e)
            {
                lg("Error loading image from memory.");
                lg(e.what());
            }
        }
        else 
        {
            throw std::runtime_error("Unsupported image format : " + std::to_string((int)format));
        }
    }

    void Image_impl::setWidth(int w)
    {
        Widget_impl::setWidth(w);
        if (_icon)
            image()->set_pixel_size(w);
    }
}
