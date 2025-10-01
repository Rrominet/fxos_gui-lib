//This is a generated file, don't change it manually, it will be override when rebuild.


    std::shared_ptr<ml::Box> WidgetsFactory::createBox(ml::Window* parent)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Box>();
        widget->_impl = std::make_shared<ml::Box_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(&parent->content());
        parent->append(widget);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(&parent->content());
        parent->append(widget);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(&parent->content());
        parent->append(widget);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(&parent->content());
        parent->append(widget);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::Button> WidgetsFactory::createButton(ml::AbsoluteBox* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Button>();
        widget->_impl = std::make_shared<ml::Button_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::Button> WidgetsFactory::createButton(ml::Scrollable* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Button>();
        widget->_impl = std::make_shared<ml::Button_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::ToggleButton> WidgetsFactory::createToggleButton(ml::AbsoluteBox* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ToggleButton>();
        widget->_impl = std::make_shared<ml::ToggleButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::ToggleButton> WidgetsFactory::createToggleButton(ml::Scrollable* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ToggleButton>();
        widget->_impl = std::make_shared<ml::ToggleButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::Switch> WidgetsFactory::createSwitch(ml::AbsoluteBox* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Switch>();
        widget->_impl = std::make_shared<ml::Switch_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::Switch> WidgetsFactory::createSwitch(ml::Scrollable* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Switch>();
        widget->_impl = std::make_shared<ml::Switch_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::CheckBox> WidgetsFactory::createCheckBox(ml::AbsoluteBox* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::CheckBox>();
        widget->_impl = std::make_shared<ml::CheckBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::CheckBox> WidgetsFactory::createCheckBox(ml::Scrollable* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::CheckBox>();
        widget->_impl = std::make_shared<ml::CheckBox_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::ProgressBar> WidgetsFactory::createProgressBar(ml::AbsoluteBox* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ProgressBar>();
        widget->_impl = std::make_shared<ml::ProgressBar_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::ProgressBar> WidgetsFactory::createProgressBar(ml::Scrollable* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::ProgressBar>();
        widget->_impl = std::make_shared<ml::ProgressBar_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::Entry> WidgetsFactory::createEntry(ml::AbsoluteBox* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Entry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::Entry> WidgetsFactory::createEntry(ml::Scrollable* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Entry>();
        widget->_impl = std::make_shared<ml::Entry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::PasswordEntry> WidgetsFactory::createPasswordEntry(ml::AbsoluteBox* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::PasswordEntry>();
        widget->_impl = std::make_shared<ml::PasswordEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::PasswordEntry> WidgetsFactory::createPasswordEntry(ml::Scrollable* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::PasswordEntry>();
        widget->_impl = std::make_shared<ml::PasswordEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::SpinButton> WidgetsFactory::createSpinButton(ml::AbsoluteBox* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::SpinButton>();
        widget->_impl = std::make_shared<ml::SpinButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::SpinButton> WidgetsFactory::createSpinButton(ml::Scrollable* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::SpinButton>();
        widget->_impl = std::make_shared<ml::SpinButton_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::Slider> WidgetsFactory::createSlider(ml::AbsoluteBox* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Slider>();
        widget->_impl = std::make_shared<ml::Slider_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::Slider> WidgetsFactory::createSlider(ml::Scrollable* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Slider>();
        widget->_impl = std::make_shared<ml::Slider_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::Label> WidgetsFactory::createLabel(ml::AbsoluteBox* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Label>();
        widget->_impl = std::make_shared<ml::Label_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::Label> WidgetsFactory::createLabel(ml::Scrollable* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Label>();
        widget->_impl = std::make_shared<ml::Label_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::Spinner> WidgetsFactory::createSpinner(ml::AbsoluteBox* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Spinner>();
        widget->_impl = std::make_shared<ml::Spinner_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::Spinner> WidgetsFactory::createSpinner(ml::Scrollable* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Spinner>();
        widget->_impl = std::make_shared<ml::Spinner_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::Image> WidgetsFactory::createImage(ml::AbsoluteBox* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Image>();
        widget->_impl = std::make_shared<ml::Image_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::Image> WidgetsFactory::createImage(ml::Scrollable* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::Image>();
        widget->_impl = std::make_shared<ml::Image_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
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
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::MultilineEntry> WidgetsFactory::createMultilineEntry(ml::AbsoluteBox* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::MultilineEntry>();
        widget->_impl = std::make_shared<ml::MultilineEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::MultilineEntry> WidgetsFactory::createMultilineEntry(ml::Scrollable* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::MultilineEntry>();
        widget->_impl = std::make_shared<ml::MultilineEntry_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }

