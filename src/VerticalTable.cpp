#include "./VerticalTable.h"
#include "./Box.h"
#include "./VerticalTableModel.h"

#include "./Box.hpp"
#include "./enums.h"

namespace ml
{
    VerticalTable::VerticalTable(Box* parent)
    {
        _tablebox = parent->createBox();
        _tablebox->setOrient(Orient::VERTICAL);
        _tablebox->addCssClass("vertical-table");

        _headerRow = _tablebox->createBox();
        _headerRow->setOrient(Orient::HORIZONTAL);
        _headerRow->addCssClass("vertical-table-header");

        _datascroll = _tablebox->createScrollable();
        _datascroll->setOrient(Orient::VERTICAL);
        _datascroll->addCssClass("vertical-table-body");

        _headEmpty = _datascroll->createBox();
        _headEmpty->setOrient(Orient::VERTICAL);
        _headEmpty->addCssClass("vertical-empty-head");
        _headEmpty->setHExpand();

        _databox = _datascroll->createBox();
        _databox->setOrient(Orient::VERTICAL);
        _databox->addCssClass("vertical-table-content");
        _databox->setHExpand();

        _footEmpty = _datascroll->createBox();
        _footEmpty->setOrient(Orient::VERTICAL);
        _footEmpty->addCssClass("vertical-empty-foot");
        _footEmpty->setHExpand();

        _composed.push_back(_tablebox.get());
        _rows.resize(this->max_row_size());
        for (unsigned int i = 0; i < this->max_row_size(); i++)
            _rows[i] = std::make_unique<VerticalRow>();

        _setEvents();
    }

    VerticalTable::~VerticalTable(){}

