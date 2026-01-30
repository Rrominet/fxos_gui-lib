#pragma once
#include "str.h"
#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/val.h>
#include <functional>
#include "../enums.h"

typedef emscripten::val emval;

namespace em
{
    emval dom();
    emval head();
    emval body();
    emval window();

    // need to call this one if you want to be able to use the addEventListener func below
    emval createElement(const std::string& tag);

    // css classes a separated by spaces
    emval newNode(const emval& parent, const std::string tag, 
            const std::string& html="", 
            const std::string& classes="", 
            const std::string& id="");

    emval newNode(const emval& parent, const std::string tag, 
            emval& child,
            const std::string& classes="", 
            const std::string& id="");

    void show(const emval& dom);
    void hide(const emval& dom);

    void remove(const emval& dom);

    // js equivalents
    unsigned int innerWidth();
    unsigned int innerHeight();

    unsigned int width(const emval& dom);
    unsigned int height(const emval& dom);

    double x(const emval& dom);
    double y(const emval& dom);

    // if the func return true, preventDefault() will be called in JS
    void addEventListener(const emval& dom, ml::Event event, const std::function<bool(const emval&, const EmscriptenMouseEvent*)>& callback, bool useCapture = false);
    void addEventListener(const emval& dom, ml::Event event, const std::function<bool(const emval&, const EmscriptenKeyboardEvent*)>& callback, bool useCapture = false);

    // for other events not directly managed by emscripten.
    void addEventListener(const emval& elmt, 
            const std::string& event,
            const std::function<void(const emval& event)>& callback);
    void addEventListener(const emval& dom, ml::Event event, const std::function<void()>& callback, bool useCapture = false);

    // css classes a separated by spaces
    void addClasses(const emval& dom, const std::string& classes);
    void removeClasses(const emval& dom, const std::string& classes);
    void toggleClasses(const emval& dom, const std::string& classes);
    bool containsClasses(const emval& dom, const std::string& classes);
    std::vector<std::string> classes(const emval& dom);
    void clearClasses(const emval& dom);

    void setCss(const emval& dom, const std::string& attr, const std::string& value);
    void addCss(const emval& dom, const std::string& css);
    void setFocusable(const emval& dom, bool value);

    bool hovered(const emval& dom);
    float fontSize(const emval& dom);
}
