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

        bool match(const std::string& keybind, const EventInfos& e)
        {
            bool ctrl = false;
            bool alt = false;
            bool super = false;

            if (str::contains(keybind, "ctrl"))
                ctrl = true;

            if (str::contains(keybind, "alt"))
                alt = true;

            if (str::contains(keybind, "super"))
                super = true;

            std::string key = keybind;
            key = str::replace(key, "ctrl", "");
            key = str::replace(key, "alt", "");
            key = str::replace(key, "shift", "");
            key = str::replace(key, "super", "");
            key = str::replace(key, " ", "");

            lg(e.key);

            if (str::lower(key) == "enter" || str::lower(key) == "ret" || str::lower(key) == "return")
                key = "Return";

            return (key == e.key && ctrl == e.ctrl && alt == e.alt && super == e.super);
        }
    }

}
