#pragma once
#include <string>
#include <functional>
#include "vec.h"
//Represent the infos needed to instanciate a Panel.
//Specially used in a Paned.
//created with the a PanelsManager instance, not instanciated directly.
//(do not call it with new or make_unique/shared)

namespace ml
{
    class Panel;
    class PanelInfos
    {
        public:
            PanelInfos() = default;
            ~PanelInfos() = default;

            std::string id;
            ml::Vec<std::function<void(Panel*)>> todraw;
    };
}
