#include "App_impl.h"
#include "../App.h"
#include "../Window.h"
#include "em.h"
#include <emscripten.h>
#include <emscripten/val.h>

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
        for (auto& w : _app->windows())
        {
            if (w.second->stayHiddenFirstRun())
                continue;
            w.second->show();
        }
        // Browser drives the event loop, nothing else needed here.
    }

    void App_impl::unfocusAll()
    {
        for (auto& w : _app->windows())
            w.second->unfocus();
    }

    // queue: just run on next JS event loop tick via setTimeout 0
    void App_impl::queue(const std::function<void()>& callback)
    {
        em::setTimeout(callback, 0);
    }

    // setTimeout: ms == 0 means next tick; interval==true repeats
    size_t App_impl::setTimeout(const std::function<void()>& callback, int ms, bool interval)
    {
        size_t id;
        if (!interval)
            id = em::setTimeout(callback, ms);
        else
            id = em::setInterval(callback, ms);

        _jsIntervalIds[id] = id;
        _lastId = id;
        return id;
    }

    void App_impl::removeTimeout(size_t id)
    {
        try
        {
            emscripten_clear_interval(_jsIntervalIds.at(id));
            _jsIntervalIds.erase(id);
        }
        catch(const std::exception& e)
        {
            ml::app()->error("App_impl::removeTimeout: " + std::string(e.what()));
        }
    }

    void App_impl::addCss(std::string filepath)
    {
        // Inject a <link> element into the document head
        auto link = em::newNode(em::head(), "link");
        link.set("rel", std::string("stylesheet"));
        link.set("href", filepath);
    }

    void App_impl::setClipboardText(const std::string& text)
    {
        emval::global("navigator")["clipboard"].call<void>("writeText", text);
    }

    std::string App_impl::clipboardText() const
    {
        // Clipboard read is async in browsers; return empty synchronously.
        return "";
    }

    void App_impl::openFile(const std::string& title,
            const std::string& initialDir,
            const std::function<void(const std::string&)>& callback)
    {
        auto input = emval::global("document").call<emval>("createElement", std::string("input"));
        input.set("type", std::string("file"));
        auto* cb = new std::function<void(const std::string&)>(callback);
        em::addEventListener(input, "change", [cb](const emval& event)
        {
            auto files = event["target"]["files"];
            if (files["length"].as<int>() > 0)
            {
                auto file = files[0];
                std::string name = file["name"].as<std::string>();
                (*cb)(name);
            }
            delete cb;
        });
        input.call<void>("click");
    }

    void App_impl::openFiles(const std::string& title,
            const std::string& initialDir,
            const std::function<void(const ml::Vec<std::string>&)>& callback)
    {
        auto input = emval::global("document").call<emval>("createElement", std::string("input"));
        input.set("type", std::string("file"));
        input.set("multiple", true);
        auto* cb = new std::function<void(const ml::Vec<std::string>&)>(callback);
        em::addEventListener(input, "change", [cb](const emval& event)
        {
            auto files = event["target"]["files"];
            int len = files["length"].as<int>();
            ml::Vec<std::string> result;
            for (int i = 0; i < len; i++)
                result.push(files[i]["name"].as<std::string>());
            (*cb)(result);
            delete cb;
        });
        input.call<void>("click");
    }

    void App_impl::openFolder(const std::string& title,
            const std::string& initialDir,
            const std::function<void(const std::string&)>& callback)
    {
        auto input = emval::global("document").call<emval>("createElement", std::string("input"));
        input.set("type", std::string("file"));
        input.call<void>("setAttribute", std::string("webkitdirectory"), std::string(""));
        auto* cb = new std::function<void(const std::string&)>(callback);
        em::addEventListener(input, "change", [cb](const emval& event)
        {
            auto files = event["target"]["files"];
            if (files["length"].as<int>() > 0)
            {
                auto file = files[0];
                std::string path = file["webkitRelativePath"].as<std::string>();
                // Return the folder part (everything before the last /)
                auto pos = path.find_last_of('/');
                if (pos != std::string::npos)
                    path = path.substr(0, pos);
                (*cb)(path);
            }
            delete cb;
        });
        input.call<void>("click");
    }

    void App_impl::openFolders(const std::string& title,
            const std::string& initialDir,
            const std::function<void(const ml::Vec<std::string>&)>& callback)
    {
        // Browsers only support one folder at a time via webkitdirectory
        auto input = emval::global("document").call<emval>("createElement", std::string("input"));
        input.set("type", std::string("file"));
        input.call<void>("setAttribute", std::string("webkitdirectory"), std::string(""));
        input.set("multiple", true);
        auto* cb = new std::function<void(const ml::Vec<std::string>&)>(callback);
        em::addEventListener(input, "change", [cb](const emval& event)
        {
            auto files = event["target"]["files"];
            int len = files["length"].as<int>();
            ml::Vec<std::string> folders;
            for (int i = 0; i < len; i++)
            {
                std::string path = files[i]["webkitRelativePath"].as<std::string>();
                auto pos = path.find_last_of('/');
                if (pos != std::string::npos)
                    path = path.substr(0, pos);
                if (!folders.contains(path))
                    folders.push(path);
            }
            (*cb)(folders);
            delete cb;
        });
        input.call<void>("click");
    }

    void App_impl::saveFile(const std::string& title,
            const std::string& initialDir,
            const std::function<void(const std::string&)>& callback)
    {
        // Use showSaveFilePicker if available, otherwise prompt for filename
        auto window = emval::global("window");
        if (!window["showSaveFilePicker"].isUndefined())
        {
            auto* cb = new std::function<void(const std::string&)>(callback);
            // Call via JS: window.showSaveFilePicker().then(...)
            auto promise = window.call<emval>("showSaveFilePicker");
            auto* cbThen = new std::function<void(const std::string&)>(*cb);
            delete cb;
            em::addEventListener(promise, "then", [cbThen](const emval& handle)
            {
                std::string name = handle["name"].as<std::string>();
                (*cbThen)(name);
                delete cbThen;
            });
        }
        else
        {
            // Fallback: prompt
            auto result = emval::global("window").call<emval>("prompt", std::string("Save as:"), std::string("file.txt"));
            if (!result.isNull() && !result.isUndefined())
            {
                std::string name = result.as<std::string>();
                if (!name.empty())
                    callback(name);
            }
        }
    }
}
