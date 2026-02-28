#include "./keybinds.h"
#include "./EventInfos.h"
#include "str.h"

namespace ml
{
    namespace keybinds
    {
        std::string label(std::string keybind)
        {
            if (keybind.empty())
                return "";
            auto tmp = str::split(keybind, " ");
            if (str::isAMaj(tmp[tmp.size() - 1]))
                keybind = "Shift " + keybind;
            keybind = str::capitalize(keybind);
            return keybind;
        }

        bool match(const std::string& keybind, const EventInfos& e, FocusedType focusedType)
        {
            bool ctrl = keybinds::containsCtrl(keybind);
            bool alt = keybinds::containsAlt(keybind);
            bool super = keybinds::containsSuper(keybind);

            std::string key = keybind;
            key = str::replace(key, "ctrl", "");
            key = str::replace(key, "alt", "");
            key = str::replace(key, "shift", "");
            key = str::replace(key, "super", "");
            key = str::replace(key, " ", "");

            if (str::lower(key) == "enter" || str::lower(key) == "ret" || str::lower(key) == "return")
                key = "Return";

            bool _match = (key == e.key && ctrl == e.ctrl && alt == e.alt && super == e.super);

            if (focusedType == FocusedType::NONE || focusedType == FocusedType::NON_EDITABLE)
                return _match;

            else if (focusedType == FocusedType::ONELINE_EDITABLE || focusedType == FocusedType::MULTILINE_EDITABLE)
            {
                if (!ctrl && !alt && !super)
                    return false;
                if (ctrl && key=="c")
                    return false;
                if (ctrl && key=="v")
                    return false;
                if (ctrl && key=="a")
                    return false;
                if (ctrl && key=="x")
                    return false;
                if (ctrl && key=="z")
                    return false;
                if (ctrl && key=="y")
                    return false;
                if (ctrl && key=="Backspace")
                    return false;
                if (key == "Return" && !ctrl && !alt && !super)
                    return false;
                return _match;
            }

            return _match;
        }

        bool containsAlt(const std::string& keybind)
        {
            return (str::contains(keybind, "alt"));
        }
        bool containsCtrl(const std::string& keybind)
        {
            return (str::contains(keybind, "ctrl"));
        }
        bool containsSuper(const std::string& keybind)
        {
            return (str::contains(keybind, "super"));
        }
        bool containsShift(const std::string& keybind)
        {
            bool _r = false;
            _r = str::contains(keybind, "shift");
            if (_r)
                return _r;
            auto tmp = str::split(keybind, " ");
            return str::isAMaj(tmp[tmp.size() - 1]);
        }
    }

}
