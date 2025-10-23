#include "./Collapsable.h"
#include "./Box.h"
#include "./Image.h"
#include "./Label.h"
#include "./App.h"

namespace ml
{
    Collapsable::Collapsable(Box* parent, const std::string& label, bool collapsed) : ComposedWidget()
    {
        _box = parent->createBox();
        _box->addCssClass("collapsable");

        _header = _box->createBox();
        _header->setOrient(Orient::HORIZONTAL);
        _header->addCssClass("collapsable-header");
        _header->setCursor("pointer");

        _collapsedIcon = _header->createIcon("collapsed");
        if (ml::app()->isDarkTheme())
            _collapsedIcon->invert();
        _uncollapsedIcon = _header->createIcon("uncollapsed");
        if (ml::app()->isDarkTheme())
            _uncollapsedIcon->invert();
        _label = _header->createLabel(label);

        _body = _box->createBox();
        _body->addCssClass("collapsable-body");

        if (collapsed)
            this->collapse();
        else
            this->expand();

        _composed.push_back(_box.get());
        _composed.push_back(_header.get());
        _composed.push_back(_label.get());
        _composed.push_back(_body.get());
        _composed.push_back(_collapsedIcon.get());
        _composed.push_back(_uncollapsedIcon.get());

        _setEvents();
    }

    void Collapsable::_setEvents()
    {
        _header->addEventListener(Event::LEFT_UP, [this](EventInfos& e){this->toggle();});
    }

    void Collapsable::toggle()
    {
        lg("Collapsable::toggle");
        if (this->collapsed())
            this->expand();
        else
            this->collapse();
    }


    void Collapsable::collapse()
    {
        _uncollapsedIcon->hide();
        _collapsedIcon->show();
        _body->hide();
    }


    void Collapsable::expand()
    {
        _uncollapsedIcon->show();
        _collapsedIcon->hide();
        _body->show();
    }

    bool Collapsable::collapsed()
    {
        return !_body->isVisible();
    }


    void Collapsable::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        _box->addEventListener(event, callback);
    }

}
