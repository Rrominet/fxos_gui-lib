#pragma once
#include "./VerticalTable.h"
#include <memory>

namespace ml
{
    class VerticalTableModel;
    class VerticalSelectableTableModel;
    class VerticalSelectableTable : public VerticalTable
    {
        public : 
            VerticalSelectableTable(Box* parent) : VerticalTable(parent){}
            virtual ~VerticalSelectableTable(){}

            virtual void linkToModel(std::shared_ptr<VerticalTableModel> model ) override;

        private : 
            void _clearSelectionEvents();
            void _setSelectionEvents();

            void _onSelected(size_t idx);
            void _onUnselected(size_t idx);
            void _onSelectionCleared();

            void _select(VerticalRow* row);
            void _unselect(VerticalRow* row);

            VerticalSelectableTableModel* _selmodel() const;
    };
}
