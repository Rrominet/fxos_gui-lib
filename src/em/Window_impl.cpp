#include "./Window_impl.h"
#include "../Window.h"
#include "../App.h"
#include "em.h"

namespace ml
{
    Window_impl::Window_impl(Window* win) : _win(win)
    {

    }
    Window_impl::~Window_impl()
    {
        lg("~Window_impl");
    }

    void Window_impl::_createWindow()
    {
        _draw();
        auto later = [this]
        {
            // FIXME : This is a problem because It's gonna be final even if overriden in a child class.
            this->setSize(640, 380);
            this->center();
            this->focus();
        };
        em::setTimeout(later, 0);
        _setBasicEvents();
    }

    void Window_impl::remove()
    {
        em::remove(*_dom);
    }

    void Window_impl::show()
    {
        if (!_drawn)
            _draw();
        em::show(*_dom);
    }

    void Window_impl::hide()
    {
        if (!_drawn)
            return;
        em::hide(*_dom);
        _onhide.exec();
    }

    void Window_impl::_draw()
    {
        lg("Creating the dom element for Window.");
        _dom = std::make_shared<emval>(em::newNode(em::body(), "div", "", "window"));
        _scaleGrabber = std::make_shared<emval>(em::newNode(*_dom, "div", "", "scale-grabber"));
        _titlebar = std::make_shared<emval>(em::newNode(*_dom, "div", "", "title-bar"));
        (*_titlebar)["classList"].call<void, std::string>("add", "box");
        (*_titlebar)["classList"].call<void, std::string>("add", "horizontal");
        _titlelabel = std::make_shared<emval>(em::newNode(*_titlebar, "label", "", "title-label"));
        _closeButton = std::make_shared<emval>(em::newNode(*_titlebar, "button", "", "close-button"));
        em::setFocusable(*_dom, true);
        _drawn = true;
    }

    void Window_impl::addCssClass(const std::string& cls)
    {
        (*_dom)["classList"].call<void>("add", cls);	
    }

    void Window_impl::removeCssClass(const std::string& cls)
    {
        (*_dom)["classList"].call<void>("remove", cls);	
    }

    void Window_impl::setSize(unsigned int w, unsigned int h)
    {
        if (_main)
            return;
        _width = w;
        _height = h;
        (*_dom)["style"].set("width", std::to_string(w) + "px");
        (*_dom)["style"].set("height", std::to_string(h) + "px");
    }

    void Window_impl::setWidth(unsigned int w)
    {
        if (_main)
            return;
        _width = w;
        (*_dom)["style"].set("width", std::to_string(w) + "px");
    }

    void Window_impl::setHeight(unsigned int h)
    {
        if (_main)
            return;
        _height = h;
        (*_dom)["style"].set("height", std::to_string(h) + "px");
    }

    void Window_impl::resetSize()
    {
        (*_dom)["style"].set("width", "");
        (*_dom)["style"].set("height", "");
    }

    void Window_impl::setPosition(double x,double y)
    {
        if (_main)
            return;
        _x = x;
        _y = y;
        (*_dom)["style"].set("left", std::to_string(x) + "px");
        (*_dom)["style"].set("top", std::to_string(y) + "px");
    }

    void Window_impl::move(double x,double y)
    {
        if (_main)
            return;
        _x += x;
        _y += y;
        (*_dom)["style"].set("left", std::to_string(x) + "px");
        (*_dom)["style"].set("top", std::to_string(y) + "px");
    }

    void Window_impl::resetPosition()
    {
        (*_dom)["style"].set("left", "");
        (*_dom)["style"].set("top", "");
    }

    void Window_impl::center()
    {
        if (_main)
            return;
        auto dw = em::innerWidth();
        auto dh = em::innerHeight();
        this->setPosition((dw - _width) / 2, (dh - _height) / 2);
    }

    void Window_impl::setChild(std::shared_ptr<ml::Widget> child)
    {
        lg("dom : ");
        lg(_dom);
        _dom->call<void, emval&>("appendChild", *child->dom());        
    }

    void Window_impl::setTitle(const std::string& title)
    {
        if (_main)
            emscripten_set_window_title(title.c_str());
        else
            _titlelabel->set<std::string>("innerText", title);
    }

