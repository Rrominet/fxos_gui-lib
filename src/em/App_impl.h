#pragma once
#include "em.h"

namespace ml
{
    class App;
    class Window_impl;
    class App_impl
    {
        public:
            App_impl(App* app){_app = app;}
            App_impl(App* app, int argc, char *argv[]){_app = app;}
            virtual ~App_impl() = default;

            void init();
            void setEvents();
            void run();
            void unfocusAll();

            bool onWindowMove(const EmscriptenMouseEvent* e);
            bool onWindowScaled(const EmscriptenMouseEvent* e);
            //changed

            // can't quit app in a browser.
            void quit() const{}

        private : 
            App* _app = nullptr;
            Window_impl* _grabbed = nullptr; //bp gs
            Window_impl* _scaleGrabbed = nullptr; //bp gs

        public:
            #include "./App_impl_gen.h"
    };
}
