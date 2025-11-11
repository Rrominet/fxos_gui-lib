
#update them here if needed.
events = (
        "CLICK",
        "DOUBLE_CLICK",
        "MOUSE_ENTER",
        "MOUSE_LEAVE",
        "MOUSE_MOVE",
        "MOUSE_UP",
        "MOUSE_DOWN",
        "LEFT_UP",
        "LEFT_DOWN",
        "RIGHT_UP",
        "RIGHT_DOWN",
        "MIDDLE_UP",
        "MIDDLE_DOWN",
        "KEY_DOWN",
        "KEY_UP",
        "WHEEL",
        "FOCUS",
        "UNFOCUS",
        "CHANGE",
        "VALID",
        "SHOWN",
        "HIDDEN",
        "RESIZE",
        )

def widget_h(event) : 
    event = event.lower()
    s = "ml::Vec<std::function<void (EventInfos&)>> _*event*;\n"
    s += "bool _*event*_initialized = false;\n"

    s = s.replace("*event*", event)
    return s

def widget_events_trigger(event): 
    eventl = event.lower()
    s = """case(*EVENT*) :
    for (const auto& f : _*event*)
        f(infos);
    break;
"""

    s = s.replace("*EVENT*", event)
    s = s.replace("*event*", eventl)
    return s

def widget_cpp(event) : 
    event_l = event.lower()
    s = """
    case(*event*) :
    {
        _*event_l*.push(callback);
        if (!_*event_l*_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _*event_l*)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _*event_l*_initialized = true;
        }
        break;
    }
    """

    s = s.replace("*event_l*", event_l)
    s = s.replace("*event*", event)
    return s

def get() : 
    all_h = ""
    all_cpp = ""
    trigger_cpp = ""

    for event in events : 
        all_h += widget_h(event)
        all_cpp += widget_cpp(event)
        trigger_cpp += widget_events_trigger(event)

    return all_h, all_cpp, trigger_cpp
