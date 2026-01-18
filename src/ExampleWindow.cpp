#include "./ExampleWindow.h"
#include "./Box.h"
#include "./Scrollable.h"
#include "./Label.h"
#include "./Button.h"
#include "./Entry.h"
#include "./PasswordEntry.h"
#include "./SpinButton.h"
#include "./ProgressBar.h"
#include "./Slider.h"
#include "./CheckBox.h"
#include "./ToggleButton.h"
#include "./Switch.h"
#include "./Widget.h"
#include "./EventInfos.h"
#include "./Popover.h"
#include "./MenuBar.h"
#include "./Popover.h"
#include "./Image.h"
#include "./IconButton.h"
#include "./ComboBox.h"
#include "./Collapsable.h"
#include "./Paned.h"
#include "./Panel.h"
#include "./Dialog.h"
#include "./App.hpp"

#include "./Box.hpp"
#include "./Scrollable.hpp"
#include "./keybinds.h"
#include "./enums.h"
#include "./AskPropertyDialog.h"
#include "./AskPropertyGroupDialog.h"
#include "./VerticalTableModel.h"
#include "./VerticalTable.h"
#include "./Subrange.h"
#include "./VideoPlayer.h"
#include "./TimeSliderInOut.h"
#include "./MdView.h"
#include "./Canvas.h"
#include "./Fixed.h"

#include "./GuiCommand.h"
#include "./Commander.h"
#include "./CommandButton.h"
#include "./ListWidget.h"
#include "./WebView.h"
#include "./ColorPicker.h"
#include "./ColorButton.h"

#include <any>
#include <memory>

namespace ml
{
    void ExampleWindow::init()
    {
        Window::init();

        // example of using tabs.
        _tabs = std::make_unique<Tabs>(_main.get());
        _basicsWidgets = _tabs->createTab("Basics Widgets")->body();
        _composedWidgets = _tabs->createTab("Composed Widgets")->body();
        _fixed = _tabs->createTab("Fixed")->body();
        _basicsProperty = _tabs->createTab("Properties")->body();
        _propertyGroup = _tabs->createTab("Properties Groups")->body();
        _containers = _tabs->createTab("Containers")->body();
        _dialogs = _tabs->createTab("Dialogs")->body();
        _commands = _tabs->createTab("Commands")->body();
        _cursors = _tabs->createTab("Cursors")->body();
        _browser = _tabs->createTab("HTML Browser")->body();
        _tabs->show(0);

        this->createCommands();
        this->createBasicsWidgets();
        this->createComposedWidgets();
        this->createFixed();
        this->createBasicsProperties();
        this->createPropertyGroups();
        this->createContainers();
        this->createDialogs();
        this->createCursors();
        this->createExampleMenu();
        this->createHtmlExample();
    }

