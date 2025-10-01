#include "./App_impl.h"
#include "../App.h"
#include <iostream>
#include <gtkmm.h>
#include "files.2/files.h"
#include "glibmm/main.h"
#include "mlprocess.h"
#include <gdkmm/clipboard.h>

namespace ml
{
    App_impl::App_impl(App* app, const std::string& gtkid)
    {
        _app = app;
        if (!gtkid.empty())
            _gtkapp = Gtk::Application::create(gtkid);
        else 
            _gtkapp = Gtk::Application::create();
        _initQueueDispatcher();
    }

    App_impl::App_impl(App* app,int argc, char *argv[], const std::string& gtkid)
    {
        _app = app;
        if (!gtkid.empty())
            _gtkapp = Gtk::Application::create(gtkid);
        else 
            _gtkapp = Gtk::Application::create();
        _argv = args::nparse(argc, argv);
        _initQueueDispatcher();
    }

    App_impl::~App_impl()
    {
        lg("App_impl::~App_impl()");    
    }

    void App_impl::init()
    {
        _default_css = "mlgui_gtk.css";
    }

    void App_impl::_initQueueDispatcher()
    {
        _dispatcher.connect([this]() {
            lg("dispatcher received a signal.");
            lg("executing it from main thread : " << std::this_thread::get_id());
            std::queue<std::function<void()>> localQueue;

            // Lock and swap to reduce lock duration
            {
                std::lock_guard<std::mutex> lock(_queueMtx);
                std::swap(localQueue, _queue);
                lg("swap queues to local thread done.");
            }

            lg("executing " << localQueue.size() << " queued functions.");
            // Execute all queued functions
            while (!localQueue.empty()) {
                localQueue.front()(); // Run f()
                localQueue.pop();
            }
            lg("functions executed.");
        });

        lg("diapatcher initialized.");
        lg("dispatcher connected from this thread " << std::this_thread::get_id());
    }

    void App_impl::addCss(std::string filepath)
    {
        lg("App_impl::addCss(" << filepath << ")");
        filepath = _app->paths().path(filepath);
        auto provider = Gtk::CssProvider::create();
        Gtk::StyleContext::add_provider_for_display(Gdk::Display::get_default(), provider,
                GTK_STYLE_PROVIDER_PRIORITY_USER);

        provider->signal_parsing_error().connect([](const auto& section, const auto& error){std::cerr << "Parsing css error : " << error.what() <<  std::endl;}); 
        provider->load_from_path(filepath);
        lg("App_impl::addCss(" << filepath << ") -- css loaded and applied.");
    }

    void App_impl::run()
    {
        this->init();
        auto f = [this]
        {
            for (auto& p : _app->windows())
            {
                auto w = p.second;
                _gtkapp->add_window(*w->gtk());
            }

            this->addCss(_default_css);
            for (auto& css : _css_to_add)
                this->addCss(css);
            _css_to_add.clear();
            for (auto& w : _app->windows())
            {
                if (w.second->stayHiddenFirstRun())
                    continue;
                w.second->show();
            }
        };
        _gtkapp->signal_startup().connect(f);

        lg("gtk app is starting its main loop...");
        _gtkapp->run();

        _app->events().emit("quit"); 
    }

    size_t App_impl::setTimeout(const std::function<void()>& callback, int ms, bool interval)
    {
        lg("adding gtk timeout... ms = " << ms);
        auto slot = [callback, interval]() -> bool
        {
            callback();
            return interval;
        };

        auto tm = Glib::signal_timeout().connect(slot, ms);
        lg("timeout slot connected.");
        _timeouts.push_back(std::move(tm));
        lg("timeout id added to the inter list.");
        return _timeouts.size() - 1;
    }

    void App_impl::removeTimeout(size_t id)
    {
        if (_timeouts.size() > id)
            _timeouts[id].disconnect();
    }

    void App_impl::quit() const
    {
        _gtkapp->quit();
    }

    void App_impl::setClipboardText(const std::string& text)
    {
        _gtkapp->get_windows()[0]->get_display()->get_clipboard()->set_text(text);
    }

    std::string App_impl::clipboardText() const
    {
        std::string text;
        auto clipboard = _gtkapp->get_windows()[0]->get_display()->get_clipboard();
        clipboard->read_text_async({});
        return clipboard->read_text_finish({});
    }

    void App_impl::queue(const std::function<void()>& callback)
    {
        {
            std::lock_guard<std::mutex> lock(_queueMtx);
            lg("adding the function to the queue.");
            _queue.push(callback);
            lg("function added to the queue.");
        }

        _dispatcher.emit();
        lg("dispatcher emitted from this thread " << std::this_thread::get_id());
    }
}
