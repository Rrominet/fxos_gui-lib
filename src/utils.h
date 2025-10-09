#pragma once
#include "./Box.h"
#include "./Label.h"

// some useful function to create premade group of widgets on any container.
namespace ml
{
    struct LabelValue
    {
        Box* container = nullptr;
        Label* label = nullptr;
        Label* value = nullptr;
    };

    template<typename C=Box>
        LabelValue labelValue(C* parent, const std::string& label, const std::string& value="")
        {
            auto c = parent->createBox();
            c->addCssClass("label-value-container");
            c->setOrient(ml::HORIZONTAL);
            c->setHExpand();
            auto lbl = c->createLabel(label + " : ");
            lbl->addCssClass("label");
            lbl->setHAlign(ml::LEFT);
            lbl->setHExpand(false);
            auto val = c->createLabel(value);
            val->addCssClass("value");
            val->setHAlign(ml::RIGHT);
            lbl->setHExpand(true);

            return {c.get(), lbl.get(), val.get()};
        }
}
