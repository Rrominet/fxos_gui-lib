#pragma once
#include "./PropertyWidget.h"
#include "./ListWidget.h"

#include "./Box.h"
#include "./Scrollable.h"
#include "./Property.h"

#include "./str.h"


//The elements needs to be drawn in their constructor.
//You pass the List as argument (as a pointer or ref) and use list->listbox()->create... to draw your interface in your element directly
//
//Your element T needs to have the methods searchStr() (returning a string that would be used for the search feature) and gui() representing its main gui component (should descent of ml::Widget*) and return a ptr.
//The searchStr() don't need to be cleaned up, it's done directly here.
//
//if MaxDrawn == true, you need the function draw() in the element to draw the element. (and draw shouldn't be executed in the constructor)
//else, the element should be drawn in its constructor

namespace ml
{
    template<typename T, bool Dynamic=false, bool MaxDrawn=false>
    class List: public ComposedWidget
    {
        public : 
            enum SelectionType
            {
                NONE = 0,
                SINGLE,
                MULTIPLE
            };

#define __CONSTRUCT \
            _maxDrawn = maxDrawn; \
            _parent = parent->window(); \
            __draw(parent, search);

        List(Box* parent, bool search = true, SelectionType selectionType = SelectionType::NONE, int maxDrawn = 50) : ComposedWidget(), _search(_S"Search", ""), _selectionType(selectionType)
        {
            __CONSTRUCT;
        }

        List(Scrollable* parent, bool search = true, SelectionType selectionType = SelectionType::NONE, int maxDrawn = 50): ComposedWidget(), _search(_S"Search", ""), _selectionType(selectionType)
        {
            __CONSTRUCT;
        }

        List(std::shared_ptr<Box> parent, bool search = true, SelectionType selectionType = SelectionType::NONE, int maxDrawn = 50) : ComposedWidget(), _search(_S"Search", ""), _selectionType(selectionType)
        {
            __CONSTRUCT;
        }

        List(std::shared_ptr<Scrollable> parent, bool search = true, SelectionType selectionType = SelectionType::NONE, int maxDrawn = 50): ComposedWidget(), _search(_S"Search", ""), _selectionType(selectionType)
        {
            __CONSTRUCT;
        }

        virtual ~List() = default;

        void hideSearch()
        {
            _search.hide();
        }

        void showSearch()
        {
            _search.show();
        }

        void toggleSearch()
        {
            if(_search.visible())
                _search.hide();
            else 
                _search.show();
        }

        ml::StringProperty& search() {return _search;}

        void clear()
        {
            _selected.clear();
            _drawn = 0;
            _guiCreated.clear();
            _list->clear();
            _elmts.clear();
            _search.set(_S"");
        }

        template<typename... Args>
        T* createElmt(Args&&... args)
        {
            _elmts.push_back(std::make_shared<T>(std::forward<Args>(args)...));
            auto _r = _elmts.back().get();

            if constexpr(MaxDrawn)
            {
                if (_drawn < _maxDrawn)
                {
                    __drawElmt(_r);
                    _drawn ++;
                }
            }
            else 
                __drawElmt(_r);
            return _elmts.back().get();
        }

        void removeElmt(unsigned int idx)
        {
            if (idx >= _elmts.size())
                return;
            this->unselect(idx);
            if constexpr(!MaxDrawn)
                _list->remove(_elmts[idx]->gui());
            else 
            {
                if (_guiCreated.contains(idx))
                {
                    _list->remove(_elmts[idx]->gui());
                    _guiCreated.remove(idx);
                }
            }
            _elmts.removeByIndex(idx);
            for (auto& sidx : _selected)
            {
                if (sidx > idx)
                    sidx --;
            }
            if constexpr(MaxDrawn)
            {
                for (auto& idx_c : _guiCreated)
                {
                    if (idx_c > idx)
                        idx --;
                }
            }
        }
        void removeElmt(T* elmt)
        {
            this->removeElmt(this->index(elmt));
        }

