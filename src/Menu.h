#pragma once
#include <memory>
#include <string>
#include "Popover.h"
#include "vec.h"
#include "Events.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// _events can emit : 
//  - shown -- just after the _popover has been happend to the box and shown.

namespace ml
{
    class MenuButton;
    class Command;
    class Window;
    class Menu 
    {
        public : 
            Menu(const std::string& id, const std::string& name="");
            virtual ~Menu();

            std::shared_ptr<ml::MenuButton> addButton(const std::string& text, const std::function<void()>& onClick=0, const std::string& keybind="");
            void removeButton(const std::string& text);
            void clear();

            std::shared_ptr<ml::MenuButton> addCommand(Command* cmd, const std::any& overrideArgs={}, const std::string& overrideText="");
            std::shared_ptr<ml::MenuButton> addCommand(const std::string& cmd_id, const std::any& overrideArgs={}, const std::string& overrideText="");

            void addSeparator();

            void show();
            void hide(){_popover->hide();}
            void redraw() {_popover->redraw();}   

            json serialize() const;
            void deserialize(const json& j);

        protected : 
            std::string _id; //bp cg
            std::string _name; //bp cgs
            ml::Vec<std::shared_ptr<ml::MenuButton>> _buttons; //bp cg
            std::shared_ptr<ml::Popover> _popover; //bp cg
            Events _events; //bp cg

            ml::Vec<std::string> _cmdsIds;
            
        public : 
#include "./Menu_gen.h"
    };
}
