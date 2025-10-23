#include "./VerticalTableModel.h"
#include "VerticalTable.h"
namespace ml
{
    void VerticalTableModel::setAttributes(const ml::Vec<std::pair<std::string,Property::PropertyType>>& attributes)
    {
        _attributes = attributes;
        this->notify("attributes-changed");
    }

    void VerticalTableModel::addAttribute(const std::pair<std::string,Property::PropertyType>& attribute)
    {
        _attributes.push_back(attribute);
        this->notify("attributes-added", attribute);
    }

    void VerticalTableModel::removeAttribute(const std::string& name)
    {
        for (int i = 0; i < _attributes.size(); i++)
        {
            if (_attributes[i].first == name)
            {
                _attributes.vec.erase(_attributes.begin() + i);
                this->notify("attributes-removed", name);
                return;
            }
        }
    }

    void VerticalTableModel::removeAttribute(unsigned int index)
    {
        _attributes.vec.erase(_attributes.begin() + index);
        this->notify("attributes-removed-idx", index);
    }

    void VerticalTableModel::setData(const ml::Vec<json>& data)
    {
        _data = data;
        this->notify("data-changed");
    }

    void VerticalTableModel::addToData(const json& data)
    {
        _data.push_back(data);
        this->notify("data-added", data);
    }

    void VerticalTableModel::prependToData(const json& data)
    {
        _data.vec.insert(_data.begin(), data);
        this->notify("data-prepended", data);
    }

    void VerticalTableModel::removeFromData(unsigned int index)
    {
        _data.vec.erase(_data.begin() + index);
        this->notify("data-removed", index);
    }

    void VerticalTableModel::removeFromDataIf(const std::function<bool(const json&)>& callback)
    {
        for (unsigned int i = 0; i < _data.size(); i++)
        {
            if (callback(_data[i]))
            {
                _data.vec.erase(_data.begin() + i);
                this->notify("data-removed", i);
                i--;
            }
        }
    }

    void VerticalTableModel::modifyDataIf(const std::function<bool(json&)>& callback, const json& data)
    {
        for (unsigned int i = 0; i < _data.size(); i++)
        {
            if (callback(_data[i]))
            {
                _data[i] = data;
                this->notify("data-modified", std::pair<unsigned int, json>(i, data));
            }
        }
    }
}
