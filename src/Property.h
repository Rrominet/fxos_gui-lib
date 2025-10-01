#pragma once
#include <string>
#include <any>
#include <functional>
#include "vec.h"
#include "observers/Observed.h"

namespace ml
{
    class Box;
    // Do NOT create the Property directly, use the create method of the PropertiesManager instead in ml::app()
    class Property : public Observed
    {
        public : 
            Property(const std::string& name, const std::string& description, const std::any value) : Observed(), _name(name), _description(description), _value(value) {}
            virtual ~Property() {}

            enum PropertyType
            {
                NONE = 0,
                BOOL,
                INT,
                FLOAT,
                DOUBLE,
                STRING,
                IMG,
            };
            
            virtual PropertyType type() const { return NONE;}

            void set(const std::any& value, Observer* observer = nullptr);
            virtual double min(){return 0;}
            virtual double max(){return 0;}

            virtual double step(){return 1;}
            std::any asAny()const {return _value;}

            virtual void addOnUpdate(const std::function<void()> f){_onUpdate.push(f);}

            // typically when the user press return on his keyboard
            virtual void addOnValid(const std::function<void()> f){_onValid.push(f);}

            bool isANumber() const{return type() == INT || type() == FLOAT || type() == DOUBLE;}

            //hide/show all the widget connected to this property
            void hide();
            void show();

            bool visible() const;

            void update(){_onUpdate.exec();}
            void valid(){_onValid.exec();}

        protected : 
            std::string _name;//bp cgs
            std::string _description;//bp cgs
            std::any _value;
            bool _visible = true;

            ml::Vec<std::function<void()>> _onUpdate; //bp cg
            ml::Vec<std::function<void()>> _onValid; //bp cg
            
            ml::Vec<std::shared_ptr<Box>> _widgetsConnected; //bp cg

        public : 
#include "./Property_gen.h"
    };

#include "./props_gen.h"
}

// this should only be included here, and the Property.h included anywhere its needed.
#include "./EnumProperty.h" 
