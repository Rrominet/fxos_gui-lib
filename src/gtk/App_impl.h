#pragma once
#include <gtkmm/application.h>
#include <glibmm/dispatcher.h>
#include "files.2/ResourcesManager.h"
#include <sigc++/connection.h>
#include <map>
#include <mutex>
#include <gtkmm/filedialog.h>

//if you set the gtkid in the constructor, GTK will force a single instance around your computer behavior.
//if you let it empty, it will allow multiple instances

namespace ml
{
    class App;
    class App_impl
    {
        public:
            App_impl(App* app, const std::string& gtkid="");
            App_impl(App* app, int argc, char *argv[], const std::string& gtkid="");
            virtual ~App_impl();

            void init();
            void addCss(std::string filepath);
            void run();

            size_t setTimeout(const std::function<void()>& callback, int ms, bool interval = false);
            void removeTimeout(size_t id);
            void removeInterval(size_t id){this->removeTimeout(id);}

            // can be called from any threads
            void queue(const std::function<void()>& callback);

            ml::ResourcesManager& resources(){return _resources;}
            const ml::ResourcesManager& resources() const{return _resources;}

            void quit() const;

            const std::map<std::string, std::string>& argv()const {return _argv;}

            void setClipboardText(const std::string& text);
            std::string clipboardText() const ;

            Gtk::Application& gtkapp(){return *_gtkapp;}

            std::string default_css() const;
            std::string color_variables_css() const;

            // launch a file fialog native to gtk
            void openFile(const std::string& title="Open File...", 
                    const std::string& initialDir="",
                    const std::function<void(const std::string&)>& callback = nullptr);

            void openFiles(const std::string& title="Open Files...", 
                    const std::string& initialDir="",
                    const std::function<void(const ml::Vec<std::string>&)>& callback = nullptr);

            void openFolder(const std::string& title="Open Folder...",
                    const std::string& initialDir="",
                    const std::function<void(const std::string&)>& callback = nullptr);

            void openFolders(const std::string& title="Open Folders...",
                    const std::string& initialDir="",
                    const std::function<void(const ml::Vec<std::string>&)>& callback = nullptr);

            void saveFile(const std::string& title="Save File...", 
                    const std::string& initialDir="",
                    const std::function<void(const std::string&)>& callback = nullptr);

            bool isDarkTheme() const;

        private : 
            Glib::RefPtr<Gtk::Application> _gtkapp;
            App* _app = nullptr;
            ml::ResourcesManager _resources;

            ml::Vec<std::string> _css_to_add;
            std::map<std::string, std::string> _argv;

            ml::Vec<sigc::connection> _timeouts;

            Glib::Dispatcher _dispatcher;
            std::mutex _queueMtx;
            std::queue<std::function<void()>> _queue;

            void _initQueueDispatcher();

            std::shared_ptr<Gtk::FileDialog> _filedialog = nullptr;

            void _createFileDialogIfNeeded(const std::string& title, const std::string& initialDir);
    };
}
