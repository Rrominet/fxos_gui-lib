#include "./AskPropertyDialog.h"
#include "./App.h"
#include "./PropertiesManager.h"
#include "./props_utils.h"

#include "./Box.hpp"
#include "./Scrollable.hpp"

namespace ml
{
    AskPropertyDialog::AskPropertyDialog(App* app) : ConfirmDialog(app)
    {
    }

    AskPropertyDialog::AskPropertyDialog(App* app, ml::Window* parent) : ConfirmDialog(app, parent)
    {
    }

    AskPropertyDialog::~AskPropertyDialog()
    {
        if (_ownProp && _prop)
        {
            app()->props().destroy(_prop);
            _prop = nullptr;
        }
    }

    void AskPropertyDialog::set(Property::PropertyType type, const std::string&propname, const std::string& propdesc)
    {
        if (_prop && _ownProp)
            app()->props().destroy(_prop);
        _prop = app()->props().createFromType(type, propname);
        _prop->setDescription(propdesc);
        _setCalled = true;
    }
    void AskPropertyDialog::set(Property* prop)
    {
        _ownProp = false;
        _prop = prop;
        _setCalled = true;
    }

    void AskPropertyDialog::drawProp()
    {
        assert(_setCalled && "the method AskPropertyDialog::set has not been called before AskPropertyDialog::drawProp(), you nust call it before.");
        auto box = _main->appendPropBaseClass(_prop);

        this->setSize(-1, -1);
        _prop->addOnValid([this]{this->hide(); _events.emit("ok");});
        
        auto input = props::propInput(_prop, box.get());
        input->focus();
        if (_prop->isANumber())
            input->setHAlign(FILL);
    }

    std::any AskPropertyDialog::value()
    {
        assert(_prop && "AskPropertyDialog::value(), _prop is nullptr, should not happen.");
        return _prop->asAny();
    }
}
