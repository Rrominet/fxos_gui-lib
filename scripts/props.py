# careful if you add type here, ypu should add them in the PropertyType Enum too (see Property.h)
number_types = (
    "bool",
    "int",
    "float",
    "double",
        )

other_types = (
        "std::string",
        )

def replacedTypes(c, type) : 
    c = c.replace("*type*", type)

    if "::" in type : 
        type = type.split("::")[1]
    cap = type.capitalize()
    c = c.replace("*Type*", cap)
    c = c.replace("*TYPE*", cap.upper())
    return c

def numbers_h(type) : 
    c = """
    class *Type*Property : public Property
    {
        public : 
            *Type*Property(const std::string& name, *type* value=0, *type* min=-10000000, *type* max=1000000, const std::string& description = "") : Property(name, description, value), _min(min), _max(max){}
            virtual ~*Type*Property() = default;

            // the observer arg is really important if you call that from a class that is an observer of this property (like a widget representing it for example)
            void setMin(*type* min, Observer* observer = nullptr);
            void setMax(*type* max, Observer* observer = nullptr);

            *type* value(){return std::any_cast<*type*>(_value);}
            virtual double min() override {return _min;}
            virtual double max() override {return _max;}

            virtual PropertyType type() const override {return *TYPE*;}

        protected : 
            double _min;
            double _max;
    };

    """

    return replacedTypes(c, type)

def numbers_cpp(type) : 
    c = """
        void *Type*Property::setMin(*type* min, Observer* observer)
        {
            _min = min; 
            this->notify("min", std::any(_min), observer);
        }

        void *Type*Property::setMax(*type* max, Observer* observer)
        {
            _max = max; 
            this->notify("max", std::any(_max), observer);
        }
    """

    return replacedTypes(c, type)

def others_h(type) : 
    c = """
    class *Type*Property : public Property
    {
        public : 
            *Type*Property(const std::string& name, const *type*& value="", const std::string& description = "") : Property(name, description, value){}
            virtual ~*Type*Property() = default;

            // the observer arg is really important if you call that from a class that is an observer of this property (like a widget representing it for example)
            *type* value(){return std::any_cast<*type*>(_value);}

            virtual PropertyType type() const override {return *TYPE*;}

        protected : 
    };

    """
    return replacedTypes(c, type)

def others_cpp(type) : 
    c = """
    """

    return replacedTypes(c, type)

def props() : 
    _r = {}
    h = ""
    cpp = ""

    for i in number_types :
        h += numbers_h(i) + "\n"
        cpp += numbers_cpp(i) + "\n"

    for i in other_types :
        h += others_h(i) + "\n"
        cpp += others_cpp(i) + "\n"

    _r["h"] = h
    _r["cpp"] = cpp
    return _r