    void ExampleWindow::createBasicsWidgets()
    {
        auto lbl = _basicsWidgets->createLabel("This is a label.");
        auto btn = _basicsWidgets->createButton("Click Me !");
        _basicsWidgets->createButton("Click Me !");
        auto emptyEntry = _basicsWidgets->createEntry();
        emptyEntry->setHelp("Please, enter some text.");
        auto writtenEntry = _basicsWidgets->createEntry();
        writtenEntry->setValue("There is some text here.");
        _basicsWidgets->createPasswordEntry();
        _basicsWidgets->createSpinButton();
        _basicsWidgets->createSlider();

        auto pgr = _basicsWidgets->createProgressBar();
        pgr->setValue(0.265);

        auto ch = _basicsWidgets->createCheckBox("This is a checkbox");
        ch->setValue(true);

        auto toggle = _basicsWidgets->createToggleButton("Toggle Me !");
        toggle->setHelp("Toggle Me ! And see...");
        auto swicth = _basicsWidgets->createSwitch();
        swicth->setValue(true);

        emptyEntry->addEventListener(Event::MOUSE_DOWN, [](EventInfos& e){
                lg("emptyEntry : MOUSE_DOWN");             
                e.preventDefault = false;
                });

        emptyEntry->addEventListener(Event::MOUSE_UP, [](EventInfos& e){
                lg("emptyEntry : MOUSE_UP");             
                e.preventDefault = false;
                });

        emptyEntry->addEventListener(Event::CHANGE, [](EventInfos&){
                lg("emptyEntry : CHANGE");             
                });

        lbl->addEventListener(Event::MOUSE_DOWN, [](EventInfos&){
                lg("lbl : MOUSE_DOWN");             
                });

        toggle->addEventListener(Event::MOUSE_DOWN, [](EventInfos&){
                lg("toggle : MOUSE_DOWN");             
                });

        toggle->addEventListener(Event::CHANGE, [toggle](EventInfos&){
                lg("toggle : CHANGE");             
                if(toggle->value())
                toggle->setText("Im ONNNN ! :)");
                else 
                toggle->setText("Im OFF ! :(");
                });

        toggle->addEventListener(Event::LEFT_UP, [](EventInfos&){
                lg("toggle : LEFT_UP");             
                });

        btn->addEventListener(Event::LEFT_DOWN, [](EventInfos&){
                lg("btn : LEFT_DOWN");             
                });

        btn->addEventListener(Event::LEFT_UP, [](EventInfos&){
                });

        btn->addEventListener(Event::RIGHT_DOWN, [](EventInfos&){
                lg("btn : RIGHT_DOWN");             
                });

        btn->addEventListener(Event::RIGHT_UP, [](EventInfos&){
                lg("btn : RIGHT_UP");             
                });

        swicth->addEventListener(Event::CHANGE, [](EventInfos&){
                lg("swicth : CHANGE");             
                });

        _basicsWidgets->createSpinner();

        // tmp

        lbl->addEventListener(Event::MOUSE_UP, [this](EventInfos&){
                lg("lbl : MOUSE_UP");             
                this->showMenu("file");
                });

        btn->setContextMenu("file");
        _basicsWidgets->appendCommand(ml::app()->cmds().command("testlog1").get());

        _basicsWidgets->createLabel("Images :");
        auto imagesBox = _basicsWidgets->createBox();
        imagesBox->setOrient(HORIZONTAL);
        auto image = imagesBox->createImage();
        image->load("images/blender.jpg");

        image = imagesBox->createImage();
        image->load("images/not_exists.jpg");

        image = imagesBox->createImage();
        image->load("images/code.webp");

        _basicsWidgets->createMultilineEntry("This is some multiline text\nYep.");
        _basicsWidgets->createDateEntry("0000-01-01");
        _basicsWidgets->createTimeEntry("00:00:00");
        _basicsWidgets->createDateTimeEntry("0000-01-01 - 00:00:00");

        auto abox = _basicsWidgets->createAbsoluteBox();
        auto l1 = abox->createLabel("This is a label 1");
        auto l2 = abox->createLabel("this up");
        l2->setMargins(30, 30, 0, 0);
        abox->setHeight(100);

        auto canvas = _basicsWidgets->createCanvas();
        canvas->setHAlign(FILL);
        canvas->setHExpand();
        canvas->setHeight(200);
        auto d = [canvas](int w, int h)
        {
            canvas->fillRoundedRect(10, 10, 250, 50, 7, Color<double>(0.3));
            TextMetrics metrics = canvas->textMetrics("False Button");
            lg("x_bearing : " + std::to_string(metrics.x_bearing) + " y_bearing : " + std::to_string(metrics.y_bearing) + " width : " + std::to_string(metrics.width) + " height : " + std::to_string(metrics.height) + " x_advance : " + std::to_string(metrics.x_advance));

            canvas->fillRect(15, 15, metrics.width, metrics.height, Color<double>(1, 0, 0)); //chagn
            canvas->drawText(15, 15, "False Button", {}, Color<double>(1));
        };

        canvas->addToDraws(d);
    }

