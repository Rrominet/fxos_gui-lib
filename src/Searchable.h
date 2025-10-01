#pragma once
//This class should be used as a second inheritance an an already existing GUI class that contains stuffs like widgets.
//The Child class Should call this->createSearchInput(parent) to create the search input

#include <memory>
#include <string>
#include "vec.h"

namespace ml
{
    class Widget;
    class Box;
    class Entry;
    class SearchableWidget;
    class Searchable
    {
        public:
            Searchable(){}
            virtual ~Searchable(){}

            void createSearchInput(ml::Box* parent);

            //will be reimplement in child class
            //will be called when the input is changed
            //the searched string is cleaned with no spaces and no majs
            virtual void search(const std::string& searched);

            //When the user press enter when the search entry is focused.
            //by default, does nothing.
            virtual void valid(const std::string& searched){};

            // need to be implemented in child class
            // for the default search() implementation to work.
            virtual ml::Vec<std::shared_ptr<SearchableWidget>> searchableWidgets(){return {};}

        protected : 
            std::shared_ptr<Entry> _searchInput = nullptr;

            // you can use this to get the matches when implementing the valid override.
            // do not it in searchMatch or serachDontMatch override from your SearchableWidget, the return value will be wrong.
            ml::Vec<std::shared_ptr<SearchableWidget>> _matches; //bp cg

            // called in createSearchInput
            void _setEvents();

        public : 
#include "./Searchable_gen.h"
    };
}
