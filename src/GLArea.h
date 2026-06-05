#pragma once
#include "./Widget.h"
#include <functional>
#include "vec.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/GLArea_impl.h"
#else
#include "./gtk/GLArea_impl.h"
#endif

namespace ml
{
    class GLArea : public Widget
    {
        public : 
            GLArea();
            virtual ~GLArea() = default;
            virtual void init() override;

            std::shared_ptr<ml::GLArea_impl> gLArea(){return std::static_pointer_cast<GLArea_impl>(_impl);}
            std::shared_ptr<ml::GLArea_impl> gLArea()const {return std::static_pointer_cast<GLArea_impl>(_impl);}

            void addOnOpenGLReady(const std::function<void()>& f){_onOpenGLReady.push_back(f);}
            void addOnOpenGLDestroyed(const std::function<void()>& f){_onOpenGLDestroyed.push_back(f);}
            void addOnRender(const std::function<void()>& f){_onRender.push_back(f);}

            const ml::Vec<std::function<void()>>& onOpenGLReady() const {return _onOpenGLReady;}
            const ml::Vec<std::function<void()>>& onOpenGLDestroyed() const {return _onOpenGLDestroyed;}
            const ml::Vec<std::function<void()>>& onRender() const {return _onRender;}

            void clearOnOpenGLReady(){_onOpenGLReady.clear();}
            void clearOnOpenGLDestroyed(){_onOpenGLDestroyed.clear();}
            void clearOnRender(){_onRender.clear();}

        protected : 
            ml::Vec<std::function<void()>> _onOpenGLReady;
            ml::Vec<std::function<void()>> _onOpenGLDestroyed;
            ml::Vec<std::function<void()>> _onRender;

    };
}
