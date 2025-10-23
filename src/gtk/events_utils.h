#pragma once
#include <gdkmm/event.h>

namespace ml 
{
    struct EventInfos; 
    namespace gtk
    {
        void setModifiersOnEventInfos(const Gdk::ModifierType& state, EventInfos& infos);
    }
}
