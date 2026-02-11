
#pragma once
#include <cassert>
#include <gtkmm/widget.h>
#include <gtkmm/eventcontrollermotion.h>
#include <gtkmm/eventcontrollerfocus.h>
#include <gtkmm/eventcontrollerscroll.h>
#include <gtkmm/gestureclick.h>
#include <gtkmm/eventcontrollerkey.h>
#include <gtkmm/cssprovider.h>
#include <memory>
#include "../enums.h"
#include "geometry.h"
#include "Ret.h"

namespace ml
{
    class Widget;
    class EventHandle;
    class EventInfos;

    class Widget_impl
    {
        public:
            Widget_impl(Widget* abstract);
            virtual ~Widget_impl() = default;

            std::shared_ptr<Gtk::Widget> widget(){return _gtk;}
            void addCssClass(const std::string& cls){_gtk->add_css_class(cls);}
            void removeCssClass(const std::string& cls){_gtk->remove_css_class(cls);}
            void clearCssClasses(){_gtk->set_css_classes({});}
            void setCssClasses(const std::vector<std::string>& classes);
            bool hadCssClass(const std::string& cls){return _gtk->has_css_class(cls);}

            ml::Ret<> addCss(const std::string& css);
            void addCss(const std::string& attr, const std::string& value);

            virtual void show(){_gtk->show();}
            virtual void hide(){_gtk->hide();}
            bool isVisible(){return _gtk->is_visible();}

            void remove();

            // this function should be called just after the constructor.
            // it create the widget itself (should be overriden in child class)
            virtual void _createWidget(){}

            // this is executes after the widget is parented.
            virtual void setEvents(){}

            virtual void setHAlign(HAlignment align){_gtk->set_halign((Gtk::Align)align);}
            virtual void setVAlign(VAlignment align){_gtk->set_valign((Gtk::Align)align);}

            virtual void setHExpand(bool value=true){_gtk->set_hexpand(value);}
            virtual void setVExpand(bool value=true){_gtk->set_vexpand(value);} //changed

            void setHExpandSet(bool value=true){_gtk->set_hexpand_set(value);}
            void setVExpandSet(bool value=true){_gtk->set_vexpand_set(value);}

            void setHelp(const std::string& help){_gtk->set_tooltip_text(help);}
            std::string help(){return _gtk->get_tooltip_text();}

            void addEventListener(Event event, const std::function<void (EventInfos&)>& callback);

            virtual void setWidth(int w){_gtk->set_size_request(w, -1);}
            virtual void setHeight(int h){_gtk->set_size_request(-1, h);}
            virtual void setSize(int w, int h){_gtk->set_size_request(w, h);}

            int width() const{return _gtk->get_allocated_width();}
            int height() const{return _gtk->get_allocated_height();}

            geometry::Point<double> position() const;

            void setFocusable(bool value){_gtk->set_focusable(value);}
            bool hovered() const{return _hovered;}

            void setCursor(const std::string& name);
            void focus(){_gtk->grab_focus();}

            void _createBasicEvents();

            float fontSize() const;

            void setMargins(int left, int top, int right, int bottom);
            void setMargins(int margin);
            void setLeftMargin(int margin);
            void setTopMargin(int margin);
            void setRightMargin(int margin);
            void setBottomMargin(int margin);

            void redraw() const{_gtk->queue_draw();}

            bool isEditable() const;
            bool focused() const {return _controller_focus->is_focus();}

            //return true is one of its children contains focus too.
            bool containsFocus() const {return _controller_focus->contains_focus();}

        protected : 
            Widget* _abstract = nullptr;
            std::shared_ptr<Gtk::Widget> _gtk;
            sigc::connection _handler;
            Glib::RefPtr<Gtk::CssProvider> _cssProvider = nullptr;
            
            bool _hovered = false;
            double _oldWidth = 0, _oldHeight = 0;

            double _lastX = 0, _lastY = 0;

            Glib::RefPtr<Gtk::EventControllerMotion> _controller_motion = nullptr;
            Glib::RefPtr<Gtk::EventControllerFocus> _controller_focus = nullptr;
            Glib::RefPtr<Gtk::GestureClick> _controller_leftclick = nullptr;
            Glib::RefPtr<Gtk::GestureClick> _controller_rightclick = nullptr;
            Glib::RefPtr<Gtk::GestureClick> _controller_middleclick = nullptr;
            Glib::RefPtr<Gtk::GestureClick> _controller_anyclick = nullptr;
            Glib::RefPtr<Gtk::EventControllerKey> _controller_key = nullptr;

            void _createControllerMotion();
            void _createControllerFocus();
            void _createControllerLeftClick();
            void _createControllerRightClick();
            void _createControllerMiddleClick();
            void _createControllerAnyClick();
            void _createControllerKey();

            bool _setEventInfosMove(Event event, EventInfos& e, double x, double y);
            bool _setEventInfosClick(Event event, EventInfos& e, int numbers, double x, double y);
            void _onMouseAnyClick(Event event, int numbers, double x, double y, const std::function<void (EventInfos&)>& callback);

            virtual void _addOnMouseDown(Event event, const std::function<void (EventInfos&)>& callback);
            virtual void _addOnMouseUp(Event event, const std::function<void (EventInfos&)>& callback);

            virtual void _addOnLeftDown(Event event, const std::function<void (EventInfos&)>& callback);
            virtual void _addOnLeftUp(Event event, const std::function<void (EventInfos&)>& callback);

            virtual void _addOnRightDown(Event event, const std::function<void (EventInfos&)>& callback);
            virtual void _addOnRightUp(Event event, const std::function<void (EventInfos&)>& callback);

            virtual void _addOnMiddleDown(Event event, const std::function<void (EventInfos&)>& callback);
            virtual void _addOnMiddleUp(Event event, const std::function<void (EventInfos&)>& callback);

            virtual void _addOnKeyDown(Event event, const std::function<void (EventInfos&)>& callback);
            virtual void _addOnKeyUp(Event event, const std::function<void (EventInfos&)>& callback);

            virtual void _addOnChange(Event event, const std::function<void (EventInfos&)>& callback){}
            virtual void _addOnValid(Event event, const std::function<void (EventInfos&)>& callback){}

            virtual void _addOnWheel(Event event, const std::function<void (EventInfos&)>& callback);

            virtual void _addOnShown(Event event, const std::function<void (EventInfos&)>& callback);
            virtual void _addOnHidden(Event event, const std::function<void (EventInfos&)>& callback);

            virtual void _addOnResize(Event event, const std::function<void (EventInfos&)>& callback);

            void _createCssProviderIfNeeded();

            std::unordered_map<std::string, std::string>_css;
            std::string _generatedCss() const;
            void _updateCssProvider();
    };
}
