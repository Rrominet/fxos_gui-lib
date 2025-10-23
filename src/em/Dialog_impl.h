#include "./Window_impl.h"
#include "../Dialog.h"

namespace ml
{
    class Dialog_impl : public Window_impl
    {
        public:
            Dialog_impl(Dialog* win);
            virtual ~Dialog_impl() = default;
            virtual void _createWindow() override;
    };
}
