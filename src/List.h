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
//Your element T needs to have the methods searchStr() and gui() representing its main gui component (should descent of ml::Widget*).
//The searchStr() don't need to be cleaned up, it's done directly here.
//
//TODO : certainly a way to add/remove elements dynamicly
//TODO : certainly a way to add/remove elements directly in the GUI (or at least removing one)

namespace ml
{
    template<typename T, bool Dynamic=false>
    class List: public ComposedWidget
    {
        public : 
        List(Box* parent, bool search = true) : ComposedWidget(), _search(_S"Search", "")
        {
            _parent = parent->window();
            __draw(parent);
        }

        List(Scrollable* parent, bool search = true): ComposedWidget(), _search(_S"Search", "")
        {
            _parent = parent->window();
            __draw(&parent->content());
        }

        List(std::shared_ptr<Box> parent, bool search = true) : ComposedWidget(), _search(_S"Search", "")
        {
            _parent = parent->window();
            __draw(parent.get());
        }

        List(std::shared_ptr<Scrollable> parent, bool search = true): ComposedWidget(), _search(_S"Search", "")
        {
            _parent = parent->window();
            __draw(&parent->content());
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

        void clear()
        {
            _list->clear();
            _elmts.clear();
            _search.set(_S"");
        }

        template<typename... Args>
        T* createElmt(Args&&... args)
        {
            _elmts.push_back(std::make_shared<T>(std::forward<Args>(args)...));
            auto _r = _elmts.back().get();
            _r->gui()->addCssClass("list-item");
            _r->gui()->setHAlign(HAlignment::FILL);
            _r->gui()->setHExpand(true);
            if constexpr(Dynamic)
                _r->gui()->addEventListener(ml::MOUSE_ENTER, [this, _r](auto&e){_activeElmt = _r;});

            return _elmts.back().get();
        }

        void removeElmt(T* elmt)
        {
            for (int i = 0; i < _elmts.size(); i++) 
            {
                if (_elmts[i].get() == elmt)
                {
                    _elmts[i]->gui()->addCssClass("list-item");
                    _list->remove(_elmts[i]->gui());
                    _elmts.removeByIndex(i);
                    break;
                }
            }
        }

        void setOnAddElmt(const std::function<void()>& f) {_onAddElmt = f;}

        protected: 
            ml::Box* _body;
            std::shared_ptr<ListWidget> _list;
            ml::Vec<std::shared_ptr<T>> _elmts;
            StringProperty _search;

            void __setEvents()
            {
                auto searchf = [this]
                {
                    std::string searched = _search.value();
                    searched = str::clean(searched, true);
                    if (searched.empty())
                    {
                        for (auto& elmt : _elmts)
                            elmt->gui()->show();
                        return;
                    }

                    for (auto& elmt : _elmts)
                        elmt->gui()->hide();
                    for (auto& elmt : _elmts)
                    {
                        auto elmt_searchstr = elmt->searchStr();
                        elmt_searchstr = str::clean(elmt_searchstr, true);
                        if(str::contains(elmt_searchstr, searched))
                            elmt->gui()->show();
                    }
                };
                _search.addOnUpdate(searchf);
                _search.addOnValid(searchf);
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
                if (_onAddElmt)
                    _onAddElmt();
                else 
                    ml::app()->error("No List::onAddElmt function setted.");
            }

            void _removeActiveElmt()
            {
                if (_activeElmt)
                    this->removeElmt(_activeElmt);
            }

            void __createCommands()
            {
                if constexpr(!Dynamic)
                    return;
                auto c = _parent->cmds().createCommand<ml::GuiCommand>("Add", "add-elmt", [this](auto&e){_addElmt();});	
                c = _parent->cmds().createCommand<ml::GuiCommand>("Remove", "remove-active-elmt", [this](auto&e){_removeActiveElmt();});	
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

            ml::Window* _parent = nullptr;
            T* _activeElmt = nullptr;
            std::function<void()> _onAddElmt = nullptr;

        public : 
            ml::Vec<std::shared_ptr<T>>& elmts() {return _elmts;}
            const ml::Vec<std::shared_ptr<T>>& elmts()const {return _elmts;}

            ml::Box* listbox()
            {
                return &_list->body()->content();
            }

            std::shared_ptr<ListWidget> list() {return _list;}
            const std::shared_ptr<ListWidget> list()const {return _list;}
    };
}
