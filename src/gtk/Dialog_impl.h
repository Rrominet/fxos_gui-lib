#include "./Window_impl.h"
#include "../Dialog.h"

namespace ml
{
    class Dialog_impl : public Window_impl
    {
        friend class WindowsFactory;

        public:
            Dialog_impl(Dialog* win);
            virtual ~Dialog_impl() = default;

            virtual void _createWindow() override;

        protected : 
    };
}
