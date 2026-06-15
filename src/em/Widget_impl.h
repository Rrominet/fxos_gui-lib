#pragma once
#include "./em.h"
#include "../enums.h"
#include <memory>
#include "Ret.h"
#include "vec.h"
#include "../EventInfos.h"

namespace ml { struct EventCallback; }

namespace ml
{
    struct EventCallback
    {
        EventInfos event;
        std::function<void(EventInfos&)> callback;
    };

    class Widget;
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

            ml::Ret<> addCss(const std::string& css);
            void addCss(const std::string& attr, const std::string& value);

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

            void setHtml(const std::string& html);
            void setWordWrap(bool wrap);

            void setTextJustify(HAlignment align);
            void setWrap(bool wrap=true);
            void setSelectable(bool sel=true);

            void setEllipsizeMode(EllipsizeMode mode);
            EllipsizeMode ellipsizeMode() const;

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

            void scrollDown(double amount);
            void scrollUp(double amount);

            void scrollLeft(double amount);
            void scrollRight(double amount);

            void addOnXScroll(const std::function<void(double)>& cb);
            void addOnYScroll(const std::function<void(double)>& cb);

            double scrollX() const;
            double scrollY() const;

            geometry::Point<double> position() const;

            bool isEditable() const;
            bool isOnelineEditable() const;
            bool isMultilineEditable() const;

            bool focused() const;
            bool containsFocus() const;

            void enable();
            void disable();
            bool enabled() const;

            void _createBasicEvents();

            geometry::Point<double> computedPosition(ml::Widget* coordonatesSrc) const;

            void setOverflow(Overflow overflow);

        protected : 
            Widget* _abstract = nullptr;

            void _addMouseEvent(bool clear=true);
            void _addKeyEvent(bool clear=true);
            void _addResizeEvent(bool clear=true);
            void _addGeneralEvent(bool clear=true);

            virtual void _addOnChange(const std::function<void(EventInfos&)>& callback);
            virtual void _addOnLeftUp(const std::function<void(EventInfos&)>& callback);

            // the dom element representing the window
            std::shared_ptr<emval> _dom = nullptr;
            bool _visible = false;
            bool _hovered = false;
            bool _enabled = true;
            bool _wasOneTimeInDom = false;

            double _oldWidth = 0, _oldHeight = 0;

            ml::Vec<EventCallback> _onResize;

            ml::Vec<EventCallback> _onMouseEvent;
            ml::Vec<EventCallback> _onKeyEvent;
            ml::Vec<EventCallback> _onGeneralEvents;

            EllipsizeMode _ellipsizeMpde;

            void _onAppended();
            void _addEventToDOMElement(bool clear=true);

            //really different because managed directly by the cpp NOT the DOM
            //see hide()/show() methods
            ml::Vec<EventCallback> _onShown;
            ml::Vec<EventCallback> _onHidden;
    };
}
