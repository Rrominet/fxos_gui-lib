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

    std::unordered_map<ml::Event, //event-type, 
        std::unordered_map<std::string, //elmt-id
                ml::Vec<std::function<bool (const emval&, const EmscriptenMouseEvent*)>>
                >
            > mouse_events;

    std::unordered_map<ml::Event, 
        std::unordered_map<std::string, ml::Vec<std::function<bool (const emval&, const EmscriptenKeyboardEvent*)>>>
            > key_events;

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
        ml::Event event;
    };

    EM_BOOL default_mouse_cb(int type, const EmscriptenMouseEvent* e, void* userData)
    {
        lg("Trying to execyte a mouse event callback...");
        auto elmt = (Elmt*)userData;
        lg("Event " << elmt->event << " for elmt " << elmt->id);
        if (mouse_events.find(elmt->event) == mouse_events.end())
        {
            lg("No mouse event found for " << elmt->event);
            return false;
        }
        if (mouse_events[elmt->event].find(elmt->id) == mouse_events[elmt->event].end())
        {
            lg("Event type " << elmt->event << " founded but NOT for elmt " << elmt->id);
            return false;
        }

        bool _r = false;
        for (const auto& f : mouse_events[elmt->event][elmt->id])
        {
            if (elmt->event == ml::Event::LEFT_UP || elmt->event == ml::Event::LEFT_DOWN)
            {
                if (e->button == 0)
                {
                    lg("Executing event for left mouse");
                    _r = f(elmt->elmt, e);
                }
            }

            else if (elmt->event == ml::Event::MIDDLE_UP || elmt->event == ml::Event::MIDDLE_DOWN)
            {
                if (e->button == 1)
                {
                    lg("Executing event for middle mouse");
                    _r = f(elmt->elmt, e);
                }
            }

            else if (elmt->event == ml::Event::RIGHT_UP || elmt->event == ml::Event::RIGHT_DOWN)
            {
                if (e->button == 2)
                {
                    lg("Executing event for right mouse");
                    _r = f(elmt->elmt, e);
                }
            }
            else 
            {
                _r = f(elmt->elmt, e);
            }
        }
        return _r;
    }

    EM_BOOL default_kb_cb(int type, const EmscriptenKeyboardEvent* e, void* userData)
    {
        auto elmt = (Elmt*)userData;
        if (key_events.find(elmt->event) == key_events.end())
            return false;
        if (key_events[elmt->event].find(elmt->id) == key_events[elmt->event].end())
            return false;

        bool _r = false;
        for (const auto& f : key_events[elmt->event][elmt->id])
            _r = f(elmt->elmt, e);
        return _r;
    }

    void addEventListener(const emval& dom, ml::Event event, const std::function<bool(const emval&, const EmscriptenMouseEvent*)>& callback, bool useCapture)
    {
        lg("em::addEventListener(" << &dom << ", " << event << ", " << &callback << ", " << useCapture << ")");
        auto id = dom["id"].as<std::string>();
        id = "#" + id;
        lg("Adding event listener to " << id);
        mouse_events[event][id].push(callback);
        if (event == ml::Event::CLICK)
        {
            lg("Adding click listener to " << id);
            emscripten_set_click_callback(id.c_str(), (void*)(new Elmt{id, dom, event}), useCapture, default_mouse_cb);
        }
        else if (event == ml::Event::MOUSE_UP || event == ml::Event::LEFT_UP || event == ml::Event::RIGHT_UP || event == ml::Event::MIDDLE_UP)
        {
            lg("Adding mouseup listener to " << id);
            emscripten_set_mouseup_callback(id.c_str(), (void*)(new Elmt{id, dom, event}), useCapture, default_mouse_cb);
        }
        else if (event == ml::Event::MOUSE_DOWN || event == ml::Event::LEFT_DOWN || event == ml::Event::RIGHT_DOWN || event == ml::Event::MIDDLE_DOWN)
        {
            lg("Adding mousedown listener to " << id);
            emscripten_set_mousedown_callback(id.c_str(), (void*)(new Elmt{id, dom, event}), useCapture, default_mouse_cb);
        }
        else if (event == ml::Event::DOUBLE_CLICK)
        {
            lg("Adding dblclick listener to " << id);
            emscripten_set_dblclick_callback(id.c_str(), (void*)(new Elmt{id, dom, event}), useCapture, default_mouse_cb);
        }
        else if (event == ml::Event::MOUSE_MOVE)
        {
            lg("Adding mousemove listener to " << id);
            emscripten_set_mousemove_callback(id.c_str(), (void*)(new Elmt{id, dom, event}), useCapture, default_mouse_cb);
        }
        else if (event == ml::Event::MOUSE_ENTER)
        {
            lg("Adding mouseenter listener to " << id);
            emscripten_set_mouseenter_callback(id.c_str(), (void*)(new Elmt{id, dom, event}), useCapture, default_mouse_cb);
        }
        else if (event == ml::Event::MOUSE_LEAVE)
        {
            lg("Adding mouseleave listener to " << id);
            emscripten_set_mouseleave_callback(id.c_str(), (void*)(new Elmt{id, dom, event}), useCapture, default_mouse_cb);
        }
    }

    void addEventListener(const emval& dom, ml::Event event, const std::function<bool(const emval&, const EmscriptenKeyboardEvent*)>& callback, bool useCapture)
    {
        auto id = dom["id"].as<std::string>();
        id = "#" + id;
        key_events[event][id].push(callback);
        if (event == ml::Event::KEY_DOWN)
            emscripten_set_keyup_callback(id.c_str(), (void*)(new Elmt{id, dom, event}), useCapture, default_kb_cb);

        else if (event == ml::Event::KEY_UP)
            emscripten_set_keydown_callback(id.c_str(), (void*)(new Elmt{id, dom, event}), useCapture, default_kb_cb);
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
            case ml::Event::FOCUS : 
                addEventListener(dom, "focus", [callback](const emval& event){callback();});
            case ml::Event::UNFOCUS: 
                addEventListener(dom, "blur", [callback](const emval& event){callback();});
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

    void removeClasses(const emval& dom, const std::string& classes_str)
    {
        auto _tmp = str::split(classes_str, ",");
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
        auto cls = classes(dom);
        for (auto& c : cls)
            dom["classList"].call<void>("remove", c);
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
            dom.call<void>("setAttribute", _S"tabindex", _S"1");
        }
        else
        {
            dom.call<void>("removeAttribute", _S"tabindex");
        }
    }

    bool hovered(const emval& dom)
    {
        return dom.call<bool>("matches", emval(":hover"));
    }

    float fontSize(const emval& dom)
    {
        emval window = emval::global("window");
        emval computedStyle = window.call<emval>("getComputedStyle", dom);
        std::string fontSize = computedStyle["fontSize"].as<std::string>();

        return std::stof(fontSize);
    }

    void scrollBy(const emval& dom, int x, int y)
    {
        dom.call<void>("scrollBy", x, y);
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

    emval parent(const emval& dom)
    {
        return dom["parentNode"];
    }

    void setCustomData(emval* dom, const std::any& data)
    {
        _custom_datas[dom] = data;    
    }

    std::any& customData(emval* dom)
    {
        if (_custom_datas.find(dom) == _custom_datas.end())
        {
            _custom_datas[dom] = std::any();
            lg("The custom data asked was not found, returning an empty any");
        }
        return _custom_datas[dom];
    }

    void move(const emval& dom, double x, double y)
    {
        dom["style"].set("left", std::to_string(x) + "px");
        dom["style"].set("top", std::to_string(y) + "px");

        setCustomData(const_cast<emval*>(&dom), geometry::Point<double>(x, y));
    }

    geometry::Point<double> position(const emval& dom)
    {
        geometry::Point<double> _r(0, 0);
        try
        {
            auto& any = customData(const_cast<emval*>(&dom));
            _r = std::any_cast<geometry::Point<double>>(any);
        }
        catch(const std::exception& e)
        {
            lg("Warning : The cast failed for em::position, returning (0, 0)");
        }

        return _r;    
    }

    long setTimeout(const std::function<void()>& callback, int ms)
    {
        auto* cb = new std::function<void()>(callback);
        return emscripten_set_timeout([](void* userData) {
                auto* f = static_cast<std::function<void()>*>(userData);
                (*f)();
                delete f;
                }, ms, cb);
    }

    long setInterval(const std::function<void()>& callback, int ms)
    {
        auto* cb = new std::function<void()>(callback);
        return emscripten_set_interval([](void* userData) {
                auto* f = static_cast<std::function<void()>*>(userData);
                (*f)();
                delete f;
                }, ms, cb);
    }

    bool isInDom(const emval& elmt)
    {
        if (elmt.isNull() || elmt.isUndefined())
            return false;
        std::string type = elmt["id"].typeOf().as<std::string>();
        if (type != "string")
            return false;
        auto id = elmt["id"].as<std::string>();
        auto founded_dom = dom().call<emval>("getElementById", id);

        if (founded_dom.isNull()|| founded_dom.isUndefined())
            return false;
        return true;
    }
}

