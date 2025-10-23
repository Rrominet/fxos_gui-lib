#pragma once
#include <string>
#include <map>
#include "./Property.h"

namespace ml
{
    class Argv
    {
        public : 
            Argv(const std::map<std::string, std::string>& map) : _argv(map){}
            virtual ~Argv() = default;

            bool has(const std::string& key);
            void setPropFromArg(ml::Property* prop, const std::string& key);

            const std::map<std::string, std::string>& argv()const{return _argv;}
            bool empty() const {return _argv.empty();}
            size_t size() const noexcept {return _argv.size();}

            std::map<std::string, std::string>::const_iterator find(const std::string& key) const{return _argv.find(key);}
            const std::string& operator[](const std::string& key) const {
                return _argv.at(key);
            }

            const std::string& at(const std::string& key) const {return _argv.at(key);}

            std::map<std::string, std::string>::const_iterator end() const {
                return _argv.end();
            }

        private : 
            const std::map<std::string, std::string>& _argv;
    };
}

