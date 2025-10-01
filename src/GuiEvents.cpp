#include "./GuiEvents.h"
#include "./App.h"

namespace ml
{
    void GuiEvents::emit(const std::string &type,std::string data)
    {
        auto f = [this, type, data]
        {
            ml::Events::emit(type, data);
        };

        _app->queue(f);
    }

    void GuiEvents::emit(const std::string &type,const std::any& data)
    {
        auto f = [this, type, data]
        {
            ml::Events::emit(type, data);
        };

        _app->queue(f);
    }
}
