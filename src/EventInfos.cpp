#include "./EventInfos.h"
#include "./App.h"

namespace ml
{
    void EventInfos::stopPropagation()
    {
        auto type = this->type;
        ml::app()->stopEventPropagationMap()[type] = true;
        ml::app()->queue([type]{ml::app()->stopEventPropagationMap()[type] = false;});
    }
}
