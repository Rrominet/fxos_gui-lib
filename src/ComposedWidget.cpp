#include "./ComposedWidget.h"
#include "./Widget.h"

namespace ml
{
    void ComposedWidget::blockEvents()
    {
        for (auto w : _composed)
            std::visit([](auto& w){w->blockEvents();}, w);
    }

    void ComposedWidget::unblockEvents()
    {
        for (auto w : _composed)
            std::visit([](auto& w){w->unblockEvents();}, w);
    }

    void ComposedWidget::setHelp(const std::string& help)
    {
        for (auto w : _composed)
            std::visit([&help](auto& w){w->setHelp(help);}, w);
    }

    void ComposedWidget::removeWindow()
    {
        for (auto w : _composed)
            std::visit([](auto& w){w->removeWindow();}, w);
    }

    void ComposedWidget::unparent()
    {
        for (auto w : _composed)
            std::visit([](auto& w){w->unparent();}, w);
    }
}
