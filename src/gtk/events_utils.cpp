#include "./events_utils.h"
#include "../EventInfos.h"

namespace ml 
{
    namespace gtk
    {
        void setModifiersOnEventInfos(const Gdk::ModifierType& state, EventInfos& infos)
        {
            infos.ctrl = (bool)(state & Gdk::ModifierType::CONTROL_MASK);
            infos.alt = (bool)(state & Gdk::ModifierType::ALT_MASK);
            infos.shift = (bool)(state & Gdk::ModifierType::SHIFT_MASK);
            infos.super = (bool)(state & Gdk::ModifierType::META_MASK);
        }
    }
}
