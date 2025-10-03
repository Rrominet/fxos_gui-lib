#include "./WindowsFactory.h"
#include "./App.h"
#include "./Window.h"
#include "./Dialog.h"

#include "./Window_types_includes_gen.h"

namespace ml
{
    template <typename T>
        std::shared_ptr<T> WindowsFactory::createWindow(ml::Window* parent, std::string id)
        {
            ml::app()->checker().set("can-construct-window", true);

            std::shared_ptr<T> window;
            if (parent)
                window = std::make_shared<T>(ml::app(), parent);
            else
                window = std::make_shared<T>(ml::app());

            if (id.empty())
                id = _newId();
            if (ml::app()->windowExists(id))
                id = _newId();

            window->_id = id;
            ml::app()->windows()[id] = window;

            window->_impl = std::make_shared<ml::Window_impl>(window.get());
            window->_impl->_createWindow();
            window->init();

            ml::app()->checker().set("can-construct-window", false);
            return window;
        }

    template <typename T>
        std::shared_ptr<T> WindowsFactory::createDialog(ml::Window* parent, std::string id)
        {
            ml::app()->checker().set("can-construct-window", true);

            std::shared_ptr<T> window;
            if (parent)
                window = std::make_shared<T>(ml::app(), parent);
            else
                window = std::make_shared<T>(ml::app());

            if (id.empty())
                id = _newId();
            if (ml::app()->windowExists(id))
                id = _newId();

            window->_id = id;
            ml::app()->windows()[id] = window;

            window->_impl = std::make_shared<ml::Dialog_impl>(window.get());
            window->_impl->_createWindow();
            window->init();

            ml::app()->checker().set("can-construct-window", false);
            return window;
        }
}