        void setOnAddElmt(const std::function<void()>& f) {_onAddElmt.push_back(f);}
        void setBeforeRemoveElmt(const std::function<void(T*)>& f) {_beforeRemoveElmt.push_back(f);}
        void addOnAddElmt(const std::function<void()>& f) {_onAddElmt.push_back(f);}
        void addBeforeRemoveElmt(const std::function<void(T*)>& f) {_beforeRemoveElmt.push_back(f);}
        void addOnSelected(const std::function<void(const ml::Vec<T>&)>& f) {_onSelected.push_back(f);}
        void addOnUnselected(const std::function<void(const ml::Vec<T>&)>& f) {_onUnselected.push_back(f);}

        void clearOnSelected() {_onSelected.clear();}
        void clearOnUnselected() {_onUnselected.clear();}
        void clearOnAddElmt() {_onAddElmt.clear();}
        void clearBeforeRemoveElmt() {_beforeRemoveElmt.clear();}

        int index(T* elmt)
        {
            for (int i = 0; i < _elmts.size(); i++) 
            {
                if (_elmts[i].get() == elmt)
                    return i;
            }
            return -1;
        }

        protected: 
            ml::Box* _body;
            std::shared_ptr<ListWidget> _list;
            ml::Vec<std::shared_ptr<T>> _elmts;
            StringProperty _search;

            void __setEvents()
            {
                auto searchf = [this]
                {
                    _searchedMatched.clear();
                    std::string searched = _search.value();
                    searched = str::clean(searched, true);
                    if (searched.empty())
                    {
                        for (unsigned i=0; i<_elmts.size(); i++)
                            __hide(i);
                        for (unsigned i=0; i<_elmts.size(); i++)
                            __show(i);
                        return;
                    }

                    for (unsigned i=0; i<_elmts.size(); i++)
                        __hide(i);
                    for (unsigned i=0; i<_elmts.size(); i++)
                    {
                        auto elmt_searchstr = _elmts[i]->searchStr();
                        elmt_searchstr = str::clean(elmt_searchstr, true);
                        if(str::contains(elmt_searchstr, searched))
                        {
                            __show(i);
                            _searchedMatched.push_back(i);
                        }
                    }
                };
                _search.addOnUpdate(searchf);
                _search.addOnValid(searchf);
            }

            void __drawElmt(T* elmt)
            {
                if constexpr(MaxDrawn)
                {
                    elmt->draw();
                    _guiCreated.push_back(this->index(elmt));
                    lg("elmt " << this->index(elmt)<< " drawn");
                }
                elmt->gui()->addCssClass("list-item");
                elmt->gui()->setHAlign(HAlignment::FILL);
                elmt->gui()->setHExpand(true);
                if constexpr(Dynamic)
                    elmt->gui()->addEventListener(ml::MOUSE_ENTER, [this, elmt](auto&e){_activeElmt = elmt;});

                elmt->gui()->addEventListener(ml::LEFT_DOWN, [this, elmt](auto&e){__onLeftDown(e, elmt);});
                elmt->gui()->addEventListener(ml::RIGHT_DOWN, [this, elmt](auto&e){__onRightDown(e, elmt);});
                if (_selectionType != NONE)
                    elmt->gui()->setCursor("pointer");
            }

            void __hide(unsigned int idx)
            {
                if constexpr(MaxDrawn)
                {
                    if (!_guiCreated.contains(idx))
                    {
                        lg("elmt " << idx << " not drawn yet, nothing to hide");
                        return;
                    }
                }
                if (idx < _elmts.size())
                {
                    lg("elmt " << idx << " drawn, hidding it");
                    if (_elmts[idx]->gui()->visible())
                    {
                        _elmts[idx]->gui()->hide();
                        lg("elmt " << idx << " hidden");
                        if constexpr(MaxDrawn)
                        {
                            _drawn --;
                            lg("drawn " << _drawn);
                        }
                    }
                }

                this->unselect(idx);
            }

            void __hide(T* elmt)
            {
                __hide(this->index(elmt));
            }

