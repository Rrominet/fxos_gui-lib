#pragma once
#define ENTRY_GET_SET(entryVar)                                       \
    std::string value() { return this->entryVar()->value(); }                  \
    virtual std::any valueAsAny() override { return this->value(); }                  \
    std::string text() override { return this->entryVar()->value(); }          \
                                                                               \
    virtual void setValue(const std::string& value)override { this->entryVar()->setValue(value); }  \
    virtual void setValue(double value)override {this->setValue(std::to_string(value));}  \
    void setText(const std::string& text) override { this->entryVar()->setValue(text); }\
    virtual void setHelp(const std::string& help) override {Widget::setHelp(help); this->entryVar()->setPlaceholder(help);}\
    std::string placeholder(){return this->entryVar()->placeholder();}\

#define ENTRY_GET_SET_GTK(entryVar, type)                                       \
    type value(){return entryVar()->get_text();}\
    void setValue(const type& value){entryVar()->set_text(value);}\

#define ENTRY_GET_SET_EM(type)                                       \
    type value(){return (*_dom)["value"].as<type>();}\
    void setValue(const type& value){_dom->set("value", value);}\
    std::string placeholder(){return (*_dom)["placeholder"].as<std::string>();}\
    void setPlaceholder(const std::string& placeholder){_dom->set("placeholder", placeholder);}\

#define NB_ENTRY_GET_SET(entryVar)                                       \
    double value() { return this->entryVar()->value(); }                  \
    virtual std::any valueAsAny() override { return this->value(); }                  \
    virtual void setValue(double value)override { this->entryVar()->setValue(value); }  \
    virtual void setValue(const std::string& value)override {this->setValue(std::stod(value));}  \
    virtual void setRange(double min, double max)override {this->entryVar()->setRange(min, max);}\
    unsigned int precision(){return this->entryVar()->precision();}\
    virtual void setPrecision(unsigned int precision)override {this->entryVar()->setPrecision(precision);}\
    double step(){return this->entryVar()->step();}\
    virtual void setStep(double step) override {this->entryVar()->setStep(step);}

#define NB_ENTRY_GET_SET_GTK(entryVar, type)                                       \
    type value(){return entryVar()->get_value();}\
    void setValue(const type& value){entryVar()->set_value(value);}\
    void setRange(double min, double max){this->entryVar()->set_range(min, max);}\
    unsigned int precision(){return this->entryVar()->get_digits();}\
    void setPrecision(unsigned int precision){this->entryVar()->set_digits(precision);}\
    double step(){return this->entryVar()->get_adjustment()->get_step_increment();}\
    void setStep(double step){this->entryVar()->get_adjustment()->set_step_increment(step);}\

#define NB_ENTRY_GET_SET_EM(type)\
    type value(){return (*_dom)["value"].as<type>();}\
    void setValue(const type& value){_dom->set("value", value);}\
    void setRange(double min, double max){\
        _dom->set("min", min);\
        _dom->set("max", max);\
    }\
    unsigned int precision(){\
        auto step = this->step();\
        auto precision = 0;\
        while(step < 1){\
            step *= 10;\
            precision++;\
        }\
        return precision;\
    }\
    void setPrecision(unsigned int precision){this->setStep((double(1)/(precision + 1)));}\
    double step(){return (*_dom)["step"].as<double>();}\
    void setStep(double step){_dom->set("step", step);}\
    std::string placeholder(){return (*_dom)["placeholder"].as<std::string>();}\
    void setPlaceholder(const std::string& placeholder){_dom->set("placeholder", placeholder);}\

