#pragma once
#include "./VerticalTableModel.h"

namespace ml
{
    class VerticalSelectableTableModel : public VerticalTableModel
    {
        public : 
            VerticalSelectableTableModel(){}
            virtual ~VerticalSelectableTableModel(){}

            void select(size_t idx);
            void unselect(size_t idx);

            bool selected(size_t idx) const;

            void clearSelection();

            //to is the final idx included
            void selectRange(size_t from, size_t to);

            void selectAll(){this->selectRange(0, _data.size()-1);}
            void unselectAll(){this->clearSelection();}
            void selectFirst(){this->select(0);}
            void selectLast(){this->select(_data.size() - 1);}

            void selectRangeFromLastSelected(size_t to);

        protected : 
            ml::Vec<size_t> _selected;
            int _lastSelected = -1;
    };
}
