#include "./Box.h"
#include "./Scrollable.h"
#include "./App.h"
#include "./Property.h"
#include "./Button.h"
#include "./Image.h"
#include "./PropertyGroup.h"
#include "./Box.hpp"
#include "./ComboBox.h"
#include "./enums.h"
#include "./props_utils.h"
#include "AsyncGuiCommand.h"
#include <memory>

namespace ml
{
    Box::Box() : Widget()
    {

    }

    void Box::init(ml::Scrollable* scrollable)
    {
        _impl = std::make_shared<Box_impl>(this);
        _impl->_createWidget();
        _impl->_createBasicEvents();
        scrollable->setChild(*this);
        this->init();
    }

    void Box::init()
    {
        this->addCssClass("box");
        this->setOrient(Orient::VERTICAL);
    }

    void Box::append(std::shared_ptr<ml::Widget> child)
    {
        child->removeWindow();
        child->unparent();
        ml::app()->checker().set("can-set-window", true);
        if (this->hasWindow())
            child->setWindow(this->window());
        ml::app()->checker().set("can-set-window", false);
        this->box()->append(child);
        child->setParent(this);
        _children.push_back(child);
    }

    void Box::prepend(std::shared_ptr<ml::Widget> child)
    {
        child->removeWindow();
        child->unparent();
        ml::app()->checker().set("can-set-window", true);
        if (this->hasWindow())
            child->setWindow(this->window());
        ml::app()->checker().set("can-set-window", false);
        this->box()->prepend(child);
        _children.prepend(child);
    }

    void Box::removeChild(std::shared_ptr<ml::Widget> child)
    {
        this->removeChild(child.get());
    }

    void Box::removeChild(ml::Widget* child)
    {
        lg("Removing child : " << child);
        this->box()->remove(child);
        for (auto& c : _children)
        {
            if (c.get() == child)
            {
                _children.remove(c);
                break;
            }
        }
    }

    void Box::removeChild(ml::ComposedWidget* child)
    {
        for (auto w : child->composed())
        {
            std::visit([this](auto& w){
                    if (!w->isComposed())
                        this->removeChild(w);
                    }, w);
        }

        for (auto& c : _composedChildren)
        {
            if (c.get() == child)
            {
                _composedChildren.remove(c);
                break;
            }
        }
    }

    std::shared_ptr<ml::Button> Box::appendCommand(Command* cmd, const std::string& overrideButtonText)
    {
        auto btn = this->createButton(cmd->name());
        if (!overrideButtonText.empty())
            btn->setText(overrideButtonText);
        btn->setHelp(cmd->help());
        btn->addEventListener(Event::LEFT_UP, [cmd](const EventInfos&){cmd->exec();});
        GuiCommand* gui_cmd = dynamic_cast<GuiCommand*>(cmd);
        if (gui_cmd)
            gui_cmd->buttons().push(btn);
        return btn;
    }

    std::shared_ptr<ml::Button> Box::appendCommand(const std::string& id, const std::string& overrideButtonText)
    {
        return this->appendCommand(ml::app()->cmds().command(id).get(), overrideButtonText);
    }

    std::shared_ptr<ml::Image> Box::createIcon(const std::string& name)
    {
        std::string icons_path = ml::app()->paths().libdata()+ files::sep() + "images/icons"; // could be replaced by a prefs property system
        auto icon = this->createIconFromPath(icons_path + files::sep() + name + ".png");
        return icon;
    }
    
    std::shared_ptr<ml::Image> Box::createIconFromPath(const std::string& filepath)
    {
        int icons_width = 24;
        auto icon = this->createImage();
        lg("loading image " << filepath);
        icon->load(filepath);
        icon->setWidth(icons_width);
        icon->addCssClass("icon");
        icon->setHExpand(false);
        icon->setVExpand(false);
        return icon;
    }

    void Box::swap(size_t i, size_t j)
    {
        if (i >= _children.size() || j >= _children.size())
        {
            lg("Warning in Box::swap: index out of bounds : i = " + std::to_string(i) + ", j = " + std::to_string(j) + ", size = " + std::to_string(_children.size()));
            return;
        }

        if (i == j)
        {
            lg("Warning in Box::swap: indices are the same : i = " + std::to_string(i) + ", j = " + std::to_string(j));
            return;
        }

        if (i == j -1)
            this->box()->moveChild(i, j);
        else if (j == i - 1)
            this->box()->moveChild(j, i);
        else 
        {
            int _tmp = _children.size() - 1;
            this->box()->moveChild(i, _tmp);
            this->box()->moveChild(j, i);
            this->box()->moveChild(_tmp, j);
        }
        _children.swap(i, j);
    }

