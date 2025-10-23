#include "./Image.h"
#include "./App.h"

namespace ml
{
    Image::Image(bool icon) : Widget(), _icon(icon)
    {

    }
    void Image::init()
    {
        this->addCssClass("image");
        this->setHExpand();
        this->setVExpand();
    }

    void Image::load(const std::string& filepath, const std::function<void()>& callback)
    {
        std::string fullpath = ml::app()->paths().path(filepath);
        auto cb = [this, callback](){
            _state = this->state();
            if (_state == IMG_NORMAL)
            {
                _empty = false;
                if (callback) 
                    callback();
            }
            else if (_state == FILE_NOT_FOUND) 
            {
                this->setHelp("Image file not founded.");
                this->load("images/missing-image.png");
            }
            else if (_state == WRONG_FORMAT)
            {
                this->setHelp("Image format not supported.");
                this->load("images/wrong-format.png");
            }
        };
        this->image()->load(fullpath, cb);
    }
}
