#pragma once

// an object that call blockEvent on constructor and allowEvent on its destructor
// works like a lock_guard for a mutex
//

namespace ml
{
    template <typename W>
    class EventBlocker
    {
    public:
        EventBlocker(W* w) : _w(w)
        {
            _w->blockEvents();
        }
        ~EventBlocker()
        {
            _w->allowEvents();
        }
    private:
        W* _w;
    };
}
