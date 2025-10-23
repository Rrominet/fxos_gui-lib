#pragma once
#include "./Window.h"
#include "./Tabs.h"
#include "./TabButton.h"

namespace ml
{
    class Tabs;
    class ExampleWindow : public Window
    {
        public : 
            ExampleWindow(App* app) : Window(app) {}
            ExampleWindow(App* app, ml::Window* parent) : Window(app, parent) {}
            virtual ~ExampleWindow() = default;

            // all the important code go here.
            // don't forget call Window::init() before anything else
            virtual void init() override;

            void createBasicsWidgets();
            void createComposedWidgets();
            void createBasicsProperties();
            void createPropertyGroups();
            void createContainers();
            void createDialogs();
            void createCommands();
            void createCursors();
            void createExampleMenu();

        protected : 
            std::shared_ptr<Box> _basicsWidgets = nullptr;
            std::shared_ptr<Box> _composedWidgets = nullptr;
            std::shared_ptr<Box> _basicsProperty = nullptr;
            std::shared_ptr<Box> _propertyGroup = nullptr;
            std::shared_ptr<Box> _containers = nullptr;
            std::shared_ptr<Box> _dialogs = nullptr;
            std::shared_ptr<Box> _commands = nullptr;
            std::shared_ptr<Box> _cursors = nullptr;

            std::unique_ptr<Tabs> _tabs;
    };
}


