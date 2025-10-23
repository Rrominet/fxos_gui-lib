namespace ml
{
    class EnumProperty : public StringProperty
    {
        public : 
            EnumProperty(const std::string& name, const std::string& value="", const std::string& description ="", ml::Vec<std::string> choices={}) : StringProperty(name, value, description), _choices(choices) {}
            virtual ~EnumProperty() = default;

            // it's a reference so you can modify it like you want.
            ml::Vec<std::string>& choices() {return _choices;}
            void setChoices(const std::vector<std::string>& choices) {_choices = choices; this->notify("choices-changed");}

            virtual bool isEnum() const override {return true;}

        protected : 
            ml::Vec<std::string> _choices;
    };
}
