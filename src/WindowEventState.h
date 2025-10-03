#pragma once
#include <string>

namespace ml
{
    struct WindowEventState    
    {
        double x, y;
        bool alt, ctrl, shift, meta;
        std::string key;
    };
}
