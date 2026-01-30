
#pragma once
#include "./em.h"
#include <memory>

namespace ml
{
    class Widget;
    class EventInfos;
    class Widget_impl
    {
        public:
            Widget_impl(Widget* win);
            virtual ~Widget_impl() = default;

            std::shared_ptr<emval> widget(){assert(_dom); return _dom;}

            void addCssClass(const std::string& cls);
            void removeCssClass(const std::string& cls);

            void clearCssClasses();
            void setCssClasses(const std::vector<std::string>& classes);
            bool hadCssClass(const std::string& cls);

            void addCss(const std::string& css);

            virtual void show();
            virtual void hide();
            bool isVisible();

            void remove();

            virtual void setHAlign(HAlignment align);
            virtual void setVAlign(VAlignment align);

            virtual void setHExpand(bool value=true);
            virtual void setVExpand(bool value=true);

            void setHExpandSet(bool value=true){}
            void setVExpandSet(bool value=true){}

            // this function should be called just after the constructor.
            // it create the widget itself (should be overriden in shild class)
            virtual void _createWidget(){}

            // this is executes after the widget is parented.
            virtual void setEvents(){}

            virtual void setText(const std::string& text);
            virtual std::string text();

            virtual void setHelp(const std::string& help);
            virtual std::string help();

            void addEventListener(Event event, const std::function<void(EventInfos&)>& callback);

            virtual void setWidth(int w);
            virtual void setHeight(int h);
            virtual void setSize(int w, int h);

            int width() const;
            int height() const;

            void setFocusable(bool value);
            bool hovered() const;

            void setCursor(const std::string& name);
            void focus();

            void setMargins(int left, int top, int right, int bottom);
            void setMargins(int margin);
            void setLeftMargin(int margin);
            void setTopMargin(int margin);
            void setRightMargin(int margin);
            void setBottomMargin(int margin);

            void redraw() const;

            float fontSize() const;

        protected : 
            Widget* _abstract = nullptr;

            // the dom element representing the window
            std::shared_ptr<emval> _dom = nullptr;
            bool _visible = false;

            virtual void _addOnLeftUp(Event event, const std::function<void(EventInfos&)>& callback);
            virtual void _addOnChange(Event event, const std::function<void(EventInfos&)>& callback);
    };
}
