#pragma once
#include <string>
#include <unordered_map>
#include "./PanelInfos.h"
// a class that contains infos to build panels.
// It does not contains the Panel instances directly but a PanelInfos that give the rule to draw the Panel when it needs to be intanciated.
//
// The way it works is very easy, you create a PanelInfos for any Panel type want to be abale to draw.
// And you create one Paned with your PanelInfos to let the user selec the ones he is interested in.
// example : 
//         auto paned = new Paned(your_box_pointer);
// 
//         auto f = [](Panel* p)
//         {
//             p->box()->createLabel("First Panel");
//             p->box()->createButton("Click me");
//             p->box()->createSlider("I'm a slider");
//         };
// 
//         auto f2 = [](Panel* p)
//         {
//             p->box()->createLabel("Second Panel");
//             p->box()->createButton("Click me again");
//             p->box()->createSlider("I'm a slider");
//         };
// 
//         auto firstInfos = ml::app()->panels().create("Example Panel 1", f);
//         auto secondInfos = ml::app()->panels().create("Example Panel 2", f2);
//         auto first = paned->createFirstFromInfos(firstInfos);

namespace ml
{
    class PanelsManager
    {
        public:
            PanelsManager() = default;
            virtual ~PanelsManager() = default;

            // this will assert if the id already exists
            PanelInfos* create(const std::string& id, std::function<void(Panel*)> todraw);
            PanelInfos* get(const std::string& id) const;

            void clear();
            void remove(const std::string& id);

            bool has(const std::string& id) const {return _panelsInfos.find(id) != _panelsInfos.end();}

            const std::unordered_map<std::string, std::unique_ptr<PanelInfos>>& panelsInfos() const {return _panelsInfos;}
            // alias for panelsInfos
            const std::unordered_map<std::string, std::unique_ptr<PanelInfos>>& infos() const {return _panelsInfos;}

        protected : 
            std::unordered_map<std::string, std::unique_ptr<PanelInfos>> _panelsInfos;
    };
}
