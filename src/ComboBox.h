#pragma once
#include <memory>
#include <string>
#include "vec.h"
#include "./ComposedInput.h"

namespace ml
{
    class Box;
    class IconButton;
    class SearchableMenu;
    class ComboBox : public ComposedInput
    {
        public : 
            ComboBox(Box* parent, const std::vector<std::string>& items={});
            virtual ~ComboBox(){}
            void setItems(const std::vector<std::string>& items);
            void addItem(const std::string& item);
            void removeItem(const std::string& item);
            void removeItem(unsigned int index);
            std::string activeItem() const;
            void setActiveItem(const std::string& item);
            void setActiveIndex(int index);
            int activeIndex() const;
            void clear();
            ml::Vec<std::string> items() const {return _items;}

            virtual void setValue(const std::string& value) override;
            virtual void setValue(double value) override;
            virtual std::any valueAsAny() override;

            virtual void addEventListener(Event event, const std::function<void(EventInfos&)>& callback) override;
            virtual void setHAlign(HAlignment align) override;
            virtual void setHExpand(bool value=true) override;

            void showMenu()const;
            std::string menuId()const;
            SearchableMenu* menu()const;


        protected :
            std::shared_ptr<IconButton> _btn;  //bp cg
            std::shared_ptr<SearchableMenu> _menu;  //bp cg
            ml::Vec<std::string> _items;
            int _active = -1;

            void _setEvents();

            ml::Vec<std::function<void(EventInfos&)>> _onChange;
            void _execOnChange();
    };
}