            void __show(unsigned int idx)
            {
                if (idx >= _elmts.size())
                    return;
                if constexpr(MaxDrawn)
                {
                    if (_drawn >= _maxDrawn)
                        return;
                    if (!_guiCreated.contains(idx))
                        __drawElmt(_elmts[idx].get());
                    else 
                        _elmts[idx]->gui()->show();
                    _drawn ++;
                }
                else 
                    _elmts[idx]->gui()->show();
            }

            void __show(T* elmt)
            {
                __show(this->index(elmt));
            }

            void __draw(ml::Box* parent, bool search = true)
            {
                _body = parent->createBox().get();
                auto w = _body->appendProp(&_search);
                w->box()->addCssClass("list-search");
                _body->addCssClass("list-container");
                _list = _body->createComposedWidget<ListWidget>(_body);

                if (!search)
                    this->hideSearch();

                _composed.push_back(_body);

                __createCommands();
                __setEvents();
                __createMenus();
            }

            void _addElmt()
            {
                if (_onAddElmt.empty())
                {
                    ml::app()->error("Error in the list : no onAddElmt function defined.\nYou need to create one that create the element.");
                    return;
                }
                for (auto& f : _onAddElmt)
                    f();
            }

            void _removeActiveElmt()
            {
                if (_activeElmt)
                {
                    for (auto& f : _beforeRemoveElmt)
                        f(_activeElmt);
                    this->removeElmt(_activeElmt);
                    _activeElmt = nullptr;
                }
            }

            void _removeSelection()
            {
                for (auto& idx : _selected)
                {
                    for (auto& f : _beforeRemoveElmt)
                        f(_elmts[idx].get());
                    this->removeElmt(idx);
                }

                _selected.clear();
            }

            void __createCommands()
            {
                if constexpr(!Dynamic)
                    return;
                auto c = _parent->cmds().createCommand<ml::GuiCommand>("Add", "add-elmt", [this](auto&e){_addElmt();});	
                c = _parent->cmds().createCommand<ml::GuiCommand>("Remove", "remove-active-elmt", [this](auto&e){
                        if (_selectionType == NONE)
                            _removeActiveElmt();
                        else 
                            _removeSelection();
                        });	
            }

            void __createMenus()
            {
                if constexpr(!Dynamic)
                    return;
                auto id = "list-context-menu__" + str::random(10);
                auto ctx = ml::app()->menus().create(id);
                ctx->addCommand(_parent->cmds().command("add-elmt").get());
                ctx->addCommand(_parent->cmds().command("remove-active-elmt").get());
                this->listbox()->setContextMenu(id);
            }

            void __selectOnMouseDown(ml::EventInfos& e, T* elmt)
            {
                if (_selectionType == NONE)
                    return;
                else if (_selectionType == SINGLE)
                    this->replaceSelection(elmt);
                else if (_selectionType == MULTIPLE)
                {
                    if (!e.ctrl && !e.shift && !e.alt)
                    {
                        if (!this->selected(elmt))
                            this->replaceSelection(elmt);
                        else 
                        {
                            if (_selected.size() == 1)
                                this->unselect(elmt);
                            else 
                                this->replaceSelection(elmt);
                        }
                    }

                    else if (e.ctrl && !e.shift && !e.alt)
                    {
                        if (!this->selected(elmt))
                            this->select(elmt);
                        else 
                            this->unselect(elmt);
                    }

                    else if (!e.ctrl && e.shift && !e.alt)
                    {
                        if (_selected.empty())
                        {
                            this->select(elmt);
                            return;
                        }

                        if (this->selected(elmt))
                        {
                            this->unselect(elmt);
                            return;
                        }

                        auto firstselected = _selected.first();
                        auto lastselected = _selected.last();
                        auto curr = this->index(elmt);

                        if (curr < firstselected)
                        {
                            for (auto i = curr; i <= lastselected; i++)
                                this->select(i);
                        }
                        else if (curr > lastselected)
                        {
                            for (auto i = lastselected; i <= curr; i++)
                                this->select(i);
                        }
                    }
                }
            }

            void __onLeftDown(ml::EventInfos& e, T* elmt)
            {
                __selectOnMouseDown(e, elmt);
                if (_selectionType != NONE)
                    e.stopPropagation();
            }

