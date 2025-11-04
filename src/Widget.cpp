
#include "./Box.h"
#include "./App.h"

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

    void Widget::_createWidget()
    {
        _impl = std::make_shared<Widget_impl>(this);
        _impl->_createWidget();
        _impl->_createBasicEvents();
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
        }
    }

    void Widget::triggerEvent(Event event, EventInfos& infos)
    {
        switch(event)        
        {
#include "./Widget_events_trigger_impl_gen.h"
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

}
