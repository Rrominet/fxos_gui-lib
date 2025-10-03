#pragma once
#include "./Menu.h"
#include "./Searchable.h"

namespace ml
{
    class SearchableMenu : public Menu, public Searchable
    {
        public:
            SearchableMenu(const std::string& id, const std::string& name="");
            virtual ~SearchableMenu(){}

            virtual ml::Vec<std::shared_ptr<SearchableWidget>> searchableWidgets() override;

            virtual void valid(const std::string& searched) override;
    };
}
