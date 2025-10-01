
#include "./CheckBox_impl.h"
#include "../CheckBox.h"

namespace ml
{
    CheckBox_impl::CheckBox_impl(CheckBox* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    CheckBox_impl::~CheckBox_impl()
    {
    }

    void CheckBox_impl::_createWidget()
    {
        auto domWidget  = em::createElement("div");
        domWidget["classList"].call<void, std::string>("add", "box");
        domWidget["classList"].call<void, std::string>("add", "horizontal");

        auto cb = em::newNode(domWidget, "input", "");
        cb.set("type", "checkbox");
        auto label = em::newNode(domWidget, "label", "", "label");

        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "checkBox");

        _checkbox = std::make_shared<emval>(cb);
        _label = std::make_shared<emval>(label);
    }

    void CheckBox_impl::setValue(bool value)
    {
        _checkbox->set("checked", value);	
    }

    bool CheckBox_impl::value()
    {
        return (*_checkbox)["checked"].as<bool>();	
    }

    void CheckBox_impl::setText(const std::string& text)
    {
        _label->set("innerText", text);
    }

    std::string CheckBox_impl::text()
    {
        return (*_label)["innerHTML"].as<std::string>();
    }
}
