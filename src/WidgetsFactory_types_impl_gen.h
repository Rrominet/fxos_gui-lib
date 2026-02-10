//This is a generated file, don't change it manually, it will be override when rebuild.


    std::shared_ptr<ml::Box> WidgetsFactory::createBox()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Box>();
        widget->_impl = std::make_shared<ml::Box_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Box> WidgetsFactory::createBox(ml::Window* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Box>();
        widget->_impl = std::make_shared<ml::Box_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->setChild(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Box> WidgetsFactory::createBox(ml::Popover* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Box>();
        widget->_impl = std::make_shared<ml::Box_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->setChild(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Box> WidgetsFactory::createBox(ml::Box* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Box>();
        widget->_impl = std::make_shared<ml::Box_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Box> WidgetsFactory::createBox(ml::AbsoluteBox* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Box>();
        widget->_impl = std::make_shared<ml::Box_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Box> WidgetsFactory::createBox(ml::Fixed* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Box>();
        widget->_impl = std::make_shared<ml::Box_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Box> WidgetsFactory::createBox(ml::Scrollable* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Box>();
        widget->_impl = std::make_shared<ml::Box_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(&parent->content());
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    

    std::shared_ptr<ml::Scrollable> WidgetsFactory::createScrollable()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Scrollable>();
        widget->_impl = std::make_shared<ml::Scrollable_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Scrollable> WidgetsFactory::createScrollable(ml::Window* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Scrollable>();
        widget->_impl = std::make_shared<ml::Scrollable_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->setChild(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Scrollable> WidgetsFactory::createScrollable(ml::Popover* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Scrollable>();
        widget->_impl = std::make_shared<ml::Scrollable_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->setChild(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Scrollable> WidgetsFactory::createScrollable(ml::Box* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Scrollable>();
        widget->_impl = std::make_shared<ml::Scrollable_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Scrollable> WidgetsFactory::createScrollable(ml::AbsoluteBox* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Scrollable>();
        widget->_impl = std::make_shared<ml::Scrollable_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Scrollable> WidgetsFactory::createScrollable(ml::Fixed* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Scrollable>();
        widget->_impl = std::make_shared<ml::Scrollable_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Scrollable> WidgetsFactory::createScrollable(ml::Scrollable* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Scrollable>();
        widget->_impl = std::make_shared<ml::Scrollable_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(&parent->content());
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    

    std::shared_ptr<ml::Popover> WidgetsFactory::createPopover()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Popover>();
        widget->_impl = std::make_shared<ml::Popover_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Popover> WidgetsFactory::createPopover(ml::Window* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Popover>();
        widget->_impl = std::make_shared<ml::Popover_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->setChild(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Popover> WidgetsFactory::createPopover(ml::Popover* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Popover>();
        widget->_impl = std::make_shared<ml::Popover_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->setChild(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Popover> WidgetsFactory::createPopover(ml::Box* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Popover>();
        widget->_impl = std::make_shared<ml::Popover_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Popover> WidgetsFactory::createPopover(ml::AbsoluteBox* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Popover>();
        widget->_impl = std::make_shared<ml::Popover_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Popover> WidgetsFactory::createPopover(ml::Fixed* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Popover>();
        widget->_impl = std::make_shared<ml::Popover_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Popover> WidgetsFactory::createPopover(ml::Scrollable* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Popover>();
        widget->_impl = std::make_shared<ml::Popover_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(&parent->content());
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    

    std::shared_ptr<ml::AbsoluteBox> WidgetsFactory::createAbsoluteBox()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::AbsoluteBox>();
        widget->_impl = std::make_shared<ml::AbsoluteBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::AbsoluteBox> WidgetsFactory::createAbsoluteBox(ml::Window* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::AbsoluteBox>();
        widget->_impl = std::make_shared<ml::AbsoluteBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->setChild(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::AbsoluteBox> WidgetsFactory::createAbsoluteBox(ml::Popover* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::AbsoluteBox>();
        widget->_impl = std::make_shared<ml::AbsoluteBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->setChild(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::AbsoluteBox> WidgetsFactory::createAbsoluteBox(ml::Box* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::AbsoluteBox>();
        widget->_impl = std::make_shared<ml::AbsoluteBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::AbsoluteBox> WidgetsFactory::createAbsoluteBox(ml::AbsoluteBox* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::AbsoluteBox>();
        widget->_impl = std::make_shared<ml::AbsoluteBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::AbsoluteBox> WidgetsFactory::createAbsoluteBox(ml::Fixed* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::AbsoluteBox>();
        widget->_impl = std::make_shared<ml::AbsoluteBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::AbsoluteBox> WidgetsFactory::createAbsoluteBox(ml::Scrollable* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::AbsoluteBox>();
        widget->_impl = std::make_shared<ml::AbsoluteBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(&parent->content());
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    

    std::shared_ptr<ml::Fixed> WidgetsFactory::createFixed()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Fixed>();
        widget->_impl = std::make_shared<ml::Fixed_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Fixed> WidgetsFactory::createFixed(ml::Window* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Fixed>();
        widget->_impl = std::make_shared<ml::Fixed_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->setChild(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Fixed> WidgetsFactory::createFixed(ml::Popover* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Fixed>();
        widget->_impl = std::make_shared<ml::Fixed_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->setChild(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Fixed> WidgetsFactory::createFixed(ml::Box* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Fixed>();
        widget->_impl = std::make_shared<ml::Fixed_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Fixed> WidgetsFactory::createFixed(ml::AbsoluteBox* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Fixed>();
        widget->_impl = std::make_shared<ml::Fixed_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Fixed> WidgetsFactory::createFixed(ml::Fixed* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Fixed>();
        widget->_impl = std::make_shared<ml::Fixed_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Fixed> WidgetsFactory::createFixed(ml::Scrollable* parent)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Fixed>();
        widget->_impl = std::make_shared<ml::Fixed_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(&parent->content());
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    


    std::shared_ptr<ml::Button> WidgetsFactory::createButton()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Button>();
        widget->_impl = std::make_shared<ml::Button_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Button> WidgetsFactory::createButton(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Button>();
        widget->_impl = std::make_shared<ml::Button_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Button> WidgetsFactory::createButton(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Button>();
        widget->_impl = std::make_shared<ml::Button_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Button> WidgetsFactory::createButton(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Button>();
        widget->_impl = std::make_shared<ml::Button_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Button> WidgetsFactory::createButton(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Button>();
        widget->_impl = std::make_shared<ml::Button_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Button> WidgetsFactory::createButton(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Button>();
        widget->_impl = std::make_shared<ml::Button_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::ToggleButton> WidgetsFactory::createToggleButton()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ToggleButton>();
        widget->_impl = std::make_shared<ml::ToggleButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::ToggleButton> WidgetsFactory::createToggleButton(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ToggleButton>();
        widget->_impl = std::make_shared<ml::ToggleButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::ToggleButton> WidgetsFactory::createToggleButton(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ToggleButton>();
        widget->_impl = std::make_shared<ml::ToggleButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::ToggleButton> WidgetsFactory::createToggleButton(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ToggleButton>();
        widget->_impl = std::make_shared<ml::ToggleButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::ToggleButton> WidgetsFactory::createToggleButton(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ToggleButton>();
        widget->_impl = std::make_shared<ml::ToggleButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::ToggleButton> WidgetsFactory::createToggleButton(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ToggleButton>();
        widget->_impl = std::make_shared<ml::ToggleButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::Switch> WidgetsFactory::createSwitch()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Switch>();
        widget->_impl = std::make_shared<ml::Switch_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Switch> WidgetsFactory::createSwitch(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Switch>();
        widget->_impl = std::make_shared<ml::Switch_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Switch> WidgetsFactory::createSwitch(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Switch>();
        widget->_impl = std::make_shared<ml::Switch_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Switch> WidgetsFactory::createSwitch(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Switch>();
        widget->_impl = std::make_shared<ml::Switch_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Switch> WidgetsFactory::createSwitch(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Switch>();
        widget->_impl = std::make_shared<ml::Switch_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Switch> WidgetsFactory::createSwitch(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Switch>();
        widget->_impl = std::make_shared<ml::Switch_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::CheckBox> WidgetsFactory::createCheckBox()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::CheckBox>();
        widget->_impl = std::make_shared<ml::CheckBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::CheckBox> WidgetsFactory::createCheckBox(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::CheckBox>();
        widget->_impl = std::make_shared<ml::CheckBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::CheckBox> WidgetsFactory::createCheckBox(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::CheckBox>();
        widget->_impl = std::make_shared<ml::CheckBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::CheckBox> WidgetsFactory::createCheckBox(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::CheckBox>();
        widget->_impl = std::make_shared<ml::CheckBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::CheckBox> WidgetsFactory::createCheckBox(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::CheckBox>();
        widget->_impl = std::make_shared<ml::CheckBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::CheckBox> WidgetsFactory::createCheckBox(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::CheckBox>();
        widget->_impl = std::make_shared<ml::CheckBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::ProgressBar> WidgetsFactory::createProgressBar()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ProgressBar>();
        widget->_impl = std::make_shared<ml::ProgressBar_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::ProgressBar> WidgetsFactory::createProgressBar(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ProgressBar>();
        widget->_impl = std::make_shared<ml::ProgressBar_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::ProgressBar> WidgetsFactory::createProgressBar(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ProgressBar>();
        widget->_impl = std::make_shared<ml::ProgressBar_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::ProgressBar> WidgetsFactory::createProgressBar(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ProgressBar>();
        widget->_impl = std::make_shared<ml::ProgressBar_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::ProgressBar> WidgetsFactory::createProgressBar(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ProgressBar>();
        widget->_impl = std::make_shared<ml::ProgressBar_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::ProgressBar> WidgetsFactory::createProgressBar(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ProgressBar>();
        widget->_impl = std::make_shared<ml::ProgressBar_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::Entry> WidgetsFactory::createEntry()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Entry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Entry> WidgetsFactory::createEntry(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Entry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Entry> WidgetsFactory::createEntry(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Entry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Entry> WidgetsFactory::createEntry(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Entry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Entry> WidgetsFactory::createEntry(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Entry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Entry> WidgetsFactory::createEntry(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Entry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::PasswordEntry> WidgetsFactory::createPasswordEntry()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::PasswordEntry>();
        widget->_impl = std::make_shared<ml::PasswordEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::PasswordEntry> WidgetsFactory::createPasswordEntry(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::PasswordEntry>();
        widget->_impl = std::make_shared<ml::PasswordEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::PasswordEntry> WidgetsFactory::createPasswordEntry(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::PasswordEntry>();
        widget->_impl = std::make_shared<ml::PasswordEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::PasswordEntry> WidgetsFactory::createPasswordEntry(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::PasswordEntry>();
        widget->_impl = std::make_shared<ml::PasswordEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::PasswordEntry> WidgetsFactory::createPasswordEntry(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::PasswordEntry>();
        widget->_impl = std::make_shared<ml::PasswordEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::PasswordEntry> WidgetsFactory::createPasswordEntry(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::PasswordEntry>();
        widget->_impl = std::make_shared<ml::PasswordEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::SpinButton> WidgetsFactory::createSpinButton()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::SpinButton>();
        widget->_impl = std::make_shared<ml::SpinButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::SpinButton> WidgetsFactory::createSpinButton(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::SpinButton>();
        widget->_impl = std::make_shared<ml::SpinButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::SpinButton> WidgetsFactory::createSpinButton(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::SpinButton>();
        widget->_impl = std::make_shared<ml::SpinButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::SpinButton> WidgetsFactory::createSpinButton(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::SpinButton>();
        widget->_impl = std::make_shared<ml::SpinButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::SpinButton> WidgetsFactory::createSpinButton(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::SpinButton>();
        widget->_impl = std::make_shared<ml::SpinButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::SpinButton> WidgetsFactory::createSpinButton(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::SpinButton>();
        widget->_impl = std::make_shared<ml::SpinButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::Slider> WidgetsFactory::createSlider()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Slider>();
        widget->_impl = std::make_shared<ml::Slider_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Slider> WidgetsFactory::createSlider(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Slider>();
        widget->_impl = std::make_shared<ml::Slider_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Slider> WidgetsFactory::createSlider(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Slider>();
        widget->_impl = std::make_shared<ml::Slider_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Slider> WidgetsFactory::createSlider(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Slider>();
        widget->_impl = std::make_shared<ml::Slider_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Slider> WidgetsFactory::createSlider(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Slider>();
        widget->_impl = std::make_shared<ml::Slider_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Slider> WidgetsFactory::createSlider(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Slider>();
        widget->_impl = std::make_shared<ml::Slider_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::Label> WidgetsFactory::createLabel()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Label>();
        widget->_impl = std::make_shared<ml::Label_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Label> WidgetsFactory::createLabel(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Label>();
        widget->_impl = std::make_shared<ml::Label_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Label> WidgetsFactory::createLabel(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Label>();
        widget->_impl = std::make_shared<ml::Label_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Label> WidgetsFactory::createLabel(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Label>();
        widget->_impl = std::make_shared<ml::Label_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Label> WidgetsFactory::createLabel(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Label>();
        widget->_impl = std::make_shared<ml::Label_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Label> WidgetsFactory::createLabel(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Label>();
        widget->_impl = std::make_shared<ml::Label_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::Spinner> WidgetsFactory::createSpinner()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Spinner>();
        widget->_impl = std::make_shared<ml::Spinner_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Spinner> WidgetsFactory::createSpinner(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Spinner>();
        widget->_impl = std::make_shared<ml::Spinner_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Spinner> WidgetsFactory::createSpinner(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Spinner>();
        widget->_impl = std::make_shared<ml::Spinner_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Spinner> WidgetsFactory::createSpinner(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Spinner>();
        widget->_impl = std::make_shared<ml::Spinner_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Spinner> WidgetsFactory::createSpinner(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Spinner>();
        widget->_impl = std::make_shared<ml::Spinner_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Spinner> WidgetsFactory::createSpinner(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Spinner>();
        widget->_impl = std::make_shared<ml::Spinner_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::Image> WidgetsFactory::createImage()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Image>();
        widget->_impl = std::make_shared<ml::Image_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::Image> WidgetsFactory::createImage(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Image>();
        widget->_impl = std::make_shared<ml::Image_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Image> WidgetsFactory::createImage(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Image>();
        widget->_impl = std::make_shared<ml::Image_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Image> WidgetsFactory::createImage(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Image>();
        widget->_impl = std::make_shared<ml::Image_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Image> WidgetsFactory::createImage(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Image>();
        widget->_impl = std::make_shared<ml::Image_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::Image> WidgetsFactory::createImage(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Image>();
        widget->_impl = std::make_shared<ml::Image_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::MultilineEntry> WidgetsFactory::createMultilineEntry()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::MultilineEntry>();
        widget->_impl = std::make_shared<ml::MultilineEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::MultilineEntry> WidgetsFactory::createMultilineEntry(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::MultilineEntry>();
        widget->_impl = std::make_shared<ml::MultilineEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::MultilineEntry> WidgetsFactory::createMultilineEntry(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::MultilineEntry>();
        widget->_impl = std::make_shared<ml::MultilineEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::MultilineEntry> WidgetsFactory::createMultilineEntry(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::MultilineEntry>();
        widget->_impl = std::make_shared<ml::MultilineEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::MultilineEntry> WidgetsFactory::createMultilineEntry(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::MultilineEntry>();
        widget->_impl = std::make_shared<ml::MultilineEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::MultilineEntry> WidgetsFactory::createMultilineEntry(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::MultilineEntry>();
        widget->_impl = std::make_shared<ml::MultilineEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::WebView> WidgetsFactory::createWebView()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::WebView>();
        widget->_impl = std::make_shared<ml::WebView_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::WebView> WidgetsFactory::createWebView(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::WebView>();
        widget->_impl = std::make_shared<ml::WebView_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::WebView> WidgetsFactory::createWebView(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::WebView>();
        widget->_impl = std::make_shared<ml::WebView_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::WebView> WidgetsFactory::createWebView(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::WebView>();
        widget->_impl = std::make_shared<ml::WebView_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::WebView> WidgetsFactory::createWebView(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::WebView>();
        widget->_impl = std::make_shared<ml::WebView_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::WebView> WidgetsFactory::createWebView(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::WebView>();
        widget->_impl = std::make_shared<ml::WebView_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::DateEntry> WidgetsFactory::createDateEntry()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::DateEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::DateEntry> WidgetsFactory::createDateEntry(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::DateEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::DateEntry> WidgetsFactory::createDateEntry(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::DateEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::DateEntry> WidgetsFactory::createDateEntry(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::DateEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::DateEntry> WidgetsFactory::createDateEntry(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::DateEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::DateEntry> WidgetsFactory::createDateEntry(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::DateEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::TimeEntry> WidgetsFactory::createTimeEntry()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::TimeEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::TimeEntry> WidgetsFactory::createTimeEntry(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::TimeEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::TimeEntry> WidgetsFactory::createTimeEntry(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::TimeEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::TimeEntry> WidgetsFactory::createTimeEntry(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::TimeEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::TimeEntry> WidgetsFactory::createTimeEntry(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::TimeEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::TimeEntry> WidgetsFactory::createTimeEntry(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::TimeEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }


    std::shared_ptr<ml::DateTimeEntry> WidgetsFactory::createDateTimeEntry()
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::DateTimeEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        
        widget->init();
        widget->setEvents();
    
        return widget;
    }

    std::shared_ptr<ml::DateTimeEntry> WidgetsFactory::createDateTimeEntry(ml::Box* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::DateTimeEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::DateTimeEntry> WidgetsFactory::createDateTimeEntry(ml::Fixed* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::DateTimeEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::DateTimeEntry> WidgetsFactory::createDateTimeEntry(ml::AbsoluteBox* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::DateTimeEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::DateTimeEntry> WidgetsFactory::createDateTimeEntry(ml::Scrollable* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::DateTimeEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::DateTimeEntry> WidgetsFactory::createDateTimeEntry(ml::Popover* parent,const std::string& text)
    {
        
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::DateTimeEntry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    
        widget->setParent(parent);
        parent->content()->append(widget);
        
        widget->init();
        widget->setEvents();
    
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

