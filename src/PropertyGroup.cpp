#include "./PropertyGroup.h"
namespace ml
{

    void PropertyGroup::addOnUpdate(const std::function<void()> f)
    {
        for (auto p : _props)
            p->addOnUpdate(f);
    }
    void PropertyGroup::addOnValid(const std::function<void()> f)
    {
        for (auto p : _props)
            p->addOnValid(f);
    }
}
