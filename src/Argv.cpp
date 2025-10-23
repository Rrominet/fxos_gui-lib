#include "./Argv.h"
#include "str.h"

namespace ml
{
    bool Argv::has(const std::string& key)
    {
        return _argv.find(key) != _argv.end();
    }

    void Argv::setPropFromArg(ml::Property* prop, const std::string& key)
    {
        if (!this->has(key))
            return;

        switch (prop->type())
        {
            case Property::NONE : 
                break;
            case Property::BOOL:
                prop->set(str::asBool(_argv.at(key)));
                break;
            case Property::INT:
                prop->set(str::asInt(_argv.at(key)));
                break;
            case Property::FLOAT:
                prop->set(str::asFloat(_argv.at(key)));
                break;
            case Property::DOUBLE:
                prop->set(str::asDouble(_argv.at(key)));
                break;
            case Property::STRING:
                prop->set(_argv.at(key));
                break;
            case Property::IMG:
                break;
        }
    }
}
