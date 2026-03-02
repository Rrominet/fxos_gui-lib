#include "./ListWidget.h"
#include "./Box.h"
#include "./Scrollable.h"

#include "./Box.hpp"
#include "./Scrollable.hpp"

namespace ml
{
    ListWidget::ListWidget(Box* parent) : ComposedWidget()
    {
        _construct(parent);
    }

    ListWidget::ListWidget(Scrollable* parent) : ComposedWidget()
    {
        _construct(&parent->content());
    }

    void ListWidget::_construct(Box* parent)
    {
        _body = parent->createScrollable().get();
        _body->setOrient(Orient::VERTICAL);
        _body->addCssClass("list");
        _body->setVExpand();
        _body->setVExpandSet();

        _composed.push(_body);
    }

    void ListWidget::add(std::shared_ptr<ml::Widget> widget)
    {
        widget->addCssClass("list-item");
        _body->append(widget);
    }

    void ListWidget::remove(Widget* widget)
    {
        widget->removeCssClass("list-item");
        _body->removeChild(widget);
    }

    void ListWidget::hideElement(Widget* widget)
    {
        if (!_body->content().containsChild(widget)) 
        {
            lg("This list Widget does not contains the widget : " << widget);
            return;
        }
        widget->hide();
    }

    void ListWidget::showElement(Widget* widget)
    {
        if (!_body->content().containsChild(widget)) 
        {
            lg("This list Widget does not contains the widget : " << widget);
            return;
        }
        widget->show();
    }

    void ListWidget::clear()
    {
        _body->content().clear();
    }

    int ListWidget::elementIndex(Widget* widget)
    {
        return _body->content().childIndex(widget);
    }

    void ListWidget::swap(size_t i,size_t j)
    {
        _body->content().swap(i,j);
    }

    void ListWidget::moveTop(Widget* widget)
    {
        _body->content().moveChildTop(widget);
    }

    void ListWidget::moveBottom(Widget* widget)
    {
        _body->content().moveChildBottom(widget);
    }
}
