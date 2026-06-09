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

    void ComposedWidget::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        for (auto w : _composed)
            std::visit([&event, &callback](auto& w){w->addEventListener(event, callback);}, w);
    }

    void ComposedWidget::show()
    {
        for (auto w : _composed)
            std::visit([](auto& w){w->show();}, w);
    }

    void ComposedWidget::hide()
    {
        for (auto w : _composed)
            std::visit([](auto& w){w->hide();}, w);	
    }

    void ComposedWidget::toggle()
    {
        for (auto w : _composed)
            std::visit([](auto& w){w->toggle();}, w);	
    }

    void ComposedWidget::setHAlign(HAlignment align)
    {
        for (auto w : _composed)        
            std::visit([align](auto& w){w->setHAlign(align);}, w);
    }

    void ComposedWidget::setVAlign(VAlignment align)
    {
        for (auto w : _composed)        
            std::visit([align](auto& w){w->setVAlign(align);}, w);
    }

    void ComposedWidget::setHExpand(bool value)
    {
        for (auto w : _composed)        
            std::visit([value](auto& w){w->setHExpand(value);}, w);
    }

    void ComposedWidget::setVExpand(bool value)
    {
        for (auto w : _composed)        
            std::visit([value](auto& w){w->setVExpand(value);}, w);
    }

    void ComposedWidget::enable()
    {
        for (auto w : _composed)
            std::visit([](auto& w){w->enable();}, w);	
    }

    void ComposedWidget::disable()
    {
        for (auto w : _composed)
            std::visit([](auto& w){w->disable();}, w);	
    }
}
