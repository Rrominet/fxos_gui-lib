#include "./GLArea_impl.h"
#include "../GLArea.h"

namespace ml
{
    GLArea_impl::GLArea_impl(GLArea* abstract) : Widget_impl((Widget*)abstract)
    {
    }
    void GLArea_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::GLArea>();
        auto area = this->gLArea();
        area->set_auto_render(true);
        area->set_use_es(false);

        auto onrealize = [area, this]()
        {
            area->make_current();
            area->throw_if_error();
#ifdef mydebug
            std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;
            std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
            std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
#endif
            lg("Open GL area realized.");
            for (const auto& f : static_cast<GLArea*>(_abstract)->onOpenGLReady())
                f();
        };

        auto onunrealize = [area, this]()
        {
            area->make_current();
            area->throw_if_error();
            lg("Open GL area unrealized.");
            for (const auto& f : static_cast<GLArea*>(_abstract)->onOpenGLDestroyed())
                f();
        };

        auto onrender = [area, this](const Glib::RefPtr<Gdk::GLContext>& ctx)
        {
            area->throw_if_error();
            for (const auto& f : static_cast<GLArea*>(_abstract)->onRender())
                f();
            return true;
        };
        area->signal_realize().connect(onrealize);
        area->signal_unrealize().connect(onunrealize, false);
        area->signal_render().connect(onrender, false);
    }
}
