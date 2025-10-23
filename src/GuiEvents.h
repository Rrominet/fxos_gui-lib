#pragma once
#include "Events.h"
// exactly the same as Events the callbacks are always called on the same thread as the gui of App

namespace ml
{
    class App;
    class GuiEvents : public Events
    {
        public:
            GuiEvents(ml::App* app) : _app(app){}
            virtual ~GuiEvents() {}

            virtual void emit(const std::string &type, std::string data) override;
            virtual void emit(const std::string &type, const std::any& data=0) override;

        private : 
            ml::App* _app = nullptr;
    };
}
