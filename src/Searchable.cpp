#include "./Searchable.h"
#include "./Box.h"
#include "./Entry.h"
#include "enums.h"
#include "str.h"
#include "./SearchableWidget.h"

namespace ml
{
    void Searchable::createSearchInput(ml::Box* parent)
    {
        _searchInput = parent->createEntry();            
        _searchInput->setHelp("Search...");
        _setEvents();
    }

    void Searchable::_setEvents()
    {
        auto f = [this](EventInfos&)
        {
            std::string searched = _searchInput->value();
            searched = str::clean(searched, true);
            this->search(searched);
        };

        auto validf = [this](EventInfos&)
        {
            std::string searched = _searchInput->value();
            searched = str::clean(searched, true);
            this->valid(searched);
        };

        _searchInput->addEventListener(CHANGE, f);
        _searchInput->addEventListener(VALID, validf);
    }

    void Searchable::search(const std::string& searched)
    {
        auto ws = this->searchableWidgets();
        if (searched.empty())
        {
            for (auto& w : ws)
                w->searchMatch();
            _matches = ws;
            return;
        }

        _matches.clear();
        for (auto& w : ws)
        {
            std::string wtxt = str::clean(w->asText(), true);
            if (str::contains(wtxt, searched))
            {
                w->searchMatch();
                _matches.push(w);
            }
            else
                w->searchDontMatch();
        }
    }
}
