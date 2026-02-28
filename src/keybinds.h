#pragma once
#include "str.h"

namespace ml
{
    class EventInfos;
    namespace keybinds
    {
        enum FocusedType
        {
            NONE,
            NON_EDITABLE,
            ONELINE_EDITABLE,
            MULTILINE_EDITABLE,
        };
        std::string label(std::string keybind);
        bool match(const std::string& keybind, const EventInfos& e, FocusedType focusedType = FocusedType::NONE);
        bool containsAlt(const std::string& keybind);
        bool containsCtrl(const std::string& keybind);
        bool containsSuper(const std::string& keybind);
    }
}
