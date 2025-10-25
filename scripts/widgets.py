widgets = (
        "Button",
        "ToggleButton",
        "Switch",
        "CheckBox",
        "ProgressBar",
        "Entry",
        "PasswordEntry",
        "SpinButton",
        "Slider",
        "Label",
        "Spinner",
        "Image",
        "MultilineEntry",
        )

containers = (
        "Box",
        "Scrollable",
        "Popover",
        "AbsoluteBox",
        )

all = widgets + containers

def containerCode(cType) : 
    factoryH = ""
    ls = []
    for c in containers : 
        ls.append(c)
    ls.append("Window")
    factoryH += "std::shared_ptr<ml::*type*> create*type*();\n"
    for c in ls : 
        factoryH += "std::shared_ptr<ml::*type*> create*type*(ml::*ContainerType** parent);\n".replace("*ContainerType*", c)

    factoryCpp = """
    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*()
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::*type*>();
        widget->_impl = std::make_shared<ml::*type*_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);

        widget->init();
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Window* parent)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::*type*>();
        widget->_impl = std::make_shared<ml::*type*_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);

        parent->setChild(widget);
        widget->init();
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Popover* parent)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::*type*>();
        widget->_impl = std::make_shared<ml::*type*_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);

        parent->setChild(widget);
        widget->init();
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Box* parent)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::*type*>();
        widget->_impl = std::make_shared<ml::*type*_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        parent->append(widget);
        widget->init();
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::AbsoluteBox* parent)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::*type*>();
        widget->_impl = std::make_shared<ml::*type*_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        parent->append(widget);
        widget->init();
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Scrollable* parent)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::*type*>();
        widget->_impl = std::make_shared<ml::*type*_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(&parent->content());
        parent->append(widget);
        widget->init();
        widget->setEvents();
        return widget;
    }
    """

    return (factoryH.replace("*type*", cType), factoryCpp.replace("*type*", cType))

def widgetCode(cType) : 
    factoryH = """
std::shared_ptr<ml::*type*> create*type*();
std::shared_ptr<ml::*type*> create*type*(ml::Box* parent, const std::string& text = "");
std::shared_ptr<ml::*type*> create*type*(ml::Scrollable* parent, const std::string& text = "");
std::shared_ptr<ml::*type*> create*type*(ml::AbsoluteBox* parent, const std::string& text = "");
std::shared_ptr<ml::*type*> create*type*(ml::Popover* parent, const std::string& text = "");
"""

    factoryCpp = """
    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*()
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::*type*>();
        widget->_impl = std::make_shared<ml::*type*_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->init();
        widget->setEvents();
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Box* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::*type*>();
        widget->_impl = std::make_shared<ml::*type*_impl>(widget.get());
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

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::AbsoluteBox* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::*type*>();
        widget->_impl = std::make_shared<ml::*type*_impl>(widget.get());
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

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Scrollable* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::*type*>();
        widget->_impl = std::make_shared<ml::*type*_impl>(widget.get());
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

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Popover* parent,const std::string& text)
    {
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::*type*>();
        widget->_impl = std::make_shared<ml::*type*_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
        widget->setParent(parent);
        parent->content()->append(widget);
        widget->init();
        if (!text.empty())
            widget->setText(text);
        widget->setEvents();
        return widget;
    }
"""
    return (factoryH.replace("*type*", cType), factoryCpp.replace("*type*", cType))

def popoverWidgetsImplCode() : 
    line = """std::shared_ptr<ml::*type*> ml::Popover::create*type*(const std::string& text){return _content->create*type*(text);}"""
    cline = """std::shared_ptr<ml::*type*> ml::Popover::create*type*(){return _content->create*type*();}"""

    _r = ""
    for w in widgets:
        _r += line.replace("*type*", w) + "\n"

    for c in containers:
        _r += cline.replace("*type*", c) + "\n"

    return _r

def get() : 
    classes = ""
    widgets_classes = ""
    includes = ""
    gtk_includes = ""
    em_includes = ""

    containersFactoryH = ""
    containersFactoryCpp = ""

    widgetsFactoryH = ""
    widgetsFactoryCpp = ""

    containersCreators = ""
    widgetsCreators = ""

    containersCreators_cpp = ""
    widgetsCreators_cpp = ""

    for i in all:
        classes += "class " + i + ";\n"
        includes += "#include \"./" + i + ".h\"\n"
        gtk_includes += "#include \"./gtk/" + i + "_impl.h\"\n"
        em_includes += "#include \"./em/" + i + "_impl.h\"\n"

    includes += "#ifdef __EMSCRIPTEN__\n" + em_includes + "#else\n" + gtk_includes + "#endif\n"

    for i in containers:
        (h, cpp) = containerCode(i)
        containersFactoryH += h + "\n"
        containersFactoryCpp += cpp + "\n"
        containersCreators += "std::shared_ptr<ml::*type*> create*type*();\n".replace("*type*", i)
        containersCreators_cpp += "std::shared_ptr<ml::*type*> Box::create*type*(){return ml::app()->widgetsFactory().create*type*(this);}\n".replace("*type*", i)

    for i in widgets:
        widgets_classes += "class " + i + ";\n"
        (h, cpp) = widgetCode(i)
        widgetsFactoryH += h + "\n"
        widgetsFactoryCpp += cpp + "\n"
        widgetsCreators += "std::shared_ptr<ml::*type*> create*type*(const std::string& text=\"\");\n".replace("*type*", i)
        widgetsCreators_cpp += "std::shared_ptr<ml::*type*> Box::create*type*(const std::string& text){return ml::app()->widgetsFactory().create*type*(this, text);}\n".replace("*type*", i)

    _r = {
            "containersFactoryH" : containersFactoryH,
            "containersFactoryCpp" : containersFactoryCpp,
            "widgetsFactoryH" : widgetsFactoryH,
            "widgetsFactoryCpp" : widgetsFactoryCpp,
            "classes" : classes,
            "includes" : includes,
            "containersCreators" : containersCreators,
            "widgetsCreators" : widgetsCreators,
            "containersCreators_cpp" : containersCreators_cpp,
            "widgetsCreators_cpp" : widgetsCreators_cpp,
            "widgets_classes" : widgets_classes,
            "popover_widgets_impl" : popoverWidgetsImplCode()
            }

    return _r
