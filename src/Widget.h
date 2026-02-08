/*
 * This is the baseclass for all widgets of the frameworks (not windows - only their contents)
 * It work really closely to the JS API af a browser specialy from the event listener side.
 * To add an event listener on any widget, do : 
 * widget->addEventListener(ml::Event::YOUR_EVENT, your_callback);
 *
 * You can't create a widget directly, you need to use the create... methods from the Window/Box/Scrollable objects.
 */

#pragma once

#include "debug.h"
#include <cassert>
#include <memory>
#include "./enums.h"
#include "./EventInfos.h"
#include "vec.h"
#include "observers/Observer.h"
#include "geometry.h"
#include "Ret.h"
#ifdef __EMSCRIPTEN__
#include "./em/Widget_impl.h"
#else
#include "./gtk/Widget_impl.h"
#endif

namespace ml
{
    class Window;
    class EventHandle;
    class EventInfos;
    class Widget : public Observer
    {
        friend class WidgetsFactory;

        public : 
            Widget();
            virtual ~Widget();

#ifdef __EMSCRIPTEN__
            std::shared_ptr<emval> dom(){return _impl->widget();}
#else
            std::shared_ptr<Gtk::Widget> gtk(){return _impl->widget();}
#endif

            void addCssClass(const std::string& cls){_impl->addCssClass(cls);}
            void removeCssClass(const std::string& cls){_impl->removeCssClass(cls);}
            void clearCssClasses(){_impl->clearCssClasses();}
            void setCssClasses(const std::vector<std::string>& classes){_impl->setCssClasses(classes);}
            bool hadCssClass(const std::string& cls){return _impl->hadCssClass(cls);}
            ml::Ret<> addCss(const std::string& css){return _impl->addCss(css);}
            void addCss(const std::string& attr, const std::string& value){_impl->addCss(attr, value);}

            virtual void show(){_impl->show();}
            virtual void hide(){_impl->hide();}
            bool isVisible(){return _impl->isVisible();}
            bool visible(){return _impl->isVisible();}
            void setVisible(bool value);

            void remove();

            void toggle();

            bool hasParent(){return _parent != nullptr;}
            ml::Widget* parent(){assert(_parent); return _parent;}
            // canot be used to unparent, use unparent instead to avoid confusion
            void setParent(ml::Widget* w){assert(w); _parent = w;}

            void unparent(){_parent = nullptr;}

            virtual void _createWidget();
            virtual void init() {}

            // this is executes after the widget is parented.
            virtual void setEvents() {_impl->setEvents();}

            virtual void setText(const std::string& text){}
            virtual std::string text(){return "";}

            virtual void setHAlign(HAlignment align){_impl->setHAlign(align);}
            virtual void setVAlign(VAlignment align){_impl->setVAlign(align);}

            virtual void setHExpand(bool value=true){_impl->setHExpand(value);}
            virtual void setVExpand(bool value=true){_impl->setVExpand(value);}

            void setHExpandSet(bool value=true){_impl->setHExpandSet(value);}
            void setVExpandSet(bool value=true){_impl->setVExpandSet(value);}

            bool hasWindow(){return _window != nullptr;}
            ml::Window* window(){assert(_window); return _window;}
            void setWindow(ml::Window* w);
            void removeWindow(){_window = nullptr;}

            virtual void setHelp(const std::string& help){_impl->setHelp(help);}
            std::string help(){return _impl->help();}

            void addEventListener(Event event, const std::function<void(EventInfos&)>& callback);

            //manually trigger an event - useful if you override an event listener that modify the default behavior of the widget
            //it will often be used in couple with blockEvents() and allowEvents()
            void triggerEvent(Event event, EventInfos& infos);

            // you can set any menu id that has been registered with : 
            // ml::app()->menusFactory()->create(...);
            void setContextMenu(const std::string& menuId);

            void blockEvents(){_allowEvents = false;}
            void unblockEvents(){_allowEvents = true;}
            void allowEvents(){_allowEvents = true;}

            void setWidth(int w){_impl->setWidth(w);}
            void setHeight(int h){_impl->setHeight(h);}

            void setSize(int w, int h){_impl->setSize(w, h);}

            int width() const{return _impl->width();}
            int height() const{return _impl->height();}

            //coordonates are relative from it parent.
            //it's not from the window or even from the screen
            geometry::Point<double> position() const {return _impl->position();}
            double x() const {return _impl->position().x;}
            double y() const {return _impl->position().y;}

            double left() const {return _impl->position().x;}
            double top() const {return _impl->position().y;}

            double right() const {return _impl->position().x + this->width();}
            double bottom() const {return _impl->position().y + this->height();}

            void setFocusable(bool value){_impl->setFocusable(value);}
            bool hovered() const{return _impl->hovered();}

            void setCursor(const std::string& name){_impl->setCursor(name);}
            void focus(){_impl->focus();}

            void setMargins(int left, int top, int right, int bottom){_impl->setMargins(left, top, right, bottom);}
            void setMargins(int margin){_impl->setMargins(margin);}
            void setLeftMargin(int margin){_impl->setLeftMargin(margin);}
            void setTopMargin(int margin){_impl->setTopMargin(margin);}
            void setRightMargin(int margin){_impl->setRightMargin(margin);}
            void setBottomMargin(int margin){_impl->setBottomMargin(margin);}

            //careful this value is computed so it could be long to call this repetidly, just cahce it because font size rarely change during the lifetime of a gui program.
            float fontSize() const{return _impl->fontSize();}

            bool isComposed()const {return false;}
            void redraw()const {_impl->redraw();};

            void setDraggable();
            bool isDragging() const;

            //coordonates needs to be relative to its parent
            bool isInside(double x, double y) const;

        protected : 
            std::shared_ptr<Widget_impl> _impl;
            ml::Widget* _parent = nullptr;
            ml::Window* _window = nullptr;

            bool _allowEvents = true;

            bool _dragging = false;
            bool _draggable_setted = false;
            bool _first_drag_event = false;

            ml::Vec<std::function<void(EventInfos&)>> _drag_start;
            ml::Vec<std::function<void(EventInfos&)>> _drag_end;
            ml::Vec<std::function<void(EventInfos&)>> _drag_move;

#include "./Widget_events_gen.h"
    };
}
