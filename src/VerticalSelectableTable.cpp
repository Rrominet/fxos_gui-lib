#include "./VerticalSelectableTable.h"
#include "./VerticalTableModel.h"
#include "./VerticalSelectableTableModel.h"
#include "./App.h"

namespace ml
{
    void VerticalSelectableTable::linkToModel(std::shared_ptr<VerticalTableModel> model)
    {
        VerticalTable::linkToModel(model);
        auto selmodel = std::dynamic_pointer_cast<VerticalSelectableTableModel>(model);
        if (!selmodel)
        {
            ml::app()->error("Try to use a VerticalSelectableTable with a VerticalTableModel, you need the Selectable one (VerticalSelectableTableModel) !");
            return;
        }
        
        this->addOnUpdate("added-to-selection", [this](const std::any& a){_onSelected(std::any_cast<size_t>(a));}, _model.get());
        this->addOnUpdate("removed-from-selection", [this](const std::any& a){_onUnselected(std::any_cast<size_t>(a));}, _model.get());
        this->addOnUpdate("selection-cleared", [this](const std::any& a){_onSelectionCleared();}, _model.get());

        _setSelectionEvents();
    }

    void VerticalSelectableTable::_select(VerticalRow* row)
    {
        if (!row->row)	
        {
            lg("->row arrtibute is not setted for Selection, abort.");
            return;
        }
        row->row->addCssClass("selected");
    }

    void VerticalSelectableTable::_unselect(VerticalRow* row)
    {
        if (!row->row)	
        {
            lg("->row arrtibute is not setted for Selection, abort.");
            return;
        }
        row->row->removeCssClass("selected");
    }

    void VerticalSelectableTable::_onSelected(size_t idx)
    {
        auto rr = _row(idx);
        if (!rr.success)
        {
            lg("Error in selection : " + rr.message);
            return;
        }

        auto r = rr.value;
        _select(r);
    }

    void VerticalSelectableTable::_onUnselected(size_t idx)
    {
        auto rr = _row(idx);
        if (!rr.success)
        {
            lg("Error in unselection : " + rr.message);
            return;
        }

        auto r = rr.value;
        _unselect(r);
    }

    void VerticalSelectableTable::_onSelectionCleared()
    {
        for (auto&r : _rows)
        {
            if (r->row)
                r->row->removeCssClass("selected");
        }
    }

    void VerticalSelectableTable::_clearSelectionEvents()
    {
//TODO
    }

    VerticalSelectableTableModel* VerticalSelectableTable::_selmodel() const
    {
        return dynamic_cast<VerticalSelectableTableModel*>(_model.get()) ;
    }

    void VerticalSelectableTable::_setSelectionEvents()
    {
        _clearSelectionEvents() ;
        auto leftclick = [this]{
            auto selmodel = _selmodel();
            if (!selmodel)
                return;
            auto row = std::any_cast<VerticalRow*>(_events.data());

            if (!_tablebox->window()->state().shift && !_tablebox->window()->state().ctrl)
            {
                selmodel->clearSelection();
                selmodel->select(row->model_index);
            }

            else if (!_tablebox->window()->state().shift && _tablebox->window()->state().ctrl)
                selmodel->select(row->model_index);
            else if (_tablebox->window()->state().shift && !_tablebox->window()->state().ctrl)
                selmodel->selectRangeFromLastSelected(row->model_index);
            else if (_tablebox->window()->state().shift && _tablebox->window()->state().ctrl)
                selmodel->unselect(row->model_index);

        };


        //FIXME The event is not added, not know why. Certainly because the parent class is not fully initialized or a shit stuff like that.
        _events.add("row-clicked", leftclick);
    }
}
