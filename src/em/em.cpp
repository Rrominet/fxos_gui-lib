#include "em.h"
#include "enums.h"
#include "vec.h"
#include "str.h"
#include <unordered_map>
#include <emscripten/bind.h>

namespace em
{
    std::unordered_map<emval* , std::any> _custom_datas;

    // represent a counter for each dom element created.
    long global_id = 0;

    std::unordered_map<std::string, std::function<bool (const emval&, const EmscriptenMouseEvent*)>> mouse_click;
    std::unordered_map<std::string, std::function<bool (const emval&, const EmscriptenMouseEvent*)>> mouse_up;
    std::unordered_map<std::string, std::function<bool (const emval&, const EmscriptenMouseEvent*)>> mouse_down;
    std::unordered_map<std::string, std::function<bool (const emval&, const EmscriptenMouseEvent*)>> mouse_move;
    std::unordered_map<std::string, std::function<bool (const emval&, const EmscriptenMouseEvent*)>> mouse_enter;
    std::unordered_map<std::string, std::function<bool (const emval&, const EmscriptenMouseEvent*)>> mouse_leave;
    std::unordered_map<std::string, std::function<bool (const emval&, const EmscriptenKeyboardEvent*)>> key_down;
    std::unordered_map<std::string, std::function<bool (const emval&, const EmscriptenKeyboardEvent*)>> key_up;

    std::unordered_map<std::string, std::function<void(emval)>> cbs;
    unsigned int cb_counter = 0;

    std::string registerCb(const std::function<void(emval)>& f)
    {
        std::string key = "callback_" + std::to_string(cb_counter++);
        cbs[key] = f;
        return key;
    }
    // for all events that are not implemented in emscripten
    void triggerCb(const std::string& key, const emval& event)
    {
        cbs[key](event);
    }

    // binding not-managed events to js
    EMSCRIPTEN_BINDINGS(my_module) {
        emscripten::function("triggerCb", &triggerCb);  
    }

    struct Elmt
    {
        std::string id;
        emval elmt;
    };

    EM_BOOL default_mouse_click_cb(int type, const EmscriptenMouseEvent* e, void* userData)
    {
        auto elmt = (Elmt*)userData;
        return mouse_click[elmt->id](elmt->elmt, e);
    }

    EM_BOOL default_mouse_down_cb(int type, const EmscriptenMouseEvent* e, void* userData)
    {
        auto elmt = (Elmt*)userData;
        return mouse_down[elmt->id](elmt->elmt, e);
    }

    EM_BOOL default_mouse_move_cb(int type, const EmscriptenMouseEvent* e, void* userData)
    {
        auto elmt = (Elmt*)userData;
        return mouse_move[elmt->id](elmt->elmt, e);
    }

    EM_BOOL default_mouse_up_cb(int type, const EmscriptenMouseEvent* e, void* userData)
    {
        auto elmt = (Elmt*)userData;
        return mouse_up[elmt->id](elmt->elmt, e);
    }

    EM_BOOL default_mouse_enter_cb(int type, const EmscriptenMouseEvent* e, void* userData)
    {
        auto elmt = (Elmt*)userData;
        return mouse_enter[elmt->id](elmt->elmt, e);
    }

    EM_BOOL default_mouse_leave_cb(int type, const EmscriptenMouseEvent* e, void* userData)
    {
        auto elmt = (Elmt*)userData;
        return mouse_leave[elmt->id](elmt->elmt, e);
    }

    EM_BOOL default_key_down_cb(int type, const EmscriptenKeyboardEvent* e, void* userData)
    {
        auto elmt = (Elmt*)userData;
        return key_down[elmt->id](elmt->elmt, e);
    }

    EM_BOOL default_key_up_cb(int type, const EmscriptenKeyboardEvent* e, void* userData)
    {
        auto elmt = (Elmt*)userData;
        return key_up[elmt->id](elmt->elmt, e);
    }

