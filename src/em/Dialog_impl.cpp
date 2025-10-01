#include "./Dialog_impl.h"

namespace ml
{
    Dialog_impl::Dialog_impl(Dialog* win) : Window_impl(win)
    {
    }

    void Dialog_impl::_createWindow()
    {
        Window_impl::_createWindow();
        (*_dom)["classList"].call<void, std::string>("add", "dialog");
        _win->setTitle("Dialog");
    }
}
