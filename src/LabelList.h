#pragma once
#include "./List.h"
#include "./Label.h"

namespace ml
{
    template <bool>
        class LabelList;

    template <bool Dynamic=false> 
        class LabelListItem
        {
            public :
                LabelListItem(LabelList<Dynamic>* parent, const std::string& text)
                {
                    _label = parent->listbox()->createLabel(text).get();
                }

                std::string text() const {return _label->text();}
                std::string searchStr() const {return _label->searchStr();}
                ml::Label* gui() const {return _label;}

            protected : 
                ml::Label* _label = nullptr;
        };

    template<bool Dynamic = false>
        class LabelList : public List<ml::LabelListItem<Dynamic>, Dynamic>
    {
        public:
            LabelList(ml::Box* parent, bool search = true) : List<ml::LabelListItem<Dynamic>, Dynamic>(parent, search) {}
            LabelList(ml::Scrollable* parent, bool search = true) : List<ml::LabelListItem<Dynamic>, Dynamic>(parent, search) {}
            LabelList(std::shared_ptr<ml::Box> parent, bool search = true) : List<ml::LabelListItem<Dynamic>, Dynamic>(parent, search) {}
            LabelList(std::shared_ptr<ml::Scrollable> parent, bool search = true) : List<ml::LabelListItem<Dynamic>, Dynamic>(parent, search) {}

            virtual ~LabelList() = default;

            void remove(const std::string& labelText)
            {
                for (auto& item : this->elmts())
                {
                    if (item->text() == labelText)
                    {
                        this->remove(item);
                        return;
                    }
                }
            }

            bool contains(const std::string& labelText)
            {
                for (auto& item : this->elmts())
                {
                    if (item->text() == labelText)
                        return true;
                }
                return false;
            }
    };
}