    void ExampleWindow::createComposedWidgets()
    {
        auto bx1 = _composedWidgets->createBox();
//         auto md = bx1->createComposedWidget<MdView>(bx1.get());
//         md->setMdText(files::read("/media/romain/Donnees/Brain/Dev/Config/Installer pycurl.md"));

        bx1->setOrient(Orient::HORIZONTAL);

        auto iconbutton = (IconButton*)bx1->createComposedWidget<IconButton>(bx1.get(), "down-arrow", "Icon Button").get();
        iconbutton = (IconButton*)bx1->createComposedWidget<IconButton>(bx1.get(), "down-arrow", "Icon Button (inverted)", true).get();
        iconbutton = (IconButton*)bx1->createComposedWidget<IconButton>(bx1.get(), "down-arrow", "Icon Button (reversed)", false, true).get();

        iconbutton->addEventListener(MOUSE_UP, [](EventInfos&){
                lg("IconButton : Clicked");  
        });

        _composedWidgets->createLabel("Combo Box :");
        auto combo = (ComboBox*)_composedWidgets->createComposedWidget<ComboBox>(_composedWidgets.get(), std::vector<std::string>{"Choice 1", "Choice 2", "Choice 3", "Choice 4"}).get();

        _composedWidgets->createLabel("Collapsable :");
        auto collapsable = (Collapsable*)_composedWidgets->createComposedWidget<Collapsable>(_composedWidgets.get(), "Collapsable").get();
        collapsable->body()->createLabel("I'm in the collapsable !");
        collapsable->body()->createButton("Me tooo");
        collapsable->body()->createComposedWidget<ColorButton>(collapsable->body().get());

        auto commander = (Commander*)_composedWidgets->createComposedWidget<Commander>(_composedWidgets.get()).get();
        commander->addAllCommands(ml::app());

        auto subrg = (Subrange*)_composedWidgets->createComposedWidget<Subrange>(_composedWidgets.get(), 0, 100, 33, 66).get();
// 
        auto vtable = (VerticalTable*)_composedWidgets->createComposedWidget<VerticalTable>(_composedWidgets.get()).get();
        auto model = std::make_shared<VerticalTableModel>();
        vtable->linkToModel(model); // vtable keep a reference to the shared_ptr of the model so it's perfect.
        model->setAttributes({
                std::make_pair(_S"Index", Property::PropertyType::INT),
                std::make_pair(_S"Name", Property::PropertyType::STRING),
                std::make_pair(_S"Age", Property::PropertyType::INT),
                std::make_pair(_S"City", Property::PropertyType::STRING),
                std::make_pair(_S"Work", Property::PropertyType::STRING),
                std::make_pair(_S"Revenue", Property::PropertyType::DOUBLE),
                });

        unsigned int idx = 0;
        for (size_t i=0; i<5; i++)
        {
            model->addToData({{"Index", idx}, {"Name", "Romain"}, {"Age", 33}, {"City", "Paris"}, {"Work", "Programmer"}, {"Revenue", 1000 }});
            idx++;
            model->addToData({{"Index", idx}, {"Name", "Maud"}, {"Age", 28}, {"City", "Andorre"}, {"Work", "ThreeJS"}, {"Revenue", 3000 }});
            idx++;
            model->addToData({{"Index", idx}, {"Name", "Lucas"}, {"Age", 18}, {"City", "Chamberry"}, {"Work", "Banquier"}, {"Revenue", 2300.34 }});
            idx++;
        }

        vtable->events().add("row-clicked", [vtable](){
            auto data = std::any_cast<VerticalRow*>(vtable->events().data());   
            lg("Clicked on row " << data->gui_index);
            lg("Real index in model : " << data->model_index);
            lg("GUI Box ptr : " << data->row);

            lg("Data : " << data->data().dump(4));
            lg("--");
        });

        _composedWidgets->createLabel("List Widget :");
        auto list = (ListWidget*)_composedWidgets->createComposedWidget<ListWidget>(_composedWidgets.get()).get();
        for (size_t i=0; i<5; i++)
        {
            auto w = ml::app()->widgetsFactory().createBox();
            w->createLabel("Label " + std::to_string(i));
            w->createButton("Click Me " + std::to_string(i));
            w->createSwitch();
            w->setOrient(ml::HORIZONTAL);

            list->add(w);
        }
    }

    void ExampleWindow::createFixed()
    {
        auto fixed = _fixed->createFixed();
        auto lbl = fixed->createLabel("Label Example");
        fixed->moveChild(lbl, 100, 20);

        auto btn = fixed->createButton("Button Example");
        fixed->moveChild(btn, 120, 100);

        auto spin = fixed->createSpinner();
        fixed->moveChild(btn, 220, 200);

        auto box = fixed->createBox();
        box->createLabel("Label in box");
        box->createButton("Button in box");
        box->createSwitch();
        box->setOrient(ml::VERTICAL);
        fixed->moveChild(box, 300, 300);
    }

