#include "./AbsoluteBox.h"

#include "./Scrollable.h"
#include "./App.h"
#include "./Button.h"
#include "./Box.hpp"
#include "./enums.h"
#include "./ComposedWidget.h"
#include <variant>

namespace ml
{
    void AbsoluteBox::init(ml::Scrollable* scrollable)
    {
        _impl = std::make_shared<AbsoluteBox_impl>(this);
        _impl->_createWidget();
        _impl->_createBasicEvents();
        scrollable->setChild(*this);
        this->init();
    }

    void AbsoluteBox::init()
    {
        this->addCssClass("absolute-box");
        this->setHExpand(true);
    }

    void AbsoluteBox::append(std::shared_ptr<ml::Widget> child)
    {
        child->removeWindow();
        child->unparent();
        ml::app()->checker().set("can-set-window", true);
        if (this->hasWindow())
            child->setWindow(this->window());
        ml::app()->checker().set("can-set-window", false);
        this->absolute_box()->append(child);
        child->setParent(this);
        _children.push_back(child);
    }

    void AbsoluteBox::prepend(std::shared_ptr<ml::Widget> child)
    {
        child->removeWindow();
        child->unparent();
        ml::app()->checker().set("can-set-window", true);
        if (this->hasWindow())
            child->setWindow(this->window());
        ml::app()->checker().set("can-set-window", false);
        this->absolute_box()->prepend(child);
        _children.prepend(child);
    }

    void AbsoluteBox::removeChild(std::shared_ptr<ml::Widget> child)
    {
        this->removeChild(child.get());
    }

    void AbsoluteBox::removeChild(ml::Widget* child)
    {
        lg("AbsoluteBox::removeChild");
        child->removeWindow();
        child->unparent();
        this->absolute_box()->remove(child);

        for (auto& c : _children)
        {
            if (c.get() == child)
            {
                _children.remove(c);
                break;
            }
        }
    }

    void AbsoluteBox::removeChild(ml::ComposedWidget* child)
    {
        child->removeWindow();
        child->unparent();
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

    std::shared_ptr<ml::Button> AbsoluteBox::appendCommand(Command* cmd)
    {
        auto btn = this->createButton(cmd->name());
        btn->setHelp(cmd->help());
        btn->addEventListener(Event::LEFT_UP, [cmd](const EventInfos&){cmd->exec();});
        GuiCommand* gui_cmd = dynamic_cast<GuiCommand*>(cmd);
        if (gui_cmd)
            gui_cmd->buttons().push(btn);
        return btn;
    }

    std::shared_ptr<ml::Button> AbsoluteBox::appendCommand(const std::string& id)
    {
        return this->appendCommand(ml::app()->cmds().command(id).get());
    }

    std::shared_ptr<ml::Image> AbsoluteBox::createIcon(const std::string& name)
    {
        std::string icons_path = "images/icons"; // could be replaced by a prefs property system
        auto icon = this->createIconFromPath(icons_path + files::sep() + name + ".png");
        return icon;
    }

    std::shared_ptr<ml::Image> AbsoluteBox::createIconFromPath(const std::string& filepath)
    {
        int icons_width = 32;
        auto icon = this->createImage();
        lg("loading image " << filepath);
        icon->load(filepath);
        icon->setWidth(icons_width);
        icon->addCssClass("icon");
        icon->setHExpand(false);
        icon->setVExpand(false);
        return icon;
    }

    int AbsoluteBox::childIndex(ml::Widget* child)
    {
        for (size_t i = 0; i < _children.size(); i++)
        {
            if (_children[i].get() == child)
                return i;
        }
        lg("Warning in Box::childIndex: child not found.");
        return -1;
    }

    void AbsoluteBox::clear()
    {
        for (size_t i = 0; i < _children.size(); i++)
            this->removeChild(_children[i]);
        _children.clear();
        _composedChildren.clear();
    }


#include "./Widget_creators_implab_gen.h"
#include "./Container_creators_implab_gen.h"
}
