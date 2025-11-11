#include "./VerticalSelectableTableModel.h"
namespace ml
{
    void VerticalSelectableTableModel::select(size_t idx)
    {
        if (_selected.contains(idx))
            return;

        if (_data.size() <= idx)
            return;

        _selected.push(idx);
        _lastSelected = idx;
        this->notify("added-to-selection", idx);
    }

    void VerticalSelectableTableModel::unselect(size_t idx)
    {
        if (!_selected.contains(idx))
            return;

        if (_data.size() <= idx)
            return;

        _selected.remove(idx);
        this->notify("removed-from-selection", idx);
    }

    bool VerticalSelectableTableModel::selected(size_t idx) const
    {
        return _selected.contains(idx);
    }

    void VerticalSelectableTableModel::clearSelection()
    {
        _selected.clear();
        this->notify("selection-cleared");
    }

    void VerticalSelectableTableModel::selectRange(size_t from,size_t to)
    {
        //Maybe this will be a performance problem, may should notify a range event and not all added-to-selection individually
        for (size_t i = from; i<=to; i++)
            this->select(i);
    }

    void VerticalSelectableTableModel::selectRangeFromLastSelected(size_t to)
    {
        if (_lastSelected < 0)
        {
            this->select(to);
            return;
        }
        if (_lastSelected > to)        
            this->selectRange(to, _lastSelected);
        else 
            this->selectRange(_lastSelected, to);
    }
}
