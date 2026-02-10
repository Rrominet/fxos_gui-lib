#include "./Box.h"
#include "./App.h"
#include "enums.h"

namespace ml
{
    Widget::Widget() : Observer()
    {
        ml::app()->checker().check("can-construct-widget");
    }

    Widget::~Widget()
    {
        lg("Widget::~Widget");
        this->remove();
    }

    void Widget::toggle()
    {
        if (this->isVisible())
            this->hide();
        else
            this->show();
    }

    void Widget::_createBasicEvents()
    {
        this->addEventListener(FOCUS, [this](EventInfos&){
                lg(this << " focused.");
                    ml::app()->setFocusedWidget(this);
                }); 

        this->addEventListener(UNFOCUS, [this](EventInfos&){
                    if (ml::app()->focusedWidget() == this)
                        ml::app()->setFocusedWidget(nullptr);
                }); 
    }

    void Widget::remove()
    {
        if (!this->hasParent())
            lg("no parents founded... in Widget::remove");

        this->removeWindow();
        _impl->remove();
    }

    void Widget::setWindow(ml::Window* w)
    {
        ml::app()->checker().check("can-set-window");
        assert(w && "setWindow, w can't be nullptr.");
        _window = w;
    }

    void Widget::addEventListener(Event event, const std::function<void (EventInfos&)>& callback)
    {
        lg("Widget::addEventListener");
        switch(event)
        {
#include "./Widget_events_impl_gen.h"

            case DRAG_START :
            {
                this->setDraggable();
                _drag_start.push(callback);
                break;
            }
            case DRAG_END : 
            {
                this->setDraggable();
                _drag_end.push(callback);
                break;
            }
            case DRAGGING : 
            {
                _drag_move.push(callback);
                break;
            }
        }
    }

    void Widget::setDraggable()
    {
        if (_draggable_setted)
            return;

        auto dstart = [this](EventInfos& infos)
        {
            _first_drag_event = true;
            _dragging = true;
        };

        auto dend = [this](EventInfos& infos)
        {
            bool was_dragging = this->isDragging();
            _dragging = false;
            _first_drag_event = false;

            if (was_dragging)
            {
                for (const auto& f : _drag_end)
                    f(infos);
            }
        };

        auto dmove = [this](EventInfos& infos)
        {
            if (_first_drag_event)
            {
                _first_drag_event = false;
                for (const auto& f : _drag_start)
                    f(infos);
            }
            if (this->isDragging())
            {
                for (const auto& f : _drag_move)
                    f(infos);
            }
        };

        this->addEventListener(MOUSE_DOWN, dstart);
        this->addEventListener(MOUSE_MOVE, dmove);
        this->addEventListener(MOUSE_UP, dend);

        _draggable_setted = true;
    }

    bool Widget::isDragging() const
    {
        return (_dragging);        
    }

    void Widget::triggerEvent(Event event, EventInfos& infos)
    {
        switch(event)        
        {
#include "./Widget_events_trigger_impl_gen.h"

            case DRAG_START : 
                for (const auto& f : _drag_start)
                    f(infos);
                break;
            case DRAG_END : 
                for (const auto& f : _drag_end)
                    f(infos);
                break;
            case DRAGGING : 
                for (const auto& f : _drag_move)
                    f(infos);
                break;
        }
    }

    void Widget::setContextMenu(const std::string& menuId)
    {
        auto f = [menuId, this](EventInfos &)
        {
            try
            {
                this->window()->showMenu(menuId);
            }
            catch(const std::exception& e)
            {
                lg(e.what());
            }
        };
        this->addEventListener(Event::RIGHT_DOWN, f);
    }

    bool Widget::isInside(double x,double y) const
    {
        auto pos = this->position();        
        auto r = this->right();
        auto b = this->bottom();

        return (x > pos.x && x < r && y > pos.y && y < b);
    }

    void Widget::setVisible(bool value)
    {
        if (value)        
            this->show();
        else 
            this->hide();
    }
}
