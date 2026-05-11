#include "./Dialog.h"
#include "./App.h"

#ifdef __EMSCRIPTEN__
#include "./em/Dialog_impl.h"
#else
#include "./gtk/Dialog_impl.h"
#endif

namespace ml
{
    Dialog::Dialog(App* app) : Window(app)
    {
        if (_app->main())
            _parent = _app->main();
    }
    Dialog::Dialog(App* app, ml::Window* parent) : Window(app, parent){}

    void Dialog::init()
    {
        this->createBaseUi();
        this->setBasicEvents();
        this->hideOnClose(false);
    }
}
