#include "./Paned.h"
#include "./Box.h"
#include "./Panel.h"
#include "./SearchableMenu.h"
#include "./App.h"
#include "EventInfos.h"
#include "enums.h"

namespace ml
{
    int _paned_created = -1;
    Paned::Paned(Box* parent)
    {
        _box = parent->createBox();
        _box->addCssClass("paned");
        _box->setHExpand(true);
        _box->setVExpand(true);

        _ctx = ml::app()->menusFactory().create("__paned_" + std::to_string(_paned_created++));
        _ctx->addButton("Split", [this]{this->split();});
        _ctx->addButton("Merge", [this]{this->merge();});
        _ctx->addSeparator();
        _ctx->addButton("Swap", [this]{this->swap();});
        _ctx->addButton("Change Orientation", [this]{this->changeOrient();});

        _box->setContextMenu(_ctx->id());
        _box->setSpacing(7);
        _setEvents();
    }

    void Paned::_setEvents()
    {
        auto mousedown = [this](ml::EventInfos& infos)
        {
            if (_aPanelHovered() && !_dragging)
                return;
            _dragging = true;
        };
        _box->addEventListener(LEFT_DOWN, mousedown);

        auto mouseup = [this](ml::EventInfos& infos)
        {
            if (_dragging)
                _dragging = false;
        };
        _box->addEventListener(LEFT_UP, mouseup);

        auto f = [this](ml::EventInfos& infos)
        {
            if (_aPanelHovered())
            {
                _box->setCursor("default");
                return;
            }
            else 
            {
                if (_orient == HORIZONTAL)
                    _box->setCursor("col-resize");
                else
                    _box->setCursor("row-resize");

                if (_dragging)
                {
                    float ratio = _ratio;
                    if (_orient == HORIZONTAL)
                        ratio = infos.x / _box->width();
                    else 
                        ratio = infos.y / _box->height();
                    this->setRatio(ratio);
                }
            }
        };
        _box->addEventListener(MOUSE_MOVE, f);
    }

    bool Paned::_aPanelHovered()
    {
        if (_first && _first->box()->hovered())
            return true;
        else if (_second && _second->box()->hovered())
            return true;
        return false;
    }

    void Paned::setOrient(Orient orient)
    {
        _box->setOrient(orient);	
        _orient = orient;

        if (_orient == HORIZONTAL && _first)
        {
            _first->_box->setHExpand(false);
            _first->_box->setVExpand(true);
        }
        else if (_orient == VERTICAL && _first)
        {
            _first->_box->setHExpand(true);
            _first->_box->setVExpand(false);
        }

        if (_orient == HORIZONTAL && _second)
        {
            _second->_box->setHExpand(true);
            _second->_box->setVExpand(true);
        }
        else if (_orient == VERTICAL && _second)
        {
            _second->_box->setHExpand(true);
            _second->_box->setVExpand(true);
        }

        this->setRatio(_ratio);
    }

    void Paned::merge()
    {
       if (_active == 0)
           this->removeSecond();
       else if (_active == 1)
           this->removeFirst();
    }

    void Paned::_remove(Panel* panel)
    {
        panel->_box->clear();
        panel->_paned = nullptr;
        _box->removeChild(panel->_box);
        panel->_box = nullptr;
    }

    void Paned::removeFirst()
    {
        if (!_first)
            return;
        _remove(_first.get());
        _first = nullptr;
        if (_second)
            _active = 1;
        else 
            _active = -1;
    }

    void Paned::removeSecond()
    {
        if (!_second)
            return;
        _remove(_second.get());
        _second = nullptr;
        if (_first)
        {
            _active = 0;
            _first->_box->setHExpand(true);
            _first->_box->setVExpand(true);
        }
        else 
            _active = -1;
    }

    Paned::~Paned(){}

    std::shared_ptr<Panel> Paned::_createPanel()
    {
        auto panel = std::make_shared<Panel>(this);
        panel->_box = _box->createBox();
        panel->_box->addCssClass("panel");

        auto menter = [this, panel](ml::EventInfos& infos)
        {
            if (_first)
                _first->_box->removeCssClass("active");
            if (_second)
                _second->_box->removeCssClass("active");
            if (panel.get() == _first.get())
                _active = 0;
            else if (panel.get() == _second.get())
                _active = 1;
            else 
            {
                _active = -1;
                return;
            }

            panel->_box->addCssClass("active");
        };
        panel->_box->addEventListener(MOUSE_ENTER, menter);

        return panel;
    }

    Panel* Paned::createFirst()
    {
        _first = _createPanel();
        _first->_box->addCssClass("first");
        if (_box->childIndex(_first->_box.get()) != 0)
            _box->swap(0, 1);
        this->setOrient(_orient);
        if (!_second)
        {
            _active = 0;
            _first->_box->setHExpand(true);
            _first->_box->setVExpand(true);
        }
        return _first.get();
    }

    Panel* Paned::createSecond()
    {
        _second = _createPanel();
        _second->_box->addCssClass("last");
        _second->_box->setHExpand(true);
        _second->_box->setVExpand(true);
        if (_first)
        {
            _first->_box->setHExpand(false);
            _first->_box->setVExpand(false);
        }
        if (_box->childIndex(_second->_box.get()) != 1)
            _box->swap(0, 1);
        this->setOrient(_orient);
        if (!_first)
            _active = 1;
        return _second.get();
    }

    void Paned::swap()
    {
        _box->swap(0, 1);
        auto _tmp = _first;
        _first = _second;
        _second = _tmp;
        this->setOrient(_orient);
    }

    void Paned::split()
    {
        if (!_first && !_second)
            return;

        else if (_first && _second)
        {
            auto active = this->active();
            if (!active)
            {
                lg("No active Panel, can't split.");
                return;
            }
            active->split();
        }

        else if (!_first)
        {
            auto infos = _second->infos();
            if (infos)
                this->createFirstFromInfos(infos);
            else 
                this->createFirst();
        }

        else if (!_second)
        {
            auto infos = _first->infos();
            if (infos)
                this->createSecondFromInfos(infos);
            else 
                this->createSecond();
        }
    }

    void Paned::setRatio(float ratio)
    {
        if (!_first || !_second)
            return;
        
        _ratio = ratio;
        int margin = _box->spacing();
                        
        if (_orient == HORIZONTAL)
        {
            _first->_box->setWidth(_ratio * (this->_box->width() - margin));
            _second->_box->setWidth(-1);
        }
        else
        {
            _first->_box->setHeight(_ratio * (this->_box->height() - margin));
            _second->_box->setHeight(-1);
        }
    }

    void Paned::changeOrient()
    {
        if (_orient == HORIZONTAL)
            this->setOrient(VERTICAL);
        else
            this->setOrient(HORIZONTAL);
    }

    Panel* Paned::createFirstFromInfos(PanelInfos* infos)
    {
        auto _r = this->createFirst();
        _r->drawFromInfos(infos);
        return _r;
    }

    Panel* Paned::createSecondFromInfos(PanelInfos* infos)
    {
        auto _r = this->createSecond();
        _r->drawFromInfos(infos);
        return _r;
    }

    Panel* Paned::active()
    {
        if (_active == -1)
            return nullptr;
        if (_active == 0 && _first)
            return _first.get();
        if (_active == 1 && _second)
            return _second.get();
        return nullptr;
    }
}
