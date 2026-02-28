#pragma once
#include <string>
#include <any>
#include <functional>
#include "vec.h"
#include "observers/Observed.h"
#include <unordered_map>
#include "Date.h"

//TODO : add the Color Property

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

            void set(const std::any& value, Observer* observer = nullptr, bool preventUpdate = false);
            virtual double min(){return 0;}
            virtual double max(){return 0;}

            virtual double step(){return 1;}
            std::any asAny()const {return _value;}
            int asInt() const {return std::any_cast<int>(_value);};
            float asFloat() const {return std::any_cast<float>(_value);};
            double asDouble() const {return std::any_cast<double>(_value);};
            bool asBool() const {return std::any_cast<bool>(_value);};
            std::string asString() const {return std::any_cast<std::string>(_value);};

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

            virtual bool isEnum() const {return false;}
            virtual bool isColor() const {return false;}

            bool hasAttribute(const std::string& name){return _attrs.find(name) != _attrs.end();}
            std::any& attribute(const std::string& name){return _attrs.at(name);}
            const std::any& attribute(const std::string& name)const {return _attrs.at(name);}
            void addAttribute(const std::string& name, const std::any& value){_attrs[name] = value;}
            void setAttribute(const std::string& name, const std::any& value){_attrs[name] = value;}
            void removeAttribute(const std::string& name){if(_attrs.find(name) != _attrs.end()) _attrs.erase(name);};

            ml::Date asDate() const;

        protected : 
            std::string _name;//bp cgs
            std::string _description;//bp cgs
            std::any _value;
            bool _visible = true;

            ml::Vec<std::function<void()>> _onUpdate; //bp cg
            ml::Vec<std::function<void()>> _onValid; //bp cg
            
            ml::Vec<std::shared_ptr<Box>> _widgetsConnected; //bp cg

            //can be used to store basically anything you want.
            std::unordered_map<std::string, std::any> _attrs; //bp cg

        public : 
#include "./Property_gen.h"
    };

#include "./props_gen.h"
}

// this should only be included here, and the Property.h included anywhere its needed.
#include "./EnumProperty.h" 
#include "./ColorProperty.h" 
