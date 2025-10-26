#pragma once
// base class for all composed widget to obliged some functions to be overridden
//

#include "observers/Observer.h"
#include "./EventInfos.h"
#include "./enums.h"
#include "vec.h"
#include <variant>

namespace ml
{
    class Widget;
    class ComposedWidget : public Observer
    {
        public : 
            ComposedWidget() : Observer() {}
            virtual ~ComposedWidget() {}

            //this should be implemented by passing the call to the widget that receives the events...
            virtual void addEventListener(Event event, const std::function<void(EventInfos&)>& callback);

            virtual void blockEvents();
            virtual void unblockEvents();
            void allowEvents(){this->unblockEvents();}

            virtual void setHelp(const std::string& help);
            virtual void setHAlign(HAlignment align){}
            virtual void setVAlign(VAlignment align){}

            virtual void setHExpand(bool value=true){}
            virtual void setVExpand(bool value=true){}

            const ml::Vec<std::variant<Widget*, ComposedWidget*>>& composed() const{return _composed;}
            ml::Vec<std::variant<Widget*, ComposedWidget*>>& composed() {return _composed;}

            void removeWindow();
            void unparent();
            bool isComposed()const {return true;}

            void show();
            void hide();
            void toggle();

        protected : 
            //only the top hierarchy widgets that compose this widget should be added.
            //do not forget to add any of your created widget to this list
            ml::Vec<std::variant<Widget*, ComposedWidget*>> _composed;
    };
}
