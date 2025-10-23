#pragma once
#include <memory>
#include "vec.h"
#include "./Property.h"

namespace ml
{
    class PropertyGroup
    {
        protected : 
            ml::Vec<Property*> _props; //bp cgs

        public : 
            template<typename T>
                T* get(const std::string& name)
            {
                for (auto p : _props)
                {
                    if (p->name() == name)
                        return (T*)p;
                }
                return nullptr;
            }
        public : 
#include "./PropertyGroup_gen.h"
    };
}
