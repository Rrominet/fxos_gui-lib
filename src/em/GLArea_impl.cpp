
#include "./GLArea_impl.h"
#include "../GLArea.h"

namespace ml
{
    GLArea_impl::GLArea_impl(GLArea* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    GLArea_impl::~GLArea_impl()
    {
    }

    void GLArea_impl::_createWidget()
    {
        auto domWidget = em::createElement("gLArea");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "gLArea");
    }
}
