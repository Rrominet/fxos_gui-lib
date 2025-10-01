#include "./MdView.h"
#include "./Box.h"
#include "./Label.h"

#include "./Box.hpp"
#include "str.h"

namespace ph = std::placeholders;
namespace ml
{
    ml::Vec<std::string> _supported_tags = {
        "b",
        "i",
        "u",
        "s",
        "tt",
        "big",
        "small",
        "sub",
        "span",
        "markup",
    };

    MdView::MdView(ml::Box* parent)
    {
        _init(parent);
    }

    MdView::MdView(ml::Box* parent,double min,double max,double current)
    {
        _init(parent);
    }

    void MdView::_init(ml::Box* parent)
    {
        _body = parent->createBox().get(); 
        _body->setOrient(Orient::VERTICAL);
        _body->addCssClass("mdview");

        _composed.push_back(_body);
    }

    void MdView::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        _body->addEventListener(event, callback);
    }

    void MdView::setMdText(const std::string& txt)
    {
        _mdtext = txt;
        _body->clear();
        md::parse(txt,
                std::bind(&MdView::_onEnterBlock, this, ph::_1, ph::_2, ph::_3),
                std::bind(&MdView::_onLeaveBlock, this, ph::_1, ph::_2, ph::_3),
                std::bind(&MdView::_onEnterSpan, this, ph::_1, ph::_2, ph::_3),
                std::bind(&MdView::_onLeaveSpan, this, ph::_1, ph::_2, ph::_3),
                std::bind(&MdView::_onText, this, ph::_1, ph::_2));
    }

    void MdView::_onEnterBlock(MD_BLOCKTYPE type,void* details,void* userdata)
    {
        if (!_currentHtml.empty())
        {
            _currentHtml += "\n\t";
            _currentHtml = str::replace(_currentHtml, "\n\t\n\t", "\n\t");
            _currentHtml = str::replace(_currentHtml, "\n\n", "\n");
        }
        else 
            _isText = false;
    }

    void MdView::_onLeaveBlock(MD_BLOCKTYPE type,void* details,void* userdata)
    {
        if (_currentHtml.size() == 0)
            return;

        if (type == MD_BLOCK_UL || type == MD_BLOCK_OL || type == MD_BLOCK_TR || type == MD_BLOCK_THEAD || type == MD_BLOCK_TBODY)
            return;

        auto current = _body->createLabel().get();

        if (type == MD_BLOCK_H)
        {
            std::string cls = "h";
            auto hdetails = (MD_BLOCK_H_DETAIL*)details;
            cls += std::to_string(hdetails->level);
            current->addCssClass(cls);
        }
        else 
            current->addCssClass(md::bloc_type(type));

        if (type == MD_BLOCK_CODE)
            current->setSelectable();

        if (_currentHtml.size() > 1 && str::last(_currentHtml) == '\n')
            _currentHtml.pop_back();

        // FIXME : I can't use this every time because certain character make it buggy
        if (type == MD_BLOCK_CODE)
            current->setText(_currentHtml);
        else if (_isText)
            current->setText(_currentHtml);
        else 
            current->setHtml(_currentHtml);
        _currentHtml = "";
    }

    void MdView::_onEnterSpan(MD_SPANTYPE type,void* details,void* userdata)
    {
        std::string tag = md::span_type(type);
        if (_supported_tags.contains(tag))
            _currentHtml += "<" + md::span_type(type) + ">";
    }

    void MdView::_onLeaveSpan(MD_SPANTYPE type,void* details,void* userdata)
    {
        std::string tag = md::span_type(type);
        if (_supported_tags.contains(tag))
            _currentHtml += "</" + md::span_type(type) + ">";
    }

    void MdView::_onText(const std::string& text, void* usderdata)
    {
        if (str::contains(text, "<") || str::contains(text, ">") || str::contains(text, "::"))
            _isText = true;
        _currentHtml += text;
    }

    void MdView::setSelectable(bool sel)
    {
        for (auto c : _body->children())
        {
            ml::Label* l = dynamic_cast<ml::Label*>(c.get());
            if (l)
                l->setSelectable(sel);
        }
    }
}
