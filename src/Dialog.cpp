#include "./Dialog.h"

#ifdef __EMSCRIPTEN__
#include "./em/Dialog_impl.h"
#else
#include "./gtk/Dialog_impl.h"
#endif

namespace ml
{
    Dialog::Dialog(App* app) : Window(app){}
    Dialog::Dialog(App* app, ml::Window* parent) : Window(app, parent){}

    void Dialog::init()
    {
        this->createBaseUi();
        this->setBasicEvents();
        this->hideOnClose(false);
    }
}
