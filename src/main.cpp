#include <iostream>
#include "./App.h"
#include "debug.h"
#ifdef __EMSCRIPTEN__
#include "./ExampleWindow_em.h"
#else
#include "./ExampleWindow_gtk.h"
#endif
#include <thread>
#include "./App.hpp"


#ifdef __EMSCRIPTEN__
std::unique_ptr<ml::App> app_ptr;
#endif

int main(int argc, char *argv[])
{
#ifdef __EMSCRIPTEN__
    app_ptr = std::make_unique<ml::App>(argc, argv);
    ml::App& app = *app_ptr;
#else
    ml::App app(argc, argv);
#endif

    auto w = app.createMainWindow<ml::ExampleWindow>();
    w->setTitle("My first Window");
    app.run();
    lg("runned.");

#ifdef __EMSCRIPTEN__
    emscripten_exit_with_live_runtime();
#endif
    return 0;
}


