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
        "WebView",
        )


#widgets with no gtk/em implementation but simply a child classs of a Widget
#The first is the name of the widget, the second is the name of the parent -- needed for the implementation type
widgets_children = (
        ("DateEntry", "Entry"),
        ("TimeEntry", "Entry"),
        ("DateTimeEntry", "Entry"),
        )

containers = (
        "Box",
        "Scrollable",
        "Popover",
        "AbsoluteBox",
        "Fixed",
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

    create = """
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::*type*>();
        widget->_impl = std::make_shared<ml::*type*_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    """
    init_events = """
        widget->init();
        widget->setEvents();
    """
    factoryCpp = """
    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*()
    {
        """ + create + init_events + """
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Window* parent)
    {
        """ + create + """
        parent->setChild(widget);
        """ + init_events + """
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Popover* parent)
    {
        """ + create + """
        parent->setChild(widget);
        """ + init_events + """
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Box* parent)
    {
        """ + create + """
        parent->append(widget);
        """ + init_events + """
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::AbsoluteBox* parent)
    {
        """ + create + """
        parent->append(widget);
        """ + init_events + """
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Fixed* parent)
    {
        """ + create + """
        parent->append(widget);
        """ + init_events + """
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Scrollable* parent)
    {
        """ + create + """
        widget->setParent(&parent->content());
        parent->append(widget);
        """ + init_events + """
        return widget;
    }

    """

    return (factoryH.replace("*type*", cType), factoryCpp.replace("*type*", cType))

def widgetCode(cType) : 
    factoryH = "std::shared_ptr<ml::*type*> create*type*();"
    for c in containers:
        factoryH += "\nstd::shared_ptr<ml::*type*> create*type*(ml::" + c +" * parent, const std::string& text = \"\");"

    create = """
        ml::app()->checker().set("can-construct-widget", true);
        auto widget = std::make_shared<ml::*type*>();
        widget->_impl = std::make_shared<ml::*itype*_impl>(widget.get());
        widget->_impl->_createWidget();
        widget->_impl->_createBasicEvents();
        widget->_createBasicEvents();
        ml::app()->checker().set("can-construct-widget", false);
    """
    init_events = """
        widget->init();
        widget->setEvents();
    """

    factoryCpp = """
    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*()
    {
        """ + create + """
        """ + init_events + """
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Box* parent,const std::string& text)
    {
        """ + create + """
        widget->setParent(parent);
        parent->append(widget);
        """ + init_events + """
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Fixed* parent,const std::string& text)
    {
        """ + create + """
        widget->setParent(parent);
        parent->append(widget);
        """ + init_events + """
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::AbsoluteBox* parent,const std::string& text)
    {
        """ + create + """
        widget->setParent(parent);
        parent->append(widget);
        """ + init_events + """
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Scrollable* parent,const std::string& text)
    {
        """ + create + """
        widget->setParent(parent);
        parent->append(widget);
        """ + init_events + """
        if (!text.empty())
            widget->setText(text);
        return widget;
    }

    std::shared_ptr<ml::*type*> WidgetsFactory::create*type*(ml::Popover* parent,const std::string& text)
    {
        """ + create + """
        widget->setParent(parent);
        parent->content()->append(widget);
        """ + init_events + """
        if (!text.empty())
            widget->setText(text);
        return widget;
    }
"""
    if (type(cType) == str) :
        factoryH = factoryH.replace("*type*", cType)
        factoryCpp = factoryCpp.replace("*type*", cType)
        factoryH = factoryH.replace("*itype*", cType)
        factoryCpp = factoryCpp.replace("*itype*", cType)
    elif (type(cType) == tuple) : 
        factoryH = factoryH.replace("*type*", cType[0])
        factoryCpp = factoryCpp.replace("*type*", cType[0])
        factoryH = factoryH.replace("*itype*", cType[1])
        factoryCpp = factoryCpp.replace("*itype*", cType[1])

    return (factoryH, factoryCpp)

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

    for i in widgets_children: 
        classes += "class " + i[0] + ";\n"
        includes += "#include \"./" + i[0] + ".h\"\n"

    includes += "#ifdef __EMSCRIPTEN__\n" + em_includes + "#else\n" + gtk_includes + "#endif\n"

    for i in containers:
        (h, cpp) = containerCode(i)
        containersFactoryH += h + "\n"
        containersFactoryCpp += cpp + "\n"
        containersCreators += "std::shared_ptr<ml::*type*> create*type*();\n".replace("*type*", i)
        containersCreators_cpp += "std::shared_ptr<ml::*type*> Box::create*type*(){return ml::app()->widgetsFactory().create*type*(this);}\n".replace("*type*", i)

    for i in widgets :
        widgets_classes += "class " + i + ";\n"
        (h, cpp) = widgetCode(i)
        widgetsFactoryH += h + "\n"
        widgetsFactoryCpp += cpp + "\n"
        widgetsCreators += "std::shared_ptr<ml::*type*> create*type*(const std::string& text=\"\");\n".replace("*type*", i)
        widgetsCreators_cpp += "std::shared_ptr<ml::*type*> Box::create*type*(const std::string& text){return ml::app()->widgetsFactory().create*type*(this, text);}\n".replace("*type*", i)

    for i in widgets_children :
        widgets_classes += "class " + i[0] + ";\n"
        (h, cpp) = widgetCode(i)
        widgetsFactoryH += h + "\n"
        widgetsFactoryCpp += cpp + "\n"
        widgetsCreators += "std::shared_ptr<ml::*type*> create*type*(const std::string& text=\"\");\n".replace("*type*", i[0])
        widgetsCreators_cpp += "std::shared_ptr<ml::*type*> Box::create*type*(const std::string& text){return ml::app()->widgetsFactory().create*type*(this, text);}\n".replace("*type*", i[0])

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