            void __onRightDown(ml::EventInfos& e, T* elmt)
            {
                if (_selectionType == NONE)
                    return;
                else if (_selectionType == SINGLE)
                    this->replaceSelection(elmt);
                else if (_selectionType == MULTIPLE)
                {
                    if (!e.ctrl && !e.shift && !e.alt)
                    {
                        if (!this->selected(elmt))
                            this->replaceSelection(elmt);
                    }

                    else if (e.ctrl && !e.shift && !e.alt)
                    {
                        if (!this->selected(elmt))
                            this->select(elmt);
                    }

                    else if (!e.ctrl && e.shift && !e.alt)
                    {
                        if (_selected.empty())
                        {
                            this->select(elmt);
                            return;
                        }

                        auto firstselected = _selected.first();
                        auto lastselected = _selected.last();
                        auto curr = this->index(elmt);

                        if (curr < firstselected)
                        {
                            for (auto i = curr; i <= lastselected; i++)
                                this->select(i);
                        }
                        else if (curr > lastselected)
                        {
                            for (auto i = lastselected; i <= curr; i++)
                                this->select(i);
                        }
                    }
                }
            }

            void _cleanUpSelectedList()
            {
                auto good_selected = ml::Vec<unsigned int>();
                for (const auto& i : _selected)
                {
                    if (i >= _elmts.size())
                        continue;
                    good_selected.push_back(i);
                }
                _selected = good_selected;
            }

            void _updateDrawFromSelected()
            {
                for (unsigned int i = 0; i < _elmts.size(); i++)
                {
                    if (_selected.contains(i))
                        this->select(i);
                    else 
                        this->unselect(i);
                }
            }

            ml::Window* _parent = nullptr;
            T* _activeElmt = nullptr;

            ml::Vec<std::function<void()>> _onAddElmt;
            ml::Vec<std::function<void(T*elmt)>> _beforeRemoveElmt;
            ml::Vec<std::function<void(T*elmt)>> _onSelected;
            ml::Vec<std::function<void(T*elmt)>> _onUnselected;

            //TODO if necessary : 
//             ml::Vec<std::function<void(T*elmt)>> _onShown;
//             ml::Vec<std::function<void(T*elmt)>> _onHidden;
//             ml::Vec<std::function<void(T*elmt)>> _onDrawn;

            SelectionType _selectionType = SelectionType::NONE;
            ml::Vec<unsigned int> _selected;

            int _maxDrawn;
            int _drawn = 0;
            ml::Vec<unsigned int> _guiCreated;
            ml::Vec<unsigned int> _searchedMatched;

        public : 
            ml::Vec<std::shared_ptr<T>>& elmts() {return _elmts;}
            const ml::Vec<std::shared_ptr<T>>& elmts()const {return _elmts;}

            ml::Box* listbox()
            {
                return &_list->body()->content();
            }

            ml::Vec<unsigned int> lastSearchedMatched() {return _searchedMatched;}

            void setSelectionType(SelectionType type) {_selectionType = type;}

            void select(unsigned int idx)
            {
                auto elmt = _elmts[idx];
                if constexpr(!MaxDrawn)
                    elmt->gui()->addCssClass("selected");
                else 
                {
                    if (_guiCreated.contains(idx))
                        elmt->gui()->addCssClass("selected");
                }
                if (idx != -1 && !_selected.contains(idx))
                    _selected.push_back(idx);

                for (auto& f : _onSelected)
                    f(elmt.get());
            }
            void select(T* elmt)
            {
                this->select(this->index(elmt));
            }
            
            void unselect(unsigned int idx)
            {
                auto elmt = _elmts[idx];
                if constexpr(!MaxDrawn)
                    elmt->gui()->removeCssClass("selected");
                else 
                {
                    if (_guiCreated.contains(idx))
                        elmt->gui()->removeCssClass("selected");
                }
                if (_selected.contains(idx))
                    _selected.remove(idx);

                for (auto& f : _onUnselected)
                    f(elmt.get());
            }

            void unselect(T* elmt)
            {
                this->unselect(this->index(elmt));
            }

