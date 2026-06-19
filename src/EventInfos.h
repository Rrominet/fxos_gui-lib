#pragma once
#include <string>
#include "./enums.h"

namespace ml
{
    struct EventInfos
    {
        double x, y, dx, dy, mvtx, mvty;
        int click_numbers = -1;
        unsigned int keyval;
        unsigned int keycode;
        std::string key;
#ifdef __EMSCRIPTEN__
        bool preventDefault = false; // this is for JS (works a bit in gtk actually)
#else
        bool preventDefault = true; // this is for JS (works a bit in gtk actually)
#endif
        bool ctrl = false, alt = false, shift = false, super = false;
        bool visible = true;
        double width = 0, height = 0;
        Event type = NONE;

        void stopPropagation();
    };
}
