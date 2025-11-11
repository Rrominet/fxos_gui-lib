#pragma once
#include "./ComposedWidget.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "./Property.h"
#include "./Events.h"
#include "./Ret.h"


// Events you can subscribe to : 
//  - row-clicked exec when the user click on a row with the arg as a pair{idx, row}, idx is the index of the row and the row is the pointer itself.
//  - header-clicked exec when the user click on a header with the arg as the Label* itself

namespace ml
{
    class Box;
    class Scrollable;
    class Label;
    class VerticalTableModel;

    struct VerticalRow
    {
        VerticalTableModel* model = nullptr;
        Box* row = nullptr;
        const json& data() const;

        // index of the data in the model
        int model_index = -1;

        // index of the actual row drawn in the GUI
        int gui_index = -1;
    };

    class VerticalTable : public ComposedWidget 
    {
        public : 
            VerticalTable(Box* parent);
            virtual ~VerticalTable();

            virtual void addEventListener(Event event, const std::function<void(EventInfos&)>& callback) override;
            virtual void linkToModel(std::shared_ptr<VerticalTableModel> model);
            void removeModel();

            std::shared_ptr<VerticalTableModel> model() const { return _model; }
            double oneRowHeight() const;
            double allRowsHeight() const;
            double rowTop(size_t index) const;
            double rowTop(Box* row) const;

            void setRowData(size_t index, const json& data);

        protected :
            float _rowWidth = 150; // default
            float _rowHeight = 20; //default TODO : should be set from settings

            std::shared_ptr<VerticalTableModel> _model = nullptr;
            std::shared_ptr<Box> _tablebox;
            std::shared_ptr<Box> _headerRow;
            std::shared_ptr<Scrollable> _datascroll;
            std::shared_ptr<Box> _headEmpty;
            std::shared_ptr<Box> _databox;
            std::shared_ptr<Box> _footEmpty;

            ml::Vec<Label*> _headerLabels;
            ml::Vec<std::unique_ptr<VerticalRow>> _rows;

            int _lastAddedIndex = -1;

            // these are the reference for knowing at wich index in the data correspond the first and last row.
            int _start = 0;
            int _end = 0;

            Label* _headerLabelDragged = nullptr;

            void _onAttributesChanged();
            void _onAttributesAdded(const std::pair<std::string, Property::PropertyType>& attribute);
            void _onAttributesRemoved(const std::string& name);
            void _onAttributesRemovedIdx(unsigned int index);
            void _onDataChanged();
            void _onDataAdded(const json& data);
            void _onDataPrepended(const json& data);
            void _onDataRemoved(unsigned int index);
            void _onDataModified(unsigned int index, const json& data);

            void _setEvents();
            void _onScroll(double amount);

            //shift the the data represented from the model
            //if the offset is 5, the first row will be the 6th in the model
            //the offset is additional. (that mean if you call _shift multiple time with the same value, you will repeat the action (3x5, will give the first element to be the 16th not the 6th))
            void _shift(int offset);

            //set the data index data to the top row
            void _setFirst(int dataIndex);

            Label* _createHeaderLabel(const std::string& txt);
            void _setHeaderLabelEvents(Label* label);
            Ret<size_t> _headerLabelIndex(Label* label);

            Events _events; //bp cg
            int max_row_size() const;

            // returnr -1 if not in the gui (before or after the scroll)
            int _guiIdx(size_t dataIdx);
            ml::Ret<VerticalRow*> _row(size_t dataIdx);

        public : 
#include "./VerticalTable_gen.h"
    };
}
