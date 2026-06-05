#pragma once
#include <gtkmm/glarea.h>
#include <epoxy/gl.h>
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class GLArea;
    class GLArea_impl : public Widget_impl
    {
        public:
            GLArea_impl(GLArea* abstract);
            virtual ~GLArea_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::GLArea> gLArea(){return std::static_pointer_cast<Gtk::GLArea>(_gtk);}
            std::shared_ptr<Gtk::GLArea> gLArea() const{return std::static_pointer_cast<Gtk::GLArea>(_gtk);}
    };
}
