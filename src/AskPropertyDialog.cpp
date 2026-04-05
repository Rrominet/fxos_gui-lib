#include "./AskPropertyDialog.h"
#include "./App.h"
#include "./PropertiesManager.h"
#include "./props_utils.h"

#include "./Box.hpp"
#include "./Scrollable.hpp"

#ifdef __EMSCRIPTEN__
#else
#include "gtkmm/spinbutton.h"
#endif

namespace ml
{
    AskPropertyDialog::AskPropertyDialog(App* app) : ConfirmDialog(app)
    {
    }

    AskPropertyDialog::AskPropertyDialog(App* app, ml::Window* parent) : ConfirmDialog(app, parent)
    {
    }

    void AskPropertyDialog::init()
    {
        ConfirmDialog::init();
        this->setTitle("Informations Needed");
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
        auto input = props::propInput(_prop, box.get());

        _onok = [this, box](EventInfos&e)
        {
#ifdef __EMSCRIPTEN__
#else 
             auto input = props::propInput(_prop, box.get());
             Gtk::SpinButton* sb = dynamic_cast<Gtk::SpinButton*>(input->gtk().get());
             if (sb)
                 sb->update();
#endif
            _events.emit("ok");
            if (!this->doHideOnClose())
                this->destroy();
            else 
                this->hide();
        };

        this->setSize(540, 205);
        _prop->addOnValid([this]{
                    EventInfos e;
                    _onok(e);
                });
        
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
