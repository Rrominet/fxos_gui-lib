#include <iostream>
#include "./App.h"
#include "debug.h"
#include "./ExampleWindow.h"
#include <thread>
#include "./App.hpp"

int main(int argc, char *argv[])
{
    ml::App* app = new ml::App(argc, argv);
    auto w = app->createMainWindow<ml::ExampleWindow>();
    w->setTitle("My first Window");
    app->run();
    lg("runned.");

// we do not delete the app to keep the widgets alive and to not execute their remove methods after main is finished (because in emscripten, App::run() is not blocking !)
#ifdef __EMSCRIPTEN__
#else 
    delete app; 
#endif
    return 0;
}
