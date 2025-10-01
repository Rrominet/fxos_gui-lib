#include "./AskPropertyGroupDialog.h"
#include "./App.h"
#include "./PropertiesManager.h"
#include "./props_utils.h"

#include "./Box.hpp"
#include "./Scrollable.hpp"

namespace ml
{
    AskPropertyGroupDialog::AskPropertyGroupDialog(App* app) : ConfirmDialog(app)
    {
    }

    AskPropertyGroupDialog::AskPropertyGroupDialog(App* app, ml::Window* parent) : ConfirmDialog(app, parent)
    {
    }

    AskPropertyGroupDialog::~AskPropertyGroupDialog(){}

    void AskPropertyGroupDialog::set(PropertyGroup* prop)
    {
        _prop = prop;
        _setCalled = true;
    }

    void AskPropertyGroupDialog::drawProp()
    {
        assert(_setCalled && "the method AskPropertyGroupDialog::set has not been called before AskPropertyGroupDialog::drawProp(), you nust call it before.");
        auto box = _main->appendPropertyGroup(_prop);
        this->setSize(-1, -1);
    }
}