    void addEventListener(const emval& dom, ml::Event event, const std::function<bool(const emval&, const EmscriptenMouseEvent*)>& callback, bool useCapture)
    {
        auto id = dom["id"].as<std::string>();
        id = "#" + id;
        if (event == ml::Event::CLICK || 
                event == ml::Event::DOUBLE_CLICK || 
                event == ml::Event::MOUSE_DOWN ||
                event == ml::Event::MOUSE_UP ||
                event == ml::Event::MOUSE_MOVE ||
                event == ml::Event::MOUSE_ENTER ||
                event == ml::Event::MOUSE_LEAVE)
        {
            if (event == ml::Event::CLICK)
            {
                mouse_click[id] = callback;
                emscripten_set_click_callback(id.c_str(), (void*)(new Elmt{id, dom}), useCapture, default_mouse_click_cb);
            }
            else if (event == ml::Event::MOUSE_DOWN)
            {
                mouse_down[id] = callback;
                emscripten_set_mousedown_callback(id.c_str(), (void*)(new Elmt{id, dom}), useCapture, default_mouse_down_cb);
            }
            else if (event == ml::Event::MOUSE_UP)
            {
                mouse_up[id] = callback;
                emscripten_set_mouseup_callback(id.c_str(), (void*)(new Elmt{id, dom}), useCapture, default_mouse_up_cb);
            }
            else if (event == ml::Event::MOUSE_MOVE)
            {
                mouse_move[id] = callback;
                emscripten_set_mousemove_callback(id.c_str(), (void*)(new Elmt{id, dom}), useCapture, default_mouse_move_cb);
            }
            else if (event == ml::Event::MOUSE_ENTER)
            {
                mouse_enter[id] = callback;
                emscripten_set_mouseenter_callback(id.c_str(), (void*)(new Elmt{id, dom}), useCapture, default_mouse_enter_cb);
            }
            else if (event == ml::Event::MOUSE_LEAVE)
            {
                mouse_leave[id] = callback;
                emscripten_set_mouseleave_callback(id.c_str(), (void*)(new Elmt{id, dom}), useCapture, default_mouse_leave_cb);
            }
        }
    }

    void addEventListener(const emval& dom, ml::Event event, const std::function<bool(const emval&, const EmscriptenKeyboardEvent*)>& callback, bool useCapture)
    {
        auto id = dom["id"].as<std::string>();
        id = "#" + id;

        switch(event)
        {
            case ml::Event::KEY_DOWN:
                key_down[id] = callback;
                emscripten_set_keydown_callback(id.c_str(), (void*)(new Elmt{id, dom}), useCapture, default_key_down_cb);
                break;
            case ml::Event::KEY_UP:
                key_up[id] = callback;
                emscripten_set_keyup_callback(id.c_str(), (void*)(new Elmt{id, dom}), useCapture, default_key_up_cb);
                break;
        }
    }

    void addEventListener(const emval& elmt, 
            const std::string& event,
            const std::function<void(const emval& event)>& callback) 
    {
        auto key = registerCb(callback);
        // Create a JavaScript function that wraps the triggerCallback with the key
        emval jsFunc = emscripten::val::global("Function").new_((std::string)"key", (std::string)"event",
                (std::string)"Module.triggerCb(key, event);"
                ).call<emval>("bind", emval::global(), key); 
        elmt.call<void>("addEventListener", event, jsFunc);
    }

    void addEventListener(const emval& dom, ml::Event event, const std::function<void()>& callback, bool useCapture )
    {
        switch(event)
        {
            case ml::Event::CHANGE :
                addEventListener(dom, "input", [callback](const emval& event){callback();});
            case ml::Event::VALID :
                addEventListener(dom, "change", [callback](const emval& event){callback();});
        }
    }

    emval dom(){return emval::global("document");}
    emval head(){return dom()["head"];}
    emval body(){return dom()["body"];}
    emval window(){return emval::global("window");}

    emval createElement(const std::string& tag)
    {
        auto node = dom().call<emval>("createElement", tag);
        node.set("id", tag + "_" + std::to_string(global_id++));
        return node;
    }

    emval newNode(const emval& parent, const std::string tag, 
            const std::string& html, 
            const std::string& classes,
            const std::string& id)
    {
        auto node = dom().call<emval>("createElement", tag);
        parent.call<void>("appendChild", node);
        node.set("id", tag + "_" + std::to_string(global_id++));

        if (!classes.empty())
        {
            auto _tmp = str::split(classes, " ");
            for (const auto& c : _tmp)
                node["classList"].call<void>("add", c);
        }

        if (!html.empty())
            node.set("innerHTML", html);

        return node;
    }

    void show(const emval& dom)
    {
        dom["style"].set("display", "");
    }

    void hide(const emval& dom)
    {
        dom["style"].set("display", "none");
    }

    void remove(const emval& dom)
    {
        dom["parentNode"].call<void>("removeChild", dom);
    }

    unsigned int innerWidth()
    {
        return window()["innerWidth"].as<unsigned int>();
    }

    unsigned int innerHeight()
    {
        return window()["innerHeight"].as<unsigned int>();
    }

    unsigned int width(const emval& dom)
    {
        return dom["clientWidth"].as<unsigned int>();
    }
    unsigned int height(const emval& dom)
    {
        return dom["clientHeight"].as<unsigned int>();
    }

    double x(const emval& dom)
    {
        auto rect = dom.call<emval>("getBoundingClientRect");
        return rect["x"].as<double>();
    }
    double y(const emval& dom)
    {
        auto rect = dom.call<emval>("getBoundingClientRect");
        return rect["y"].as<double>();
    }

