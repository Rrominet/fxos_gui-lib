#pragma once
#include <string>

namespace ml
{
    struct TextStyle
    {
        double size = 12.0;
        bool bold=false;
        bool italic=false;
        bool underline=false;
        bool oblique=false;

        std::string family="sans-serif";
    };
}