    std::string Window_impl::title()
    {
        if(_main)
            return std::string(emscripten_get_window_title());
        else
            return (*_titlelabel)["innerText"].as<std::string>();
    }

    void Window_impl::_setBasicEvents()
    {
        auto onmm = [this](const emval& dom, const EmscriptenMouseEvent* e)
        {
            em::window().set("_mlMouseX", e->clientX);
            em::window().set("_mlMouseY", e->clientY);
            return false;
        };

        em::addEventListener(*_dom, ml::Event::MOUSE_MOVE, onmm);
 
        if (_main)
            return;
        em::addEventListener(*_closeButton, ml::Event::CLICK, [this](const emval& dom, const EmscriptenMouseEvent* e)
                {
                    if (_win->doHideOnClose())
                        _win->hide();
                    else
                    {
                        _onclose.exec();
                        _win->destroy();
                    }
                    return true;
                });

        em::addEventListener(*_titlebar, ml::Event::MOUSE_DOWN, [this](const emval& dom, const EmscriptenMouseEvent* e)
                {
                    _grabbOffsetX = e->clientX - _x;
                    _grabbOffsetY = e->clientY - _y;
                    ml::app()->impl().setGrabbed(this);
                    return true;
                });

        em::addEventListener(*_dom, ml::Event::MOUSE_DOWN, [this](const emval& dom, const EmscriptenMouseEvent* e)
                {
                    this->focus();
                    return false;
                });
        em::addEventListener(*_scaleGrabber, ml::Event::MOUSE_DOWN, [this](const emval& dom, const EmscriptenMouseEvent* e)
                {
                    ml::app()->impl().setScaleGrabbed(this);
                    return true;
                });
    }

    void Window_impl::focus()
    {
        ml::app()->impl().unfocusAll();
        if (!_main)
            (*_dom)["style"].set<std::string>("zIndex", "100");
        else 
            (*_dom)["style"].set<std::string>("zIndex", "0");
        (*_dom)["classList"].call<void, std::string>("add", "focused");
    }

    void Window_impl::unfocus()
    {
        if (_main)
            (*_dom)["style"].set<std::string>("zIndex", "0");
        else 
            (*_dom)["style"].set<std::string>("zIndex", "1");
        (*_dom)["classList"].call<void, std::string>("remove", "focused");
    }

    void Window_impl::setMainHeight()
    {
        auto h = _height; 
        if (!_win->main())
        {
            lg(" em/Window_impl::setMainHeight() failed -- No main.");
            return;
        }
        if (!_win->foot())
        {
            lg(" em/Window_impl::setMainHeight() failed -- No foot.");
            return;
        }

        h -= (em::y(*(_win->main()->scrollable()->widget())) - _y);
        h -= em::height(*_titlebar);
        h -= em::height(*(_win->foot()->box()->widget()));
        (*(_win->main()->scrollable()->widget()))["style"].set("height", std::to_string(h) + "px");
    }

    void Window_impl::setMain(bool main)
    {
        _main = main;
        this->setMainHeight();
        if (main)
        {
            this->resetSize();
            this->resetPosition();
        }
    }

    math::vec2d Window_impl::mousePos()
    {
        auto rect = (*_dom).call<emval>("getBoundingClientRect");
        double domX = rect["x"].as<double>();
        double domY = rect["y"].as<double>();

        auto mouseX = em::window()["_mlMouseX"].as<double>();
        auto mouseY = em::window()["_mlMouseY"].as<double>();

        return math::vec2d(mouseX - domX, mouseY - domY);
    }

    void Window_impl::addWheelEventListener(const std::function<void(EventInfos&)>& callback)
    {
        em::addEventListener(*_dom, "wheel", [callback](const emval& event)
        {
            EventInfos e;
            e.dx = event["deltaX"].as<double>();
            e.dy = event["deltaY"].as<double>();
            callback(e);
        });
    }

    void Window_impl::setResizeEventListener(const std::function<void(EventInfos&)>& callback)
    {
        em::addEventListener(em::window(), "resize", [this, callback](const emval& event)
        {
            EventInfos e;
            e.width = _width;
            e.height = _height;
            callback(e);
        });
    }
}