    void addClasses(const emval& dom, const std::string& classes)
    {
        auto _tmp = str::split(classes, ",");
        for (auto& c : _tmp)
            dom["classList"].call<void>("add", c);
    }

    void removeClasses(const emval& dom, const std::string& classes)
    {
        auto _tmp = str::split(classes, ",");
        for (auto& c : _tmp)
            dom["classList"].call<void>("remove", c);
    }

    void toggleClasses(const emval& dom, const std::string& classes)
    {
        auto _tmp = str::split(classes, ",");
        for (auto& c : _tmp)
        {
            bool contains = dom["classList"].call<bool>("contains", c);
            if (!contains)
                dom["classList"].call<void>("add", c);
            else
                dom["classList"].call<void>("remove", c);
        }
    }

    bool containsClasses(const emval& dom, const std::string& classes)
    {
        auto _tmp = str::split(classes, ",");
        for (auto& c : _tmp)
        {
            bool contains = dom["classList"].call<bool>("contains", c);
            if (contains)
                return contains;
        }
        return false;
    }

    std::vector<std::string> classes(const emval& dom)
    {
        std::vector<std::string> result;
        auto classList = dom["classList"];
        unsigned int length = classList["length"].as<unsigned int>();
        for (unsigned int i = 0; i < length; i++)
        {
            result.push_back(classList[i].as<std::string>());
        }
        return result;
    }

    void clearClasses(const emval& dom)
    {
        removeClasses(dom, classes(dom));
    }

    void addCss(const emval& dom, const std::string& css)
    {
        element["style"].set("cssText", val(css));
    }

    //set the css dynamicly, equivalent of js dom.style.attr = "value;"
    void setCss(const emval& dom, const std::string& attr, const std::string& value)
    {
        dom["style"].set(attr, value);
    }

    //set the html attribute tabindex to "1" if value == true, remove it otherwize
    void setFocusable(const emval& dom, bool value)
    {
        if (value)
        {
            dom.call<void>("setAttribute", "tabindex", "1");
        }
        else
        {
            dom.call<void>("removeAttribute", "tabindex");
        }
    }

    bool hovered(const emval& dom)
    {
        return dom.call<bool>("matches", val(":hover"));
    }

    float fontSize(const emval& dom)
    {
        val window = val::global("window");
        val computedStyle = window.call<val>("getComputedStyle", dom);
        std::string fontSize = computedStyle["fontSize"].as<std::string>();

        return std::stof(fontSize);
    }

    void scrollBy(const emval& dom, int x, int y)
    {
        dom.call<int, int>("scrollBy", x, y);
    }

    int scrollTop(const emval& dom)
    {
        return dom["scrollTop"].as<int>();
    }

    int scrollLeft(const emval& dom)
    {
        return dom["scrollLeft"].as<int>();
    }

    void append(const emval& parent, const emval& child)
    {
        parent.call<void>("appendChild", child);
    }

    void prepend(const emval& parent, const emval& child)
    {
        parent.call<void>("prepend", child);
    }

    void insertAfter(const emval& parent, const emval& child, const emval& ref)
    {
        auto nextSibling = ref["nextSibling"];
        if (nextSibling.isNull() || nextSibling.isUndefined())
            parent.call<void>("appendChild", child);
        else
            parent.call<void>("insertBefore", child, nextSibling);
    }

    void insertBefore(const emval& parent, const emval& child, const emval& ref)
    {
        parent.call<void>("insertBefore", child, ref);
    }

    void remove(const emval& parent, const emval& child)
    {
        parent.call<void>("removeChild", child);
    }

    emval& parent(const emval& dom)
    {
        return dom["parentNode"];
    }

    void setCustomData(emval* dom, const std::any& data)
    {
        _customData[dom] = data;    
    }

    std::any& customData(emval* dom)
    {
        if (_customData.find(dom) == _customData.end())
        {
            _customData[dom] = std::any();
            lg("The custom data asked was not found, returning an empty any");
        }
        return _customData[dom];
    }

    void move(const emval& dom, double x, double y)
    {
        dom["style"].set("left", std::to_string(x) + "px");
        dom["style"].set("top", std::to_string(y) + "px");

        setCusomData(&dom, geometry::Point<double>(x, y));
    }

    geometry::Point<double> position(const emval& dom)
    {
        geomtry::Point<double> _r(0, 0);
        try
        {
            auto& any = getCusomData(&dom);
            _r = std::any_cast<geometry::Point<double>>(any);
        }
        catch(const std::exception& e)
        {
            lg("Warning : The cast failed for em::position, returning (0, 0)");
        }

        return _r;    
    }
}

