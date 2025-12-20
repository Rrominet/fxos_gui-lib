#include "./App.h"
#include "./ChangeChecker.h"
#include "json.h"

namespace ml
{
    ChangeChecker::ChangeChecker(size_t intervalPeriod): _intervalPeriod(intervalPeriod)
    {
        _oninterval = [this] 
        {
            if(!_onchange)
                return;

            _update();
            if (this->changed())
                _onchange();
        };
    }

    //changed
    void ChangeChecker::setOnchange(const std::function<void()>& f)
    {
        _onchange = f;
    }

    void ChangeChecker::_update()
    {
        if (!_getCurrent)
            return;
        _prev = _current;
        _current = _getCurrent();
    }

    bool ChangeChecker::changed() const
    {
        return !ml::json::compare(_prev, _current); 
    }

    bool ChangeChecker::stop()
    {
        if (_intervalid == -1)
        {
            lg("ChangeChecker::stop : not started.");
            return false;
        }

        ml::app()->removeInterval(_intervalid);
        _intervalid = -1;
        return true;
    }

    bool ChangeChecker::start()
    {
        if (_intervalid != -1)
        {
            lg("ChangeChecker::start : already started.");
            return false;
        }
        _intervalid = ml::app()->setInterval(_oninterval, _intervalPeriod);
        return true;
    }
}
