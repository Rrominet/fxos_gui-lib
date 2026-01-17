#include "./PropertiesManager.h"
namespace ml
{
    PropertyGroup* PropertiesManager::createGroup(const std::vector<Property*> props)
    {
        auto prop = std::make_unique<PropertyGroup>();
        prop->setProps(props);
        _groups.push_back(std::move(prop));
        return (PropertyGroup*)_groups.back().get();
    }

    void PropertiesManager::destroy(Property* prop)
    {
        for (unsigned int i=0; i<_props.length(); i++)
        {
            if (_props[i].get() == prop)
            {
                _props.removeByIndex(i);
                return;
            }
        }
    }

    void PropertiesManager::destroy(PropertyGroup* prop)
    {
        for (unsigned int i=0; i<_groups.length(); i++)
        {
            if (_groups[i].get() == prop)
            {
                _groups.removeByIndex(i);
                return;
            }
        }
    }

    void PropertiesManager::clear()
    {
        _props.clear(); 
        _groups.clear();
    }
}
