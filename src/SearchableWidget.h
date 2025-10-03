#pragma once
#include <string>

namespace ml
{
    class SearchableWidget
    {
        public : 
            virtual ~SearchableWidget(){}

            //What is the text that is returned by this widget to be searched
            virtual std::string asText() const = 0;

            //What should we do If the search match (show it ?)
            virtual void searchMatch() = 0;

            //What should we do If the search don't match (hide it ?)
            virtual void searchDontMatch() = 0;
    };
}
