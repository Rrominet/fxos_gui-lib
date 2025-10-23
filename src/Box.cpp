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

    std::shared_ptr<ml::Button> Box::appendCommand(Command* cmd)
    {
        auto btn = this->createButton(cmd->name());
        btn->setHelp(cmd->help());
        btn->addEventListener(Event::LEFT_UP, [cmd](const EventInfos&){cmd->exec();});
        GuiCommand* gui_cmd = dynamic_cast<GuiCommand*>(cmd);
        if (gui_cmd)
            gui_cmd->buttons().push(btn);
        return btn;
    }

    std::shared_ptr<ml::Button> Box::appendCommand(const std::string& id)
    {
        return this->appendCommand(ml::app()->cmds().command(id).get());
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
        for (size_t i = 0; i < _children.size(); i++)
            this->removeChild(_children[i]);
        _children.clear();
        _composedChildren.clear();
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

    std::shared_ptr<ml::Image> Box::createImage(bool icon)
    {
        return ml::app()->widgetsFactory().createImage(icon, this);
    }

#include "./Widget_creators_impl_gen.h"
#include "./Container_creators_impl_gen.h"
}
