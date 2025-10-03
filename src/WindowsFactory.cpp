#include "./WindowsFactory.h"
#include "str.h"
#include "./App.h"
#include "./App.hpp"

namespace ml
{
    std::string WindowsFactory::_newId() const
    {
        std::string id = str::random(24);
        if (ml::app()->windowExists(id))
            id = str::random(24);
        return id;
    }
}
