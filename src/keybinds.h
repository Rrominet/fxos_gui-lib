#pragma once
#include "str.h"

namespace ml
{
    class EventInfos;
    namespace keybinds
    {
        std::string label(std::string keybind);
        bool match(const std::string& keybind, const EventInfos& e);
    }
}
