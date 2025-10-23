#pragma once
#include <string>

namespace ml
{
    struct EventInfos
    {
        double x, y, dx, dy, mvtx, mvty;
        int click_numbers;
        unsigned int  keyval;
        unsigned int  keycode;
        std::string key;
        bool stopPropagation = false;
        bool preventDefault = true; // this is for JS
        bool ctrl = false, alt = false, shift = false, super = false;
        bool visible = true;
        double width = 0, height = 0;
    };
}