    void Box::swap(Widget* a,Widget* b)
    {
        int idx_a = this->childIndex(a);
        int idx_b = this->childIndex(b);
        
        if (idx_a == -1 || idx_b == -1)
        {
            lg("Warning in Box::swap: one or both widgets not found in children.");
            return;
        }
        
        this->swap((size_t)idx_a, (size_t)idx_b);
    }

    void Box::moveChildTop(Widget* child)
    {
        auto idx = this->childIndex(child);
        if (idx != 0)
            this->swap(idx, 0);
    }

    void Box::moveChildBottom(Widget* child)
    {
        auto idx = this->childIndex(child);
        if (idx != _children.size() - 1)
            this->swap(idx, _children.size() - 1);
    }

    bool Box::containsChild(Widget* child)
    {
        bool res = false;
        for (auto &c : _children)
        {
            if (c.get() == child)
            {
                res = true;
                break;
            }
        }
        return res;
    }

    int Box::childIndex(ml::Widget* child)
    {
        for (size_t i = 0; i < _children.size(); i++)
        {
            if (_children[i].get() == child)
                return i;
        }
        lg("Warning in Box::childIndex: child not found.");
        return -1;
    }

    // remove all children in it (deleting their memory)
    void Box::clear()
    {
        lg("Box::clear");
        lg("Removing " << _children.size() << " children");
        while (_children.size() > 0)
        {
            this->removeChild(_children[0]);
            lg("_children size : "<< _children.size());
        }
        while (_composedChildren.size() > 0)
        {
            this->removeChild(_composedChildren[0].get());
            lg("_composedChildren size : "<< _composedChildren.size());
        }

        lg("All children are removed.");
    }

    std::shared_ptr<ml::Box> Box::createSeparator()
    {
        auto _r = this->createBox();
        _r->addCssClass("separator");
        return _r;
    }

    std::shared_ptr<ml::Box> Box::appendPropertyGroup(ml::PropertyGroup* group)
    {
        auto _r = this->createBox();
        _r->addCssClass("property-group");
        for (auto& p : group->props())
            _r->appendPropBaseClass(p);
        return _r;
    }

    std::shared_ptr<ml::Box> Box::appendPropBaseClass(Property* prop)
    {
        std::shared_ptr<ml::Box> _r=nullptr;
        switch (prop->type())
        {
            case Property::BOOL:
                _r = this->appendProp<BoolProperty>((BoolProperty*)prop)->box();
                break;
            case Property::INT:
                _r = this->appendProp<IntProperty>((IntProperty*)prop)->box();
                break;
            case Property::FLOAT:
                _r = this->appendProp<FloatProperty>((FloatProperty*)prop)->box();
                break;
            case Property::DOUBLE:
                _r = this->appendProp<DoubleProperty>((DoubleProperty*)prop)->box();
                break;
            case Property::STRING:
                if (prop->isEnum())
                    _r = this->appendEnumProp((EnumProperty*)prop)->box();
                else
                    _r = this->appendProp<StringProperty>((StringProperty*)prop)->box();
                break;
            case Property::NONE:
                this->createLabel("Cannot create a property of type NONE.");
                break;
            default:
                this->createLabel("Cannot create a property when its type is unknown.");
        }
        return _r;
    }

    std::shared_ptr<ComposedPropertyWidget<EnumProperty>> Box::appendEnumProp(EnumProperty* prop)
    {
        auto _r = this->appendComposedProp(prop, COMBOBOX);
        auto cb = (ComboBox*)_r->input().get();
        props::connectComboBox(prop, cb);
        return _r;
    }

    std::shared_ptr<ComposedPropertyWidget<ColorProperty>> Box::appendColorProp(ColorProperty* prop, DrawType type)
    {
        auto _r = this->appendComposedProp(prop, type);
        return _r;
    }

    std::shared_ptr<ml::Image> Box::createImage(bool icon)
    {
        return ml::app()->widgetsFactory().createImage(icon, this);
    }


#include "./Widget_creators_impl_gen.h"
#include "./Container_creators_impl_gen.h"
}
