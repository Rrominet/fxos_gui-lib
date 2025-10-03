#pragma once

#include "observers/Observed.h"
#include "./Property.h"

namespace ml
{
    class VerticalTableModel : public Observed
    {
        public:
            VerticalTableModel() {}
            virtual ~VerticalTableModel() {}

            void setAttributes(const ml::Vec<std::pair<std::string, Property::PropertyType>>& attributes);
            void addAttribute(const std::pair<std::string, Property::PropertyType>& attribute);
            void removeAttribute(const std::string& name);
            void removeAttribute(unsigned int index);

            void setData(const ml::Vec<json>& data);
            void addToData(const json& data);
            void prependToData(const json& data);
            void removeFromData(unsigned int index);
            void removeLastFromData(){this->removeFromData(_data.size() - 1);}
            void removeFirstFromData(){this->removeFromData(0);}

            // the callback run on every element of the data
            // if it returns true, the element is removed
            void removeFromDataIf(const std::function<bool(const json&)>& callback);
            void modifyDataIf(const std::function<bool(json&)>& callback, const json& data);

            const ml::Vec<std::pair<std::string, Property::PropertyType>> attributes() const {return _attributes;}
            const ml::Vec<json>& data() const {return _data;}
            size_t size() const {return _data.size();}

        protected : 
            ml::Vec<std::pair<std::string, Property::PropertyType>> _attributes;
            ml::Vec<json> _data;
    };
}
