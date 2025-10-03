types = (
        "Window",
        "Dialog",
        )


def get() : 
    WindowsFactory_decl = "std::shared_ptr<ml::*type*> create*type*(ml::Window* parent = nullptr);"
    WindowsFactory_imp = """
        std::shared_ptr<ml::*type*> WindowsFactory::create*type*(ml::Window* parent)
        {
            ml::app()->checker().set("can-construct-window", true);

            std::shared_ptr<ml::*type*> window;
            if (parent)
                window = std::make_shared<ml::*type*>(ml::app(), parent);
            else
                window = std::make_shared<ml::*type*>(ml::app());

            ml::app()->windows().push_back(window);

            window->_impl = std::make_shared<ml::*type*_impl>(window.get());
            window->_impl->_createWindow();
            window->init();

            ml::app()->checker().set("can-construct-window", false);
            return window;
        }
    """

    short_decl = "std::shared_ptr<ml::*type*> create*type*(ml::Window* parent = nullptr){return _windowsFactory.create*type*(parent);}"

    WindowsFactory_decls = ""
    WindowsFactory_imps = ""
    short_decls = ""

    classes = ""
    gtk_includes = ""
    em_includes = ""
    includes = ""

    for t in types:
        WindowsFactory_decls += WindowsFactory_decl.replace("*type*", t) + "\n"
        WindowsFactory_imps+= WindowsFactory_imp.replace("*type*", t) + "\n\n"
        short_decls += short_decl.replace("*type*", t) + "\n"

        classes += "class " + t + ";\n"
        gtk_includes += "#include \"./gtk/" + t + "_impl.h\"\n"
        em_includes += "#include \"./em/" + t + "_impl.h\"\n"

    includes = "#ifdef __EMSCRIPTEN__\n" + em_includes + "#else\n" + gtk_includes + "#endif\n"
    return WindowsFactory_decls, WindowsFactory_imps, short_decls, classes, includes
