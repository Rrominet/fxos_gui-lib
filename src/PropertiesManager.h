#pragma once
#include "vec.h"
#include "./Property.h"
#include "./PropertyGroup.h"

namespace ml
{
    class PropertiesManager
    {
        public : 
            PropertiesManager(){};
            virtual ~PropertiesManager(){};

            template <typename T, typename... Args>
            T* create(Args&&... args)
            {
                auto prop = std::make_unique<T>(std::forward<Args>(args)...);
                _props.push_back(std::move(prop));
                return (T*)_props.back().get();
            }

            template <typename... Args>
            Property* createFromType(Property::PropertyType type, Args&&... args)
            {
                std::unique_ptr<Property> prop = nullptr;
                switch (type)
                {
                    case Property::BOOL : 
                        prop = std::make_unique<BoolProperty>(std::forward<Args>(args)...);
                        break;
                    case Property::INT : 
                        prop = std::make_unique<IntProperty>(std::forward<Args>(args)...);
                        break;
                    case Property::FLOAT : 
                        prop = std::make_unique<FloatProperty>(std::forward<Args>(args)...);
                        break;
                    case Property::DOUBLE : 
                        prop = std::make_unique<DoubleProperty>(std::forward<Args>(args)...);
                        break;
                    case Property::STRING : 
                        prop = std::make_unique<StringProperty>(std::forward<Args>(args)...);
                        break;
                    case Property::IMG: 
                        //tmp
                        prop = std::make_unique<StringProperty>(std::forward<Args>(args)...);
                        break;
                    case Property::NONE : 
                        assert(false && "PropertiesManager::createFromType called with the type NONE");
                        break;
                }
                _props.push_back(std::move(prop));
                return _props.back().get();
            }

            PropertyGroup* createGroup(const std::vector<Property*> props = {});

            // always delete prop like this, never with delete;
            void destroy(Property* prop);
            void destroy(PropertyGroup* prop);
            void clear();

        protected :
            ml::Vec<std::unique_ptr<ml::Property>> _props; //bp cg
            ml::Vec<std::unique_ptr<ml::PropertyGroup>> _groups; //bp cg
        public : 
#include "./PropertiesManager_gen.h"
    };
}
