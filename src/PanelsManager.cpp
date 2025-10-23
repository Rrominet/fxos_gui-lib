#include "./PanelsManager.h"
namespace ml
{
    PanelInfos* PanelsManager::create(const std::string& id, std::function<void(Panel*)> todraw)
    {
        _panelsInfos[id] = std::make_unique<PanelInfos>();
        _panelsInfos[id]->id = id;
        _panelsInfos[id]->todraw.push_back(todraw);
        return _panelsInfos[id].get();
    }

    PanelInfos* PanelsManager::get(const std::string& id) const
    {
        if (_panelsInfos.find(id) == _panelsInfos.end())
        {
            lg2("PanelInfos not found.", id);
            assert(false && "PanelInfos not found.");
        }
        return _panelsInfos.at(id).get(); 
    }

    void PanelsManager::clear()
    {
        _panelsInfos.clear();
    }

    void PanelsManager::remove(const std::string& id)
    {
        _panelsInfos.erase(id);
    }
}
