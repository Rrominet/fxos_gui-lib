//This is a generated file, don't change it manually, it will be override when rebuild.


    class BoolProperty : public Property
    {
        public : 
            BoolProperty(const std::string& name, bool value=0, bool min=-10000000, bool max=1000000, const std::string& description = "") : Property(name, description, value), _min(min), _max(max){}
            virtual ~BoolProperty() = default;

            // the observer arg is really important if you call that from a class that is an observer of this property (like a widget representing it for example)
            void setMin(bool min, Observer* observer = nullptr);
            void setMax(bool max, Observer* observer = nullptr);

            bool value(){return std::any_cast<bool>(_value);}
            virtual double min() override {return _min;}
            virtual double max() override {return _max;}

            virtual PropertyType type() const override {return BOOL;}

        protected : 
            double _min;
            double _max;
    };

    

    class IntProperty : public Property
    {
        public : 
            IntProperty(const std::string& name, int value=0, int min=-10000000, int max=1000000, const std::string& description = "") : Property(name, description, value), _min(min), _max(max){}
            virtual ~IntProperty() = default;

            // the observer arg is really important if you call that from a class that is an observer of this property (like a widget representing it for example)
            void setMin(int min, Observer* observer = nullptr);
            void setMax(int max, Observer* observer = nullptr);

            int value(){return std::any_cast<int>(_value);}
            virtual double min() override {return _min;}
            virtual double max() override {return _max;}

            virtual PropertyType type() const override {return INT;}

        protected : 
            double _min;
            double _max;
    };

    

    class FloatProperty : public Property
    {
        public : 
            FloatProperty(const std::string& name, float value=0, float min=-10000000, float max=1000000, const std::string& description = "") : Property(name, description, value), _min(min), _max(max){}
            virtual ~FloatProperty() = default;

            // the observer arg is really important if you call that from a class that is an observer of this property (like a widget representing it for example)
            void setMin(float min, Observer* observer = nullptr);
            void setMax(float max, Observer* observer = nullptr);

            float value(){return std::any_cast<float>(_value);}
            virtual double min() override {return _min;}
            virtual double max() override {return _max;}

            virtual PropertyType type() const override {return FLOAT;}

        protected : 
            double _min;
            double _max;
    };

    

    class DoubleProperty : public Property
    {
        public : 
            DoubleProperty(const std::string& name, double value=0, double min=-10000000, double max=1000000, const std::string& description = "") : Property(name, description, value), _min(min), _max(max){}
            virtual ~DoubleProperty() = default;

            // the observer arg is really important if you call that from a class that is an observer of this property (like a widget representing it for example)
            void setMin(double min, Observer* observer = nullptr);
            void setMax(double max, Observer* observer = nullptr);

            double value(){return std::any_cast<double>(_value);}
            virtual double min() override {return _min;}
            virtual double max() override {return _max;}

            virtual PropertyType type() const override {return DOUBLE;}

        protected : 
            double _min;
            double _max;
    };

    

    class StringProperty : public Property
    {
        public : 
            StringProperty(const std::string& name, const std::string& value="", const std::string& description = "") : Property(name, description, value){}
            virtual ~StringProperty() = default;

            // the observer arg is really important if you call that from a class that is an observer of this property (like a widget representing it for example)
            std::string value(){return std::any_cast<std::string>(_value);}

            virtual PropertyType type() const override {return STRING;}

        protected : 
    };

    
