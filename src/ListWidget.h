#pragma once
#include "./ComposedWidget.h"

//List.h is certainly better for what you want to do.

namespace ml
{
    class Box;
    class Scrollable;
    class ListWidget : public ComposedWidget
    {
        public:
            ListWidget(Box* parent);
            ListWidget(Scrollable* parent);
            virtual ~ListWidget(){}

            void add(std::shared_ptr<ml::Widget> widget);
            void remove(Widget* widget);

            void hideElement(Widget* widget);
            void showElement(Widget* widget);

            void clear();
            int elementIndex(Widget* widget);
            void swap(size_t i, size_t j);

            void moveTop(Widget* widget);
            void moveBottom(Widget* widget);

            Scrollable* body(){return _body;}

        protected : 
            Scrollable* _body = nullptr;

        private : 
            void _construct(Box* parent);
    };
}
