#include "./ComposedButton.h"
#include "./Box.h"
#include "./Scrollable.h"
#include "./Popover.h"
#include "./Label.h"
#include "./Spinner.h"

#include "./Box.hpp"
#include "./Scrollable.hpp"
#include "enums.h"

namespace ml
{
    void ComposedButton::__construct(Box* parent,const std::string& label)
    {
        _box = parent->createBox(); 
        _box->setOrient(ml::HORIZONTAL);
        _box->setVExpand(false);
        _box->addCssClass("button");
        _box->setFocusable(true);
        _box->setCursor("pointer");
        _box->setHAlign(CENTER);

        _label = _box->createLabel(label);
        _spinner = _box->createSpinner();
        _spinner->hide();

        _composed.push(_box.get());
    }

    ComposedButton::ComposedButton(Box* parent,const std::string& label)
    {
        __construct(parent,label);
    }

    ComposedButton::ComposedButton(Scrollable* parent,const std::string& label)
    {
        __construct(&parent->content(),label); 
    }

    ComposedButton::ComposedButton(Popover* parent,const std::string& label)
    {
        __construct(&parent->content()->content(),label); 
    }

    void ComposedButton::setText(const std::string& text)
    {
        _label->setText(text); 
    }

    void ComposedButton::setValue(const std::string& text)
    {
        _label->setText(text); 
    }

    std::string ComposedButton::text()
    {
        return _label->text(); 
    }

    std::string ComposedButton::value()
    {
        return _label->text(); 
    }

    void ComposedButton::mkLoading()
    {
        _spinner->show(); 
    }

    void ComposedButton::stopLoading()
    {
        _spinner->hide(); 
    }

    bool ComposedButton::isLoading()
    {
        return _spinner->isVisible();        
    }

    void ComposedButton::toggleLoading()
    {
        if (this->isLoading())        
            this->stopLoading();
        else
            this->mkLoading();
    }
}
