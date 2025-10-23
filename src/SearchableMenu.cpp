#include "./SearchableMenu.h"
#include "./SearchableWidget.h"
#include "./MenuButton.h"
#include "./Scrollable.h"
#include "./Entry.h"
#include <memory>

namespace ml
{
    SearchableMenu::SearchableMenu(const std::string& id, const std::string& name) : Menu(id, name), Searchable()
    {
        this->createSearchInput(&_popover->content()->content());
        _events.add("shown", [this]{
                    _searchInput->setValue("");
                });
    }

    ml::Vec<std::shared_ptr<SearchableWidget>> SearchableMenu::searchableWidgets() 
    {
        ml::Vec<std::shared_ptr<SearchableWidget>> _r;
        for (auto w : _buttons)
            _r.push(std::static_pointer_cast<SearchableWidget>(w));
        return _r;
    }

    void SearchableMenu::valid(const std::string& searched)
    {
        lg2("Valid", searched);
        auto& ms = this->matches();
        if (!ms.empty())
        {
            auto mb = std::static_pointer_cast<MenuButton>(ms[0]);
            if (mb->onClick())
                mb->onClick()();
            else 
            {
                lg("No onClick on this MenuButton : " + mb->text());
            }
        }
        else 
        {
            lg("Matches empty.");
        }
    }
}