    void ExampleWindow::createBasicsProperties()
    {
        auto basics = (Collapsable*)_basicsProperty->createComposedWidget<Collapsable>(_basicsProperty.get(), "Basics").get();

        auto prop1 =ml::app()->props().create<BoolProperty>("Visible", false, 0, 1, "this is a visible or not property");
        auto prop2 =ml::app()->props().create<IntProperty>("Int property", 42, 0, 100, "this is a int property");
        auto prop3 =ml::app()->props().create<FloatProperty>("Float number", 1.2, 0, 10, "this is a float number");
        auto prop4 =ml::app()->props().create<DoubleProperty>("Double number", 1.3445, 0, 10, "this is a double number (float on 64 bits)");
        auto prop5 =ml::app()->props().create<StringProperty>("Your name", "Romain", "This is a string property");
        auto prop7 =ml::app()->props().create<StringProperty>("Date", "2025-01-01", "This is a date string property");
        auto prop8 =ml::app()->props().create<StringProperty>("Time", "00:00:00", "This is a Time string property");
        auto prop9 =ml::app()->props().create<StringProperty>("Date Time", "2025-01-01 - 00:00:00", "This is a date time string property");
        auto prop10 =ml::app()->props().create<StringProperty>("File path", "/", "This is a filepath property");
        auto prop11 =ml::app()->props().create<StringProperty>("Dir path", "/", "This is a folder path property");

        basics->body()->appendProp(prop1, LABEL);
        basics->body()->appendProp(prop1, CHECKBOX);
        basics->body()->appendProp(prop1, TOGGLEBUTTON);
        basics->body()->appendProp(prop1, SWITCH);

        basics->body()->appendProp(prop2, LABEL);
        basics->body()->appendProp(prop2, SPINBUTTON);
        basics->body()->appendProp(prop2, SLIDER);
        basics->body()->appendProp(prop2, PROGRESS);

        basics->body()->appendProp(prop3, LABEL);
        basics->body()->appendProp(prop3, SPINBUTTON);
        basics->body()->appendProp(prop3, SLIDER);
        basics->body()->appendProp(prop3, PROGRESS);

        basics->body()->appendProp(prop4, LABEL);
        auto sp = basics->body()->appendProp(prop4, SPINBUTTON);
        sp->input()->setPrecision(3);
        sp->input()->setStep(0.2);
        basics->body()->appendProp(prop4, SLIDER);
        basics->body()->appendProp(prop4, PROGRESS);

        basics->body()->appendProp(prop5, LABEL);
        basics->body()->appendProp(prop5);
        basics->body()->appendProp(prop5, MULTILINE_ENTRY);

        basics->body()->appendProp(prop7, DATE);
        basics->body()->appendProp(prop8, TIME);
        basics->body()->appendProp(prop9, DATE_TIME);

        basics->body()->appendProp(prop10, FILE_PATH);
        basics->body()->appendProp(prop11, DIR_PATH);

        auto composed = (Collapsable*)_basicsProperty->createComposedWidget<Collapsable>(_basicsProperty.get(), "Composed").get();

        auto prop6 = ml::app()->props().create<EnumProperty>("Enumeration", "", "An example of an enumeration property");
        prop6->choices() = {"Choice 1", "Choice 2", "Choice 3", "Choice 4"};

        composed->body()->appendEnumProp(prop6);

        auto prop12 = ml::app()->props().create<ColorProperty>("Color", "An example of a color property", Color<double>(1, 0, 0, 1));
        composed->body()->appendColorProp(prop12);
        composed->body()->appendColorProp(prop12, COLOR_PICKER);
    }

