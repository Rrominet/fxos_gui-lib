#include "./Tabs.h"
#include "./TabButton.h"
#include "./Box.h"
#include "./Scrollable.h"
#include "./Label.h"
#include "enums.h"
#include <memory>
#include "./App.h"

namespace ml
{
    Tabs::Tabs(Box* parent) : _tabs{}
    {
        _header = parent->createBox();
        _body = parent->createScrollable();
        __construct();
    }

    Tabs::Tabs(Scrollable* parent) : _tabs{}
    {
        _header = parent->createBox();
        _body = parent->createScrollable();
        __construct();
    }


    void Tabs::__construct()
    {
        _header->addCssClass("tabs-header");
        _header->setOrient(Orient::HORIZONTAL);
        _header->setHAlign(ml::CENTER);
        _body->addCssClass("tabs-body");
        _body->setVExpand(true);
    }


    Tabs::~Tabs()
    {

    }


    TabButton* Tabs::createTab(const std::string& label)
    {
        auto btn = std::make_unique<TabButton>(this, label, _body->createBox());
        TabButton* ptr = btn.get();
        auto onclick = [this, ptr](EventInfos& event)
        {
            for (auto& t : _tabs)
                t->setActive(false);
            ptr->setActive(true);
        };

        btn->button()->addEventListener(Event::MOUSE_UP, onclick);
        btn->label()->addEventListener(Event::MOUSE_UP, onclick);

        _tabs.push_back(std::move(btn));
        return _tabs.back().get();
    }


    void Tabs::removeTab(TabButton* tab)
    {
        for (auto& t : _tabs)
        {
            if (t.get() == tab)
            {
                _tabs.remove(t);
                return;
            }
        }
    }


    void Tabs::removeTab(const std::string& label)
    {
        for (auto& t : _tabs)
        {
            if (t->label()->text() == label)
            {
                _tabs.remove(t);
                return;
            }
        }
    }


    void Tabs::hideAll()
    {
        for (auto& t : _tabs)
            t->setActive(false);
    }

    void Tabs::show(unsigned int index)
    {
        if (index < _tabs.size())
            _tabs[index]->setActive(true);
        else 
            _tabs.last()->setActive(true);
    }

    TabButton* Tabs::active() const
    {
        for (auto& t : _tabs) 
        {
            if (t->active())
                return t.get();
        }
        return nullptr;
    }

    int Tabs::activeIdx() const
    {
        for (unsigned int i = 0; i < _tabs.size(); i++)       
        {
            if (_tabs[i]->active())
                return i;
        }
        return -1;
    }

    void Tabs::setActiveIdx(unsigned int index)
    {
        for (auto&t : _tabs)        
            t->setActive(false);

        if (index >= _tabs.size())
            ml::app()->error("Index out of range : " + std::to_string(index) + " >= " + std::to_string(_tabs.size()));
        _tabs[index]->setActive(true);
    }
}
