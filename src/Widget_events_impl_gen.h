//This is a generated file, don't change it manually, it will be override when rebuild.


    case(CLICK) :
    {
        _click.push(callback);
        if (!_click_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _click)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _click_initialized = true;
        }
        break;
    }
    
    case(DOUBLE_CLICK) :
    {
        _double_click.push(callback);
        if (!_double_click_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _double_click)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _double_click_initialized = true;
        }
        break;
    }
    
    case(MOUSE_ENTER) :
    {
        _mouse_enter.push(callback);
        if (!_mouse_enter_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _mouse_enter)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _mouse_enter_initialized = true;
        }
        break;
    }
    
    case(MOUSE_LEAVE) :
    {
        _mouse_leave.push(callback);
        if (!_mouse_leave_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _mouse_leave)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _mouse_leave_initialized = true;
        }
        break;
    }
    
    case(MOUSE_MOVE) :
    {
        _mouse_move.push(callback);
        if (!_mouse_move_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _mouse_move)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _mouse_move_initialized = true;
        }
        break;
    }
    
    case(MOUSE_UP) :
    {
        _mouse_up.push(callback);
        if (!_mouse_up_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _mouse_up)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _mouse_up_initialized = true;
        }
        break;
    }
    
    case(MOUSE_DOWN) :
    {
        _mouse_down.push(callback);
        if (!_mouse_down_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _mouse_down)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _mouse_down_initialized = true;
        }
        break;
    }
    
    case(LEFT_UP) :
    {
        _left_up.push(callback);
        if (!_left_up_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _left_up)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _left_up_initialized = true;
        }
        break;
    }
    
    case(LEFT_DOWN) :
    {
        _left_down.push(callback);
        if (!_left_down_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _left_down)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _left_down_initialized = true;
        }
        break;
    }
    
    case(RIGHT_UP) :
    {
        _right_up.push(callback);
        if (!_right_up_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _right_up)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _right_up_initialized = true;
        }
        break;
    }
    
    case(RIGHT_DOWN) :
    {
        _right_down.push(callback);
        if (!_right_down_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _right_down)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _right_down_initialized = true;
        }
        break;
    }
    
    case(MIDDLE_UP) :
    {
        _middle_up.push(callback);
        if (!_middle_up_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _middle_up)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _middle_up_initialized = true;
        }
        break;
    }
    
    case(MIDDLE_DOWN) :
    {
        _middle_down.push(callback);
        if (!_middle_down_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _middle_down)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _middle_down_initialized = true;
        }
        break;
    }
    
    case(KEY_DOWN) :
    {
        _key_down.push(callback);
        if (!_key_down_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _key_down)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _key_down_initialized = true;
        }
        break;
    }
    
    case(KEY_UP) :
    {
        _key_up.push(callback);
        if (!_key_up_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _key_up)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _key_up_initialized = true;
        }
        break;
    }
    
    case(WHEEL) :
    {
        _wheel.push(callback);
        if (!_wheel_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _wheel)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _wheel_initialized = true;
        }
        break;
    }
    
    case(FOCUS) :
    {
        _focus.push(callback);
        if (!_focus_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _focus)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _focus_initialized = true;
        }
        break;
    }
    
    case(UNFOCUS) :
    {
        _unfocus.push(callback);
        if (!_unfocus_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _unfocus)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _unfocus_initialized = true;
        }
        break;
    }
    
    case(CHANGE) :
    {
        _change.push(callback);
        if (!_change_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _change)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _change_initialized = true;
        }
        break;
    }
    
    case(VALID) :
    {
        _valid.push(callback);
        if (!_valid_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _valid)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _valid_initialized = true;
        }
        break;
    }
    
    case(SHOWN) :
    {
        _shown.push(callback);
        if (!_shown_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _shown)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _shown_initialized = true;
        }
        break;
    }
    
    case(HIDDEN) :
    {
        _hidden.push(callback);
        if (!_hidden_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _hidden)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _hidden_initialized = true;
        }
        break;
    }
    
    case(RESIZE) :
    {
        _resize.push(callback);
        if (!_resize_initialized)
        {
            auto cb = [this](EventInfos& e)
            {
                if (!_allowEvents)
                    return;
                if (this->window())
                {
                    e.ctrl = this->window()->state().ctrl;
                    e.shift = this->window()->state().shift;
                    e.alt = this->window()->state().alt;
                    e.super = this->window()->state().meta;
                }
                for (auto& f : _resize)
                    f(e);
            };
            _impl->addEventListener(event, cb);
            _resize_initialized = true;
        }
        break;
    }
    