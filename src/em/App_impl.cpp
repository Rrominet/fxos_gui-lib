#include "App_impl.h"
#include "App.h"
#include "../Window.h"

namespace ml
{
    void App_impl::init()
    {
        em::body()["classList"].call<void, std::string>("add", "mlgui");
        em::body().set<std::string>("id", "mlgui-body");
        this->setEvents();
    }

    void App_impl::setEvents()
    {
        em::addEventListener(em::body(), ml::Event::MOUSE_UP, [this](const emval& dom, const EmscriptenMouseEvent* e)
                {
                    _grabbed = nullptr;
                    _scaleGrabbed = nullptr;
                    lg("Ungrabbed (scale too.)");
                    return false;
                });

        em::addEventListener(em::body(), ml::Event::MOUSE_MOVE, [this](const emval& dom, const EmscriptenMouseEvent* e)
                {
                    bool res = this->onWindowMove(e);
                    if (res)
                        return res;

                    res = this->onWindowScaled(e);
                    if (res)
                        return res;
                    return false;
                });
    }


    bool App_impl::onWindowMove(const EmscriptenMouseEvent* e)
    {
        if (!_grabbed)
            return false;

        _grabbed->setPosition(e->clientX - _grabbed->grabbOffsetX(), e->clientY - _grabbed->grabbOffsetY());
        return true;
    }

    bool App_impl::onWindowScaled(const EmscriptenMouseEvent* e)
    {
        if (!_scaleGrabbed)
            return false;

        _scaleGrabbed->setSize(_scaleGrabbed->width() + e->movementX,
                _scaleGrabbed->height() + e->movementY);
        _scaleGrabbed->setMainHeight();
        return true;
    }

    void App_impl::run()
    {
        this->init();
        _app->windows()[0]->show();
    }

    void App_impl::unfocusAll()
    {
        for (auto w : _app->windows())
            w->unfocus();
    }

}