    void ExampleWindow::createPropertyGroups()
    {
        auto name = ml::app()->props().create<StringProperty>("Firstname", "", "Your first name");
        auto age = ml::app()->props().create<IntProperty>("Age", 27, 0, 200, "Your age");
        auto mantra = ml::app()->props().create<StringProperty>("Mantra", "", "The phrase you live by.");
        auto ca = ml::app()->props().create<DoubleProperty>("Capital", 1000, 0, 1000000, "Your money right now.");

        _propertyGroup->createLabel("Several group representing the same data :");
        for (int i = 0; i < 3; i++)
        {
            auto person = ml::app()->props().createGroup({
                        name,
                        age,
                        mantra,
                        ca
                    }); 
            _propertyGroup->appendPropertyGroup(person);
        }
        _propertyGroup->createSeparator();
        _propertyGroup->createLabel("Several group representing different data :");

        for (int i = 0; i < 3; i++)
        {
            auto name = ml::app()->props().create<StringProperty>("Firstname", "", "Your first name");
            auto age = ml::app()->props().create<IntProperty>("Age", 27, 0, 200, "Your age");
            auto mantra = ml::app()->props().create<StringProperty>("Mantra", "", "The phrase you live by.");
            auto ca = ml::app()->props().create<DoubleProperty>("Capital", 1000, 0, 1000000, "Your money right now.");
            auto person = ml::app()->props().createGroup({
                        name,
                        age,
                        mantra,
                        ca
                    }); 
            _propertyGroup->appendPropertyGroup(person);
        }
    }

    void ExampleWindow::createContainers()
    {
        _containers->createLabel("Panels :");
        _containers->createLabel("For more infos on Panels, see the PanelsManager.h file.");
        auto paned = new Paned(_containers.get());

        auto f = [](Panel* p)
        {
            p->box()->createLabel("First Panel");
            p->box()->createButton("Click me");
            p->box()->createSlider("I'm a slider");
        };

        auto f2 = [](Panel* p)
        {
            p->box()->createLabel("Second Panel");
            p->box()->createButton("Click me again");
            p->box()->createSlider("I'm a slider");
        };

        auto firstInfos = ml::app()->panels().create("Example Panel 1", f);
        auto secondInfos = ml::app()->panels().create("Example Panel 2", f2);
        auto first = paned->createFirstFromInfos(firstInfos);
    }

