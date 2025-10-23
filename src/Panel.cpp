#include "./Panel.h"
#include "./PanelInfos.h"
#include "./Box.h"
#include "./Paned.h"
#include "./Label.h"
#include "./Image.h"
#include "./enums.h"
#include "./App.h"
#include "./SearchableMenu.h"

namespace ml
{
    int _panels_chooser_created = 0;
    Panel::Panel(Paned* parent)
    {
        _parent = parent;
    }
    Panel::~Panel(){}

    void Panel::drawFromInfos(PanelInfos* infos)
    {
        _infos = infos;
        _box->clear();
        _header = _box->createBox();
        _header->addCssClass("panel-header");
        _header->setOrient(HORIZONTAL);
        auto title = _header->createLabel(_infos->id);
        title->addCssClass("panel-title");
        title->setHExpand(true);
        _changeIcon = _header->createIcon("dots-2-lines");
        _changeIcon->setCursor("pointer");
        _changeIcon->setWidth(22);
        _changeIcon->setHAlign(ml::RIGHT);
        for (auto& todraw : infos->todraw)
            todraw(this);

        auto chf = [this](EventInfos& event)
        {
            if (!_panelsChooser)
                this->createPanelsChooserMenu();
            _panelsChooser->show(); 
        };
        _changeIcon->addEventListener(Event::MOUSE_UP, chf);
    }

    void Panel::split()
    {
        _box->clear();
        _paned = std::make_unique<Paned>(_box.get());
        if (_infos)
        {
            _paned->createFirstFromInfos(_infos);
            _paned->createSecondFromInfos(_infos);
        }
        else
        {
            _paned->createFirst();
            _paned->createSecond();
        }
    }

    void Panel::createPanelsChooserMenu()
    {
        _panelsChooser = ml::app()->menusFactory().create<SearchableMenu>("__panels-chooser__" + std::to_string(_panels_chooser_created++));
        for (const auto& x : ml::app()->panels().infos())
        {
            std::string id = x.first;
            auto f = [this, id]
            {
                this->drawFromInfos(ml::app()->panels().get(id));
            };
            _panelsChooser->addButton(id, f);
        }
    }
}
