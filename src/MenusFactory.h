#pragma once
#include "./Menu.h"
#include <memory>

namespace ml
{
    class MenusFactory    
    {
        public : 
            MenusFactory() = default;
            virtual ~MenusFactory() = default;

            template <typename M=ml::Menu>
                std::shared_ptr<M> create(const std::string& id, const std::string& name="")
                {
                    auto _r = std::make_shared<M>(id, name);
                    auto _casted = std::dynamic_pointer_cast<ml::Menu>(_r);
                    if (!_casted)
                        assert(false && "Class given in template not a subclass of ml::Menu, not possible.");
                    _menus[id] = _casted;
                    return _r;
                }

            // return the existing one of exists.
            template <typename M=ml::Menu>
                std::shared_ptr<M> createIfItNotExists(const std::string& id, const std::string& name="")
                {
                    if (!this->has(id))
                        return this->create<M>(id, name);
                    return std::dynamic_pointer_cast<M>(_menus[id]);
                }

            bool has(const std::string& id) const {return _menus.find(id) != _menus.end();}

        protected : 
            std::unordered_map<std::string, std::shared_ptr<ml::Menu>> _menus; //bp cg

        public : 
#include "./MenusFactory_gen.h"
    };
}
