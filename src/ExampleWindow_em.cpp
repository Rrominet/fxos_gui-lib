#include "./ExampleWindow_em.h"
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
#include "./List.h"
#include "./WebView.h"
#include "./ColorPicker.h"
#include "./ColorButton.h"
#include "./ComposedButton.h"

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
        _commands = _tabs->createTab("Commands")->body();
        _tabs->show(0);

        this->createCommands();
        this->createBasicsWidgets();
        this->createComposedWidgets();
        this->createExampleMenu();

        ml::app()->setAbout("This is a Example App to let you know what is possible to accimplish with mlgui.");
    }

    void ExampleWindow::createBasicsWidgets()
    {
        auto lbl = _basicsWidgets->createLabel("This is a label.");
        auto btn = _basicsWidgets->createButton("Click Me !");
        btn->addEventListener(Event::LEFT_UP, [](EventInfos& e){lg("Clicked !");});
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

//         lbl->addEventListener(Event::MOUSE_UP, [this](EventInfos&){
//                 lg("lbl : MOUSE_UP");             
//                 this->showMenu("file");
//                 });
// 
//         btn->setContextMenu("file");
//         //_basicsWidgets->appendCommand(ml::app()->cmds().command("testlog1").get());
// 
//         _basicsWidgets->createLabel("Images :");
//         auto imagesBox = _basicsWidgets->createBox();
//         imagesBox->setOrient(HORIZONTAL);
//         auto image = imagesBox->createImage();
//         image->load("images/blender.jpg");
// 
//         image = imagesBox->createImage();
//         image->load("images/not_exists.jpg");
// 
//         image = imagesBox->createImage();
//         image->load("images/code.webp");
// 
//         _basicsWidgets->createMultilineEntry("This is some multiline text\nYep.");
//         _basicsWidgets->createDateEntry("0000-01-01");
//         _basicsWidgets->createTimeEntry("00:00:00");
//         _basicsWidgets->createDateTimeEntry("0000-01-01 - 00:00:00");
// 
//         auto abox = _basicsWidgets->createAbsoluteBox();
//         auto l1 = abox->createLabel("This is a label 1");
//         auto l2 = abox->createLabel("this up");
//         l2->setMargins(30, 30, 0, 0);
//         abox->setHeight(100);
// 
//         auto canvas = _basicsWidgets->createCanvas();
//         canvas->setHAlign(FILL);
//         canvas->setHExpand();
//         canvas->setHeight(200);
//         auto d = [canvas](int w, int h)
//         {
//             canvas->fillRoundedRect(10, 10, 250, 50, 7, Color<double>(0.3));
//             TextMetrics metrics = canvas->textMetrics("False Button");
//             lg("x_bearing : " + std::to_string(metrics.x_bearing) + " y_bearing : " + std::to_string(metrics.y_bearing) + " width : " + std::to_string(metrics.width) + " height : " + std::to_string(metrics.height) + " x_advance : " + std::to_string(metrics.x_advance));
// 
//             canvas->fillRect(15, 15, metrics.width, metrics.height, Color<double>(1, 0, 0)); //chagn
//             canvas->drawText(15, 15, "False Button", {}, Color<double>(1));
//         };
// 
//         canvas->addToDraws(d);
    }

    void ExampleWindow::createExampleMenu()
    {
        auto file = ml::app()->menusFactory().create("file", "File");
        auto edit = ml::app()->menusFactory().create("edit", "Edit");
        ml::app()->menusFactory().create("view", "View");
        ml::app()->menusFactory().create("tools", "Tools");
        auto windows = ml::app()->menusFactory().create("windows", "Windows");

        file->addCommand(ml::app()->cmds().command("testlog1").get());
        file->addButton("Open", 0, "Ctrl O");
        file->addButton("Save", 0, "Ctrl S");
        file->addButton("Save as", 0, "Ctrl Shift S");

        edit->addButton("New", 0 , "Ctrl N");
        edit->addButton("Open", 0, "Ctrl O");
        edit->addButton("Save");
        edit->addButton("Save as");

        windows->addCommand("about");

        _menuBar->addMenu("file");
        _menuBar->addMenu("edit");
        _menuBar->addMenu("view");
        _menuBar->addMenu("tools");
        _menuBar->addMenu("windows");
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
            lg("Adding " << c.second->name() << " in command widget.");
            _commands->appendCommand(c.second.get());
            ctx->addCommand(c.second.get());
        }

        _commands->setContextMenu(ctx->id());
    }

    void ExampleWindow::createComposedWidgets()
    {
        auto bx1 = _composedWidgets->createBox();
//         auto md = bx1->createComposedWidget<MdView>(bx1.get());
//         md->setMdText(files::read("/media/romain/Donnees/Brain/Dev/Config/Installer pycurl.md"));

        bx1->setOrient(Orient::HORIZONTAL);
        auto btn = (ComposedButton*)bx1->createComposedWidget<ComposedButton>(bx1.get(), "Composed Button").get();
        btn->addEventListener(ml::LEFT_UP, [btn](auto& e){
                    lg("Composed Button Clicked.");
                    btn->toggleLoading();
                });
    }
}
