//This is a generated file, don't change it manually, it will be override when rebuild.


        void BoolProperty::setMin(bool min, Observer* observer)
        {
            _min = min; 
            this->notify("min", std::any(_min), observer);
        }

        void BoolProperty::setMax(bool max, Observer* observer)
        {
            _max = max; 
            this->notify("max", std::any(_max), observer);
        }
    

        void IntProperty::setMin(int min, Observer* observer)
        {
            _min = min; 
            this->notify("min", std::any(_min), observer);
        }

        void IntProperty::setMax(int max, Observer* observer)
        {
            _max = max; 
            this->notify("max", std::any(_max), observer);
        }
    

        void FloatProperty::setMin(float min, Observer* observer)
        {
            _min = min; 
            this->notify("min", std::any(_min), observer);
        }

        void FloatProperty::setMax(float max, Observer* observer)
        {
            _max = max; 
            this->notify("max", std::any(_max), observer);
        }
    

        void DoubleProperty::setMin(double min, Observer* observer)
        {
            _min = min; 
            this->notify("min", std::any(_min), observer);
        }

        void DoubleProperty::setMax(double max, Observer* observer)
        {
            _max = max; 
            this->notify("max", std::any(_max), observer);
        }
    

    