    void ExampleWindow::createDialogs()
    {
        _dialogs->createLabel("Dialogs :");
        auto btn = _dialogs->createButton("Open an empty dialog");
        auto emptydg = [btn, this](EventInfos& e)
        {
            auto dialog = app()->createDialog(this);
            dialog->setTitle("Empty Dialog");
            dialog->main()->createLabel("This is an empty dialog");
            dialog->show();
        };
        btn->addEventListener(MOUSE_UP, emptydg);

        btn = _dialogs->createButton("Open an Message dialog");
        btn->addEventListener(MOUSE_UP, [this](EventInfos& e)
                    {
                        auto dg = app()->message("This is a message dialog.");
                        dg->events().add("ok", []{lg("Ok pressed.");});
                    }
                );

        btn = _dialogs->createButton("Open an Infos dialog");
        btn->addEventListener(MOUSE_UP, [](EventInfos& e){ml::app()->info("This is an info dialog.");});

        btn = _dialogs->createButton("Open an Warning dialog");
        btn->addEventListener(MOUSE_UP, [](EventInfos& e){ml::app()->warning("This is an warning dialog.");});

        btn = _dialogs->createButton("Open an Error dialog");
        btn->addEventListener(MOUSE_UP, [](EventInfos& e){ml::app()->error("This is an Error dialog.");});

        btn = _dialogs->createButton("Open Confirm dialog");
        btn->addEventListener(MOUSE_UP, [](EventInfos& e)
                {
                    auto conf = ml::app()->confirm("This is a confirm dialog.\nAre you sure of this action ?");
                    conf->events().add("ok", []{lg("Confirmed.");});
                    conf->events().add("cancel", []{lg("Cancelled.");});
                });

        btn = _dialogs->createButton("Open an Ask (Single Property - string) dialog");
        btn->addEventListener(MOUSE_UP, [](EventInfos& e)
                {
                    auto conf = ml::app()->ask(Property::STRING, "Name", "What is your name sir ?");
                    conf->events().add("ok", [conf]{lg("Confirmed : " << std::any_cast<std::string>(conf->value()));});
                    conf->events().add("cancel", []{lg("Cancelled.");});
                });
        btn = _dialogs->createButton("Open an Ask (Single Property - bool) dialog");
        btn->addEventListener(MOUSE_UP, [](EventInfos& e)
                {
                    auto conf = ml::app()->ask(Property::BOOL, "You're tall", "Is this true ?");
                    conf->events().add("ok", [conf]{lg("Confirmed : " << std::any_cast<bool>(conf->value()));});
                    conf->events().add("cancel", []{lg("Cancelled.");});
                });
        btn = _dialogs->createButton("Open an Ask (Single Property - int) dialog");
        btn->addEventListener(MOUSE_UP, [](EventInfos& e)
                {
                    auto conf = ml::app()->ask(Property::INT, "Age", "What is your age sir ?");
                    conf->events().add("ok", [conf]{lg("Confirmed : " << std::any_cast<int>(conf->value()));});
                    conf->events().add("cancel", []{lg("Cancelled.");});
                });
        btn = _dialogs->createButton("Open an Ask (Single Property - float) dialog");
        btn->addEventListener(MOUSE_UP, [](EventInfos& e)
                {
                    auto conf = ml::app()->ask(Property::FLOAT, "Size", "What is your size sir ?");
                    conf->events().add("ok", [conf]{lg("Confirmed : " << std::any_cast<float>(conf->value()));});
                    conf->events().add("cancel", []{lg("Cancelled.");});
                });
        btn = _dialogs->createButton("Open an Ask (Single Property - double) dialog");
        btn->addEventListener(MOUSE_UP, [](EventInfos& e)
                {
                    auto conf = ml::app()->ask(Property::DOUBLE, "Size", "What is your size (as a double) sir ?");
                    conf->events().add("ok", [conf]{lg("Confirmed : " << std::any_cast<double>(conf->value()));});
                    conf->events().add("cancel", []{lg("Cancelled.");});
                });

        btn = _dialogs->createButton("Open an Ask (Property Group) dialog");

        auto getGrpProp = []{
            auto name = ml::app()->props().create<StringProperty>("Firstname", "", "Your first name");
            auto age = ml::app()->props().create<IntProperty>("Age", 27, 0, 200, "Your age");
            auto mantra = ml::app()->props().create<StringProperty>("Mantra", "", "The phrase you live by.");
            auto ca = ml::app()->props().create<DoubleProperty>("Capital", 1000, 0, 1000000, "Your money right now.");

            return ml::app()->props().createGroup({name, age, mantra, ca});
        };
        btn->addEventListener(MOUSE_UP, [getGrpProp](EventInfos& e)
                {
                    auto conf = ml::app()->ask(getGrpProp(), "We need some information from you");
                    conf->events().add("ok", [conf]{lg("Confirmed.");});
                    conf->events().add("cancel", []{lg("Cancelled.");});
                });
    }

    void ExampleWindow::createExampleMenu()
    {
        auto file = ml::app()->menusFactory().create("file", "File");
        auto edit = ml::app()->menusFactory().create("edit", "Edit");
        ml::app()->menusFactory().create("view", "View");
        ml::app()->menusFactory().create("tools", "Tools");
        ml::app()->menusFactory().create("windows", "Windows");

        file->addCommand(ml::app()->cmds().command("testlog1").get());
        file->addButton("Open", 0, "Ctrl O");
        file->addButton("Save", 0, "Ctrl S");
        file->addButton("Save as", 0, "Ctrl Shift S");

        edit->addButton("New", 0 , "Ctrl N");
        edit->addButton("Open", 0, "Ctrl O");
        edit->addButton("Save");
        edit->addButton("Save as");

        _menuBar->addMenu("file");
        _menuBar->addMenu("edit");
        _menuBar->addMenu("view");
        _menuBar->addMenu("tools");
        _menuBar->addMenu("windows");
    }

    void ExampleWindow::createHtmlExample()
    {
        auto wv = _browser->createWebView();
        wv->setURI("https://motion-live.com");
    }

