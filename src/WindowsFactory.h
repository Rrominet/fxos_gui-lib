#pragma once
#include <memory>

namespace ml
{
    class Window;
    class Dialog;
    class WindowsFactory
    {
        public:
            WindowsFactory() = default;
            virtual ~WindowsFactory() = default;

            template <typename T=ml::Window>
                std::shared_ptr<T> createWindow(ml::Window* parent = nullptr, std::string id="");

            template <typename T=ml::Dialog>
                std::shared_ptr<T> createDialog(ml::Window* parent = nullptr, std::string id="");

        private : 
            std::string _newId() const;
    };
}
