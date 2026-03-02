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
//Your element T needs to have the methods show() and hide() and searchStr().
//The searchStr() don't need to be cleaned up, it's done directly here.
//
//TODO : certainly a way to add/remove elements dynamicly
//TODO : certainly a way to add/remove elements directly in the GUI (or at least removing one)

namespace ml
{
    template<typename T>
    class List: public ComposedWidget
    {
        public : 
        List(Box* parent, bool search = true) : ComposedWidget(), _search(_S"Search", "")
        {
            __draw(parent);
        }

        List(Scrollable* parent, bool search = true): ComposedWidget(), _search(_S"Search", "")
        {
            __draw(&parent->content());
        }

        List(std::shared_ptr<Box> parent, bool search = true) : ComposedWidget(), _search(_S"Search", "")
        {
            __draw(parent.get());
        }

        List(std::shared_ptr<Scrollable> parent, bool search = true): ComposedWidget(), _search(_S"Search", "")
        {
            __draw(&parent->content());
        }

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
            return _elmts.back().get();
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
                    std::string searched = _search.value();
                    searched = str::clean(searched, true);
                    if (searched.empty())
                    {
                        for (auto& elmt : _elmts)
                            elmt->show();
                        return;
                    }

                    for (auto& elmt : _elmts)
                        elmt->hide();
                    for (auto& elmt : _elmts)
                    {
                        auto elmt_searchstr = elmt->searchStr();
                        elmt_searchstr = str::clean(elmt_searchstr, true);
                        if(str::contains(elmt_searchstr, searched))
                            elmt->show();
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

                __setEvents();

                _composed.push_back(_body);
            }

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