    void VerticalTable::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        _tablebox->addEventListener(event, callback);
    }

    void VerticalTable::linkToModel(std::shared_ptr<VerticalTableModel> model)
    {
        _model = model;
        for (auto& r : _rows)
            r->model = model.get();

        this->addOnUpdate("attributes-changed", [this](const std::any& a){_onAttributesChanged();}, _model.get());
        this->addOnUpdate("attributes-added", [this](const std::any& a){_onAttributesAdded(std::any_cast<std::pair<std::string,Property::PropertyType>>(a));}, _model.get());
        this->addOnUpdate("attributes-removed", [this](const std::any& a){_onAttributesRemoved(std::any_cast<std::string>(a));}, _model.get());
        this->addOnUpdate("attributes-removed-idx", [this](const std::any& a){_onAttributesRemovedIdx(std::any_cast<unsigned int>(a));}, _model.get());
        this->addOnUpdate("data-changed", [this](const std::any& a){_onDataChanged();}, _model.get());
        this->addOnUpdate("data-added", [this](const std::any& a){_onDataAdded(std::any_cast<json>(a));}, _model.get());
        this->addOnUpdate("data-prepended", [this](const std::any& a){_onDataPrepended(std::any_cast<json>(a));}, _model.get());
        this->addOnUpdate("data-removed", [this](const std::any& a){_onDataRemoved(std::any_cast<unsigned int>(a));}, _model.get());

        auto f_data_modified = [this](const std::any& a)
        {
            std::pair<unsigned int, json> p = std::any_cast<std::pair<unsigned int, json>>(a);
            _onDataModified(p.first, p.second);
        };
        this->addOnUpdate("data-modified", f_data_modified, _model.get());

    }

    void VerticalTable::_setEvents()
    {
        _datascroll->addOnYScroll([this](double amount){
                _onScroll(amount);
        });
    }

    void VerticalTable::removeModel()
    {
        _model = nullptr;
        for (auto& r : _rows)
            r->model = nullptr;
    }


    Label* VerticalTable::_createHeaderLabel(const std::string& txt)
    {
        auto label = _headerRow->createLabel(txt);
        label->addCssClass("vtable-header-label");
        label->setEllipsizeMode(ml::ELLIPSIZE_END);

        label->setWidth(_rowWidth);
        label->setCursor("pointer");
        _headerLabels.push_back(label.get());
        _setHeaderLabelEvents(label.get());
        return label.get();
    }

    void VerticalTable::_setHeaderLabelEvents(Label* label)
    {
        label->addEventListener(LEFT_DOWN, [this, label](auto& e){
            _headerLabelDragged = label; 
        });

        label->addEventListener(LEFT_UP, [this, label](auto& e){
            _headerLabelDragged = nullptr; 
            if (!_headerRow->window()->state().ctrl)
                _events.emit("header-clicked", label);
        });

        label->addEventListener(RIGHT_UP, [this, label](auto& e){
            _events.emit("header-right-clicked", label);
        });

        label->addEventListener(MIDDLE_UP, [this, label](auto& e){
            _events.emit("header-middle-clicked", label);
        });

        auto mmove = [this](auto& e)
        {
            if(!_headerRow->window()->state().ctrl)
                return;
            if (!_headerLabelDragged)    
                return;
            _headerLabelDragged->setWidth(e.x);

            auto idx_ret = _headerLabelIndex(_headerLabelDragged);
            if (!idx_ret.success)
                return;

            size_t idx = idx_ret.value;
            for (auto& r : _rows)
            {
                if (!r->row)
                    continue;
                auto label = r->row->child<Label>(idx);
                if (label)
                    label->setWidth(e.x);
            }
        };

        label->addEventListener(MOUSE_MOVE, mmove);
    }

    Ret<size_t> VerticalTable::_headerLabelIndex(Label* label)
    {
        for (size_t i = 0; i < _headerLabels.size(); i++)
        {
            if (_headerLabels[i] == label)
                return ml::ret::success(i);
        }
        return ml::ret::fail<size_t>("Header label not found.");
    }

    void VerticalTable::_onAttributesChanged()
    {
        lg("VerticalTable::_onAttributesChanged");
        for (unsigned int i = 0; i < _model->attributes().size(); i++)
        {
            if (_headerLabels.size() <= i)
                _createHeaderLabel(_model->attributes()[i].first);
            else 
                _headerLabels[i]->setText(_model->attributes()[i].first);
        }
    }

    void VerticalTable::_onAttributesAdded(const std::pair<std::string,Property::PropertyType>& attribute)
    {
        lg("VerticalTable::_onAttributesAdded");
        _createHeaderLabel(attribute.first);
    }

    void VerticalTable::_onAttributesRemoved(const std::string& name)
    {
        lg("VerticalTable::_onAttributesRemoved");
        for (unsigned int i = 0; i < _headerLabels.size(); i++)
        {
            if (_headerLabels[i]->text() == name)
            {
                _headerLabels[i]->remove();
                _headerLabels.vec.erase(_headerLabels.begin() + i);
                return;
            }
        }
    }

    void VerticalTable::_onAttributesRemovedIdx(unsigned int index)
    {
        lg("VerticalTable::_onAttributesRemovedIdx");
        if (index >= _headerLabels.size())
            return;
        _headerLabels[index]->remove();
        _headerLabels.vec.erase(_headerLabels.begin() + index);
    }

    void VerticalTable::_onDataChanged()
    {
        _lastAddedIndex = -1;
        for (auto& r : _rows)
        {
            if (!r->row)
                continue;
            r->row->hide();
        }

        for (auto& json : _model->data())
            _onDataAdded(json);

        _headEmpty->setHeight(0);
        _footEmpty->setHeight(_model->size()*_rowHeight + _tablebox->height() - _databox->height());
    }

    void VerticalTable::_onDataAdded(const json& data)
    {
        lg("VerticalTable::_onDataAdded");
        if (_lastAddedIndex >= this->max_row_size() - 1)
        {
            lg("Doing nothing because " << _lastAddedIndex << " >= (max row size) " << this->max_row_size());
            return;
        }
        _lastAddedIndex++;
        _end = _lastAddedIndex;
        if (!_rows[_lastAddedIndex]->row)
        {
            _rows[_lastAddedIndex]->row = _databox->createBox().get();
            _rows[_lastAddedIndex]->row->setCursor("pointer");
            _rows[_lastAddedIndex]->row->setHeight(_rowHeight);

            auto vrow = _rows[_lastAddedIndex].get();
            _rows[_lastAddedIndex]->row->addEventListener(LEFT_UP, [this, vrow](auto& e){
                    _events.emit("row-clicked", vrow);
                    });

            _rows[_lastAddedIndex]->row->addEventListener(RIGHT_UP, [this, vrow](auto& e){
                    _events.emit("row-right-clicked", vrow);
                    });

            _rows[_lastAddedIndex]->row->addEventListener(MIDDLE_UP, [this, vrow](auto& e){
                    _events.emit("row-middle-clicked", vrow);
                });
        }

        _rows[_lastAddedIndex]->gui_index = _lastAddedIndex;
        _rows[_lastAddedIndex]->model_index = _lastAddedIndex;
        auto row = _rows[_lastAddedIndex]->row;
        row->setOrient(Orient::HORIZONTAL);
        row->addCssClass("vtable-row");

        for (unsigned int j = 0; j < _model->attributes().size(); j++)
        {
            auto k = _model->attributes()[j].first;
            auto t = _model->attributes()[j].second;
            if (!data.contains(k))
            {
                lg("need to create label for row " << j << " because " << k << " is not in the data properties");
                continue;
            }

            auto label = row->child<Label>(j);
            if (!label)
            {
                lg("need to create label for row " << j);
                std::shared_ptr<Label> label = row->createLabel();
                label->setEllipsizeMode(ml::ELLIPSIZE_END);
                auto w = _headerLabels[j]->width();
                lg("Attribute header label " << j << " w : " << w);
                if (w>15)
                    label->setWidth(_headerLabels[j]->width());
                else 
                    label->setWidth(_rowWidth);

                label->setHAlign(LEFT);
            }
        }

        this->setRowData(_lastAddedIndex, data);
        _rows[_lastAddedIndex]->row->show();
    }

    const json& VerticalRow::data() const
    {
        if (this->model)
            return this->model->data()[this->model_index];
        else
            throw std::runtime_error("VerticalRow::data() : model is nullptr");
    }

    void VerticalTable::setRowData(size_t index, const json& data)
    {
        if (index >= _rows.size())
        {
            lg("setRowData : index >= _rows.size() " << index << " >= " << _rows.size());
            return;
        }
        if (index > _lastAddedIndex)
        {
            lg("setRowData : index > _lastAddedIndex " << index << " > " << _lastAddedIndex);
            return;
        }

        auto& vrow = _rows[index];
        auto row = vrow->row;
        if (!row)
        {
            lg("setRowData : row " << index << " in nullptr");
            return;
        }

        for (unsigned int j = 0; j < _model->attributes().size(); j++)
        {
            auto k = _model->attributes()[j].first;
            auto t = _model->attributes()[j].second;
            if (!data.contains(k))
                continue;

            if (data[k].is_null())
                continue;

            auto label = row->child<Label>(j);
            if (!label)
            {
                lg("label " << j << " not found");
                continue;
            }

            if (t == Property::PropertyType::STRING)
            {
                label->setValue(data[k].get<std::string>());
            }
            else if (t == Property::PropertyType::INT)
            {
                label->setValue(std::to_string(data[k].get<int>()));
            }
            else if (t == Property::PropertyType::DOUBLE)
            {
                label->setValue(std::to_string(data[k].get<double>()));
            }
            else if (t == Property::PropertyType::BOOL)
            {
                label->setValue(std::to_string(data[k].get<bool>()));
            }
        }

        _events.emit("row-modified", vrow.get());
    }

    void VerticalTable::_onDataPrepended(const json& data)
    {
        lg("VerticalTable::_onDataPrepended");
        lg("data : " << data.dump(4));

        //TODO : test
        for (unsigned int i = 0; i < _rows.size(); i++)
            this->setRowData(i, _model->data()[i + _start]);

        //TODO create the last row if max_row_size() was not trigger in the model. (_lastAddedIndex)
    }

    int VerticalTable::_guiIdx(size_t dataIdx)
    {
        int gui_idx = dataIdx - _start;
        if (gui_idx < 0)
            return - 1;
        if (gui_idx >= _rows.size())
            return -1;
        return gui_idx;
    }

    ml::Ret<VerticalRow*> VerticalTable::_row(size_t dataIdx)
    {
        int gui = _guiIdx(dataIdx)        ;
        if (gui < 0)
            return ml::ret::fail<VerticalRow*>(std::to_string(dataIdx) + " is not drawn in the table.");

        if (gui >= _rows.size())
            return ml::ret::fail<VerticalRow*>("The gui_idx returned ie bigger than the number or rows, this should not happen : gui_idx : " + std::to_string(gui));

        return ml::ret::success(_rows[gui].get());
    }

    void VerticalTable::_onDataRemoved(unsigned int index)
    {
        lg("VerticalTable::_onDataRemoved(" << index << ")");
        auto size = _rows.size();
        auto msize = _model->data().size();
        if (msize < size)
        {
            auto diff = size - msize;
            for (unsigned int i = 0; i < diff; i++)
            {
                auto& r = _rows[size - i - 1];
                if (r->row)
                    r->row->hide();
            }

            size = _model->data().size();
        }

        if (index == size)
        {
            lg("_start : " << _start);
            for (unsigned int i = 0; i < _rows.size(); i++)
            {
                auto& r = _rows[i];
                lg("i : " << i);
                lg("r->model_index : " << r->model_index);
                lg("r->gui_index : " << r->gui_index);
            }
            if (_rows[index - _start]->row)
                _rows[index - _start]->row->hide();
        }
        else 
        {
            for (unsigned int i = index; i < size; i++)
                this->setRowData(i, _model->data()[i]);
        }
    }

    void VerticalTable::_onScroll(double amount)
    {
        lg("scroll : " << amount);
        lg("one row height : " << this->oneRowHeight());
        lg("all rows height : " << this->allRowsHeight());

        auto headheight = amount;
        auto footheight = _model->size()*_rowHeight - amount + _tablebox->height() - _databox->height();
        if (footheight<=0)
            return;
        _headEmpty->setHeight(amount);
        _footEmpty->setHeight(footheight);

        auto first = amount/this->oneRowHeight();
        _setFirst(first);
    }

    double VerticalTable::oneRowHeight() const
    {
        if (_lastAddedIndex == -1)
            return 0;
        return _rowHeight;
    }

    double VerticalTable::allRowsHeight() const
    {
        return _databox->height();
    }

    double VerticalTable::rowTop(size_t index) const
    {
        if (index > _lastAddedIndex)
            return -1;
        return index * this->oneRowHeight();
    }

    double VerticalTable::rowTop(Box* row) const
    {
        for (unsigned int i = 0; i < _rows.size(); i++)
        {
            if (_rows[i]->row == row)
                return this->rowTop(i);
        }
        return -1;
    }

    void VerticalTable::_shift(int offset) 
    {
        _start += offset;
        _end += offset;
        if (_end >= _model->size() -1)
            _end = _model->size() -1;

        for (unsigned int i = 0; i < _rows.size(); i++)
        {
            if (i + _start >= _model->size())
                return;

            _rows[i]->model_index = i + _start;
            this->setRowData(i, _model->data()[i + _start]);
        }
    }

    void VerticalTable::_setFirst(int dataIndex)
    {
        _start = dataIndex;
        _end = _start + _databox->height()/this->oneRowHeight();
        if (_end >= _model->size())
            _end = _model->size() - 1;

        for (unsigned int i = 0; i < _rows.size(); i++)
        {
            if (i + _start >= _model->size())
                return;

            _rows[i]->model_index = i + _start;
            this->setRowData(i, _model->data()[i + _start]);
        }
    }

    void VerticalTable::_onDataModified(unsigned int index, const json& data)
    {
        lg("_onDataModified : " << index << " : " << data.dump(4));
        this->setRowData(index, data);
    }

    int VerticalTable::max_row_size() const
    {
        return 50;
    }
}
