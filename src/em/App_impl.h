#pragma once
#include "./em.h"
#include <map>
#include <unordered_map>

namespace ml
{
    class App;
    class Window_impl;
    class App_impl
    {
        public:
            App_impl(App* app){_app = app;}
            App_impl(App* app, int argc, char *argv[]){_app = app;}
            virtual ~App_impl() = default;

            void init();
            void setEvents();
            void run();
            void unfocusAll();

            void addCss(std::string filepath);
            void queue(const std::function<void()>& callback);

            size_t getNextTimeoutIdx(){return _lastId + 1;}

            size_t setTimeout(const std::function<void()>& callback, int ms, bool interval = false);
            void removeTimeout(size_t id);
            void removeInterval(size_t id){this->removeTimeout(id);}

            void setClipboardText(const std::string& text);
            std::string clipboardText() const ;

            bool onWindowMove(const EmscriptenMouseEvent* e);
            bool onWindowScaled(const EmscriptenMouseEvent* e);
            //changed

            // can't quit app in a browser.
            void quit() const{}
            //
 // launch a file fialog native to emscripten (the browser version)
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

            bool isDarkTheme() const {return true;}

            std::map<std::string, std::string> argv()const {return {};}

        private : 
            App* _app = nullptr;
            Window_impl* _grabbed = nullptr; //bp gs
            Window_impl* _scaleGrabbed = nullptr; //bp gs

            // timeout/interval tracking
            std::unordered_map<size_t, int> _jsIntervalIds;
            int _lastId = -1;

        public:
            #include "./App_impl_gen.h"
    };
}
