#pragma once
#include "./Window.h"

namespace ml
{
    class Dialog : public Window
    {
        friend class WindowsFactory;
        public:
            Dialog(App* app);
            Dialog(App* app, ml::Window* parent);

            virtual ~Dialog() = default;
            virtual void init() override;
    };
}
