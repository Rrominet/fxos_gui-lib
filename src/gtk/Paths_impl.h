#pragma once
#include "files.2/files.h"

namespace ml
{
    class Paths_impl
    {
        public:
            std::string root() const;
            std::string lib() const;
            std::string path(const std::string& relative) const;
    };
}
