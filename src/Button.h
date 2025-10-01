
#pragma once

#include "./Widget.h"

#ifdef __EMSCRIPTEN__
#include "./em/Button_impl.h"
#else
#include "./gtk/Button_impl.h"
#endif

namespace ml
{
    class Button : public Widget
    {
        public : 
            Button();
            virtual ~Button() = default;

            std::shared_ptr<ml::Button_impl> button(){return std::static_pointer_cast<Button_impl>(_impl);}
            virtual void init() override;

            virtual void setText(const std::string& text) override {this->button()->setText(text);}
            void setValue(const std::string& text){this->button()->setText(text);}
            virtual std::string text() override{return this->button()->text();}
            std::string value(){return this->button()->text();}

            void mkLoading(){this->button()->mkLoading();}
            void stopLoading(){this->button()->stopLoading();}

        public : 
//#include "./Button_gen.h"
    };
}
