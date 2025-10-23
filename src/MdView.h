#pragma once
#include "./ComposedWidget.h"
#include "md.h"
// a widget that render a markdown formated string

namespace ml
{
    class Box;
    class Label;
    class MdView : public ml::ComposedWidget
    {
        public : 
            MdView(ml::Box* parent);
            MdView(ml::Box* parent, double min, double max, double current=-1);
            virtual ~MdView() = default;

            virtual void addEventListener(Event event, const std::function<void(EventInfos&)>& callback) override;
            void setMdText(const std::string& txt);

            // alliases to keep the same interface as ml::Label
            void setText(const std::string& txt){ this->setMdText(txt); }
            void setValue(const std::string& txt){ this->setMdText(txt); }

            void setSelectable(bool sel = true);

            std::string text() const { return _mdtext; }
            std::string mdText() const { return _mdtext; }
            std::string value() const { return _mdtext; }

        protected : 
            virtual void _init(ml::Box* parent);
            ml::Box* _body;

            //corecpond to the last label crated reading the md
            std::string _currentHtml;
            std::string _mdtext;
            bool _isText = false; // if fase, it's html

            void _onEnterBlock(MD_BLOCKTYPE type, void* details, void* userdata);
            void _onLeaveBlock(MD_BLOCKTYPE type, void* details, void* userdata);
            void _onEnterSpan(MD_SPANTYPE type, void* details, void* userdata);
            void _onLeaveSpan(MD_SPANTYPE type, void* details, void* userdata);
            void _onText(const std::string& text, void* usderdata);
    };
}