            void selectAll()
            {
                this->selectRange(0, _elmts.size() - 1);
            }

            void unselectAll()
            {
                _selected.clear();
                for (auto& elmt : _elmts)
                    this->unselect(elmt.get());
            }

            void selectRange(unsigned int start, unsigned int end)
            {
                if (start > end)
                    std::swap(start, end);
                if (start > _elmts.size() || end > _elmts.size())
                    return;
                for (unsigned int i = start; i <= end; i++)
                    this->select(i);
            }

            void selectIndexes(const ml::Vec<unsigned int>& idxs)
            {
                for (auto& idx : idxs)
                    this->select(idx);
            }

            void replaceSelection(T* elmt)
            {
                this->unselectAll();
                this->select(elmt);
            }

            bool selected(T* elmt) {return _selected.contains(this->index(elmt));}

            std::shared_ptr<ListWidget> list() {return _list;}
            const std::shared_ptr<ListWidget> list()const {return _list;}

            void runOnSelected(const std::function<void(T*)>& f)
            {
                for (auto& elmt : _elmts)
                {
                    if (this->selected(elmt.get()))
                        f(elmt.get());
                }
            }

            void runOnDrawn(const std::function<void(T*)>& f)
            {
                for (auto idx : _guiCreated)
                    f(_elmts[idx].get());
            }

            void runOnVisble(const std::function<void(T*)>& f)
            {
                for (auto idx : _guiCreated)
                {
                    if (_elmts[idx]->gui()->visible())
                        f(_elmts[idx].get());
                }
            }

            void runOnSelected(const std::function<void(const ml::Vec<std::shared_ptr<T>>&)>& f)
            {
                f(_elmts);
            }

            void runOnUnselected(const std::function<void(T*)>& f)
            {
                for (auto& elmt : _elmts)
                {
                    if (!this->selected(elmt.get()))
                        f(elmt.get());
                }
            }

            void runOnUnselected(const std::function<void(const ml::Vec<T>&)>& f)
            {
                auto unselected = ml::Vec<T>();
                for (auto& elmt : _elmts)
                {
                    if (!this->selected(elmt.get()))
                        unselected.push_back(elmt.get());
                }
                f(unselected);
            }

            int maxDrawn() const
            {
                if constexpr(MaxDrawn)
                    return _maxDrawn;
                else 
                    return -1;
            }

            void moveSelection(int offset)
            {
                if (_selected.size() == 0)
                    return;
                for (auto& idx : _selected)
                    idx += offset;

                _cleanUpSelectedList();
                _updateDrawFromSelected();
            }

            void extendSelection(int offset)
            {
                if (offset == 0)
                    return;
                if (_selected.size() == 0)
                    return;
                if (offset > 0)
                {
                    int last = -1;
                    for (auto idx : _selected)
                    {
                        if ((int)idx > last)
                        {
                            last = idx; 
                            lg(last);
                        }
                    }
                    lg(last);

                    for (int i = last + 1; i < last + offset + 1; i++)
                    {
                        lg("Pushing into selection : " << i);
                        _selected.push_back(i);
                    }
                }
                else 
                {
                    int first = INT_MAX;
                    for (auto idx : _selected)
                    {
                        if ((int)idx < first)
                        {
                            first = idx; 
                            lg(first);
                        }
                    }
                    int i = first - offset;
                    lg("first selected : " << first);
                    lg("first - offset : " << (first - offset));
                    lg("i < first: " << (i < first));
                    for (int i = first + offset; i < first; i++)
                    {
                        if (i < 0)
                            continue;
                        lg("Pushing into selection : " << i);
                        _selected.push_back(i);
                    }
                }

                _cleanUpSelectedList();
                _updateDrawFromSelected();
            }

            void invertSelection()
            {
                auto goodselect = ml::Vec<unsigned int>();
                for (unsigned int i = 0; i < _elmts.size(); i++)
                {
                    if (!_selected.contains(i))
                        goodselect.push_back(i);
                }
                _selected = goodselect;
                _updateDrawFromSelected();
            }

            ml::Vec<unsigned int> selected() const {return _selected;}
    };
}
