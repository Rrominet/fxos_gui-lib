#pragma once
#include "./em.h"
#include <memory>
#include "../Widget.h"

namespace ml
{
    class Window;
    class Window_impl
    {
        public:
            Window_impl(Window* win);
            virtual ~Window_impl();

            void show();
            void hide();
            std::shared_ptr<emval> window(){assert(_dom); return _dom;}

            virtual void _createWindow();

            void remove();

            void setSize(unsigned int w, unsigned int h);
            void setWidth(unsigned int w);
            void setHeight(unsigned int h);

            // use this to force the css to take over.
            void resetSize();
            void resetPosition();

            // this repace the actual position
            void setPosition(double x, double y);

            // this add to the actual position
            void move(double x, double y);
            void center();

            void setChild(std::shared_ptr<ml::Widget> child);

            void setTitle(const std::string& title);
            std::string title();

            // really specific to window and web system
            void _setBasicEvents();
            void focus();
            void unfocus();

            // this is ambigous, main here means main content OF the window (and not main window of the App)
            void setMainHeight();

            // this is ambigous, main here means main window (and not main content)
            void setMain(bool main);

            void addCssClass(const std::string& cls);
            void removeCssClass(const std::string& cls);

        protected : 
            Window* _win = nullptr;

            // the dom element representing the window
            std::shared_ptr<emval> _dom = nullptr; //bp g
            std::shared_ptr<emval> _titlebar = nullptr; //bp g
            std::shared_ptr<emval> _titlelabel = nullptr; //bp g
            std::shared_ptr<emval> _closeButton = nullptr; //bp g
            std::shared_ptr<emval> _scaleGrabber = nullptr; //bp g

            bool _drawn = false;
            void _draw();

            unsigned int _width = 0; //bp g
            unsigned int _height = 0; //bp g

            double _x = 0; //bp g
            double _y = 0; //bp g
                           //
            double _grabbOffsetX = 0; //bp g
            double _grabbOffsetY = 0; //bp g

            bool _main = false;

        public : 
#include "Window_impl_gen.h"
    };
}