    void ExampleWindow::createCursors()
    {
        auto bts = _cursors->createBox();
        bts->setOrient(Orient::HORIZONTAL);

        auto none = bts->createButton("none");
        none->setCursor("none");

        auto _default = bts->createButton("default");
        _default->setCursor("default");

        auto help = bts->createButton("help");
        help->setCursor("help");

        auto pointer = bts->createButton("pointer");
        pointer->setCursor("pointer");

        auto context_menu = bts->createButton("context-menu");
        context_menu->setCursor("context-menu");

        auto progress = bts->createButton("progress");
        progress->setCursor("progress");

        auto wait = bts->createButton("wait");
        wait->setCursor("wait");

        auto cell = bts->createButton("cell");
        cell->setCursor("cell");

        auto crosshair = bts->createButton("crosshair");
        crosshair->setCursor("crosshair");

        auto text = bts->createButton("text");
        text->setCursor("text");

        auto vertical_text = bts->createButton("vertical-text");
        vertical_text->setCursor("vertical-text");

        auto alias = bts->createButton("alias");
        alias->setCursor("alias");

        auto copy = bts->createButton("copy");
        copy->setCursor("copy");

        auto no_drop = bts->createButton("no-drop");
        no_drop->setCursor("no-drop");

        auto move = bts->createButton("move");
        move->setCursor("move");

        auto grab = bts->createButton("grab");
        grab->setCursor("grab");

        auto grabbing = bts->createButton("grabbing");
        grabbing->setCursor("grabbing");

        auto all_scroll = bts->createButton("all-scroll");
        all_scroll->setCursor("all-scroll");

        auto col_resize = bts->createButton("col-resize");
        col_resize->setCursor("col-resize");

        auto row_resize = bts->createButton("row-resize");
        row_resize->setCursor("row-resize");

        auto n_resize = bts->createButton("n-resize");
        n_resize->setCursor("n-resize");

        auto e_resize = bts->createButton("e-resize");
        e_resize->setCursor("e-resize");

        auto w_resize = bts->createButton("w-resize");
        w_resize->setCursor("w-resize");

        auto ne_resize = bts->createButton("ne-resize");
        ne_resize->setCursor("ne-resize");

        auto nw_resize = bts->createButton("nw-resize");
        nw_resize->setCursor("nw-resize");

        auto sw_resize = bts->createButton("sw-resize");
        sw_resize->setCursor("sw-resize");

        auto se_resize = bts->createButton("se-resize");
        sw_resize->setCursor("se-resize");

        auto zoom_in = bts->createButton("zoom-in");
        zoom_in->setCursor("zoom-in");

        auto zoom_out = bts->createButton("zoom-out");
        zoom_out->setCursor("zoom-out");
    }

    void ExampleWindow::createCommands()
    {
        auto testlog1 = _app->cmds().createCommand<GuiCommand>("Test Log", "testlog1");
        testlog1->setHelp("This is a test log (1)");

        auto tlf = [](const std::any& args)
        {
            lg("testlog1");
        };

        testlog1->setExec(tlf);
        testlog1->setKeybind("ctrl a");

        auto testlog2 = _app->cmds().createCommand<GuiCommand>("Test Log", "testlog2");

        auto tlf2 = [](const std::any& args)
        {
            lg("testlog2");
        };

        testlog2->setExec(tlf2);
        testlog2->setKeybind("ctrl b");

        testlog2->setHelp("This is a test log (2nd version)");

        auto ctx = _app->menusFactory().create("Commands Example Menu");
        auto showMenu = _app->cmds().createCommand<GuiCommand>("Show Menu", "show_cmds_menu");
        auto showMenuf = [ctx, this](const std::any& args)
        {
            this->showMenu(ctx->id());
        };

        showMenu->setExec(showMenuf);

        auto longsync = _app->cmds().createCommand<GuiCommand>("Long Sync", "longsync");
        auto longsyncf = [](const std::any& args)
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
        };

        longsync->setExec(longsyncf);

        auto longasync = _app->cmds().createCommand<AsyncGuiCommand>("Wait 5 seconds Async", "longasync");
        auto longasyncf = [](const std::any& args)
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
        };

        longasync->setExec(longasyncf);

        auto confirm = _app->cmds().createCommand<GuiCommand>("Ask confirmation before", "confirm");
        auto confirmf = [](const std::any& args)
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
        };

        confirm->setConfirm(true);
        confirm->setExec(confirmf);

        for (auto& c : _app->cmds().commands())
        {
            _commands->appendCommand(c.second.get());
            ctx->addCommand(c.second.get());
        }

        _commands->setContextMenu(ctx->id());
    }
}
