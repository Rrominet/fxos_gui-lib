
#include "./Widget_impl.h"
#include "../Widget.h"
#include "../EventInfos.h"
#include "./events_utils.h"
#include <gtkmm/box.h>
#include <gtkmm/layoutmanager.h>
#include "../Window.h"
#include <gtkmm/editable.h>
#include <gtkmm/eventcontroller.h>
#include <gtkmm/textview.h>
#include "../App.h"

namespace ml
{
    Widget_impl::Widget_impl(Widget* abstract) : _abstract(abstract)
    {
    }

    void Widget_impl::remove()
    {
        auto parent = _gtk->get_parent();
        if (!parent)
            return;

        Gtk::Box* parentAsBox = dynamic_cast<Gtk::Box*>(parent);
        if (parentAsBox)
            parentAsBox->remove(*_gtk);
        else
            _gtk->unparent();
    }

    void Widget_impl::addEventListener(Event event, const std::function<void (EventInfos&)>& callback)
    {
        assert(_gtk && "AddEventListener, Gtk Widget not created.");
        switch (event)
        {
            case MOUSE_ENTER:
                {
                    _createControllerMotion();
                    auto f = [callback, event](double x, double y)
                    {
                        EventInfos e;
                        e.type = event;
                        e.x = x;
                        e.y = y;
                        callback(e);
                    };
                    _controller_motion->signal_enter().connect(f);
                    break;
                }

            case MOUSE_LEAVE:
                {
                    _createControllerMotion();
                    auto f = [callback, event]()
                    {
                        EventInfos e;
                        e.type = event;
                        callback(e);
                    };
                    _controller_motion->signal_leave().connect(f);
                    break;
                }
            case MOUSE_MOVE:
                {
                    _createControllerMotion();
                    auto f = [this, callback, event](double x, double y)
                    {
                        EventInfos e;
                        e.type = event;
                        if (_setEventInfosMove(event, e, x, y))
                            callback(e);
                        _lastX = x;
                        _lastY = y;
                    };
                    _controller_motion->signal_motion().connect(f);
                    break;
                }
            case MOUSE_UP:
                    _addOnMouseUp(event, callback);
                    break;
            case MOUSE_DOWN:
                    _addOnMouseDown(event, callback);
                    break;
            case LEFT_UP:
                    _addOnLeftUp(event, callback);
                    break;
            case LEFT_DOWN:
                    _addOnLeftDown(event, callback);
                    break;
            case RIGHT_UP:
                    _addOnRightUp(event, callback);
                    break;
            case RIGHT_DOWN:
                    _addOnRightDown(event, callback);
                    break;
            case MIDDLE_UP:
                    _addOnMiddleUp(event, callback);
                    break;
            case MIDDLE_DOWN:
                    _addOnMiddleDown(event, callback);
                    break;
            case KEY_DOWN:
                    _addOnKeyDown(event, callback);
                    break;
            case KEY_UP:
                    _addOnKeyUp(event, callback);
                    break;
            case FOCUS:
                {
                    _createControllerFocus();
                    auto f = [callback, event]()
                    {
                        EventInfos e;
                        e.type = event;
                        callback(e);
                    };
                    _controller_focus->signal_enter().connect(f);
                    break;
                }
            case UNFOCUS:
                {
                    _createControllerFocus();
                    auto f = [callback, event]()
                    {
                        EventInfos e;
                        e.type = event;
                        callback(e);
                    };
                    _controller_focus->signal_leave().connect(f);
                    break;
                }

            case CHANGE: 
                _addOnChange(event, callback);
                break;

            case VALID:
                _addOnValid(event, callback);
                break;

            case WHEEL:
                _addOnWheel(event, callback);
                break;

            case SHOWN : 
                _addOnShown(event, callback);
                break;

            case HIDDEN : 
                _addOnHidden(event, callback);
                break;

            case RESIZE : 
                _addOnResize(event, callback);
                break;

            default:
                break;
        }
    }

    void Widget_impl::_createControllerMotion()
    {
        if (!_controller_motion)
        {
            _controller_motion = Gtk::EventControllerMotion::create();
            _gtk->add_controller(_controller_motion);
        }
    }

    void Widget_impl::_createControllerFocus()
    {
        if (!_controller_focus)
        {
            _controller_focus = Gtk::EventControllerFocus::create();
            _gtk->add_controller(_controller_focus);
        }
    }

    void Widget_impl::_createControllerLeftClick()
    {
        if (!_controller_leftclick)
        {
            _controller_leftclick = Gtk::GestureClick::create();
            _controller_leftclick->set_button(1);
            _gtk->add_controller(_controller_leftclick);
        }
    }

    void Widget_impl::_createControllerRightClick()
    {
        if (!_controller_rightclick)
        {
            _controller_rightclick = Gtk::GestureClick::create();
            _controller_rightclick->set_button(3);
            _gtk->add_controller(_controller_rightclick);
        }
    }

    void Widget_impl::_createControllerMiddleClick()
    {
        if (!_controller_middleclick)
        {
            _controller_middleclick = Gtk::GestureClick::create();
            _controller_middleclick->set_button(2); 
            _gtk->add_controller(_controller_middleclick);
        }
    }

    void Widget_impl::_createControllerAnyClick()
    {
        if (!_controller_anyclick)
        {
            _controller_anyclick = Gtk::GestureClick::create();
            _controller_anyclick->set_button(0);
            _gtk->add_controller(_controller_anyclick);
        }
    }

    void Widget_impl::_createControllerKey()
    {
        if (!_controller_key)
        {
            _controller_key = Gtk::EventControllerKey::create();
            _controller_key->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
            _gtk->add_controller(_controller_key);
        }
    }

#define SET_MOUSE_EVENT \
        e.type = event; \
        e.x = x; \
        e.y = y; \
        e.mvtx = e.x - _lastX; \
        e.mvty = e.y - _lastY; \

    bool Widget_impl::_setEventInfosClick(Event event, EventInfos& e, int numbers, double x, double y)
    {
        SET_MOUSE_EVENT
        e.click_numbers = numbers;
        return !ml::app()->stopEventPropagationMap()[event];
    }

    bool Widget_impl::_setEventInfosMove(Event event, EventInfos& e, double x,double y)
    {
        SET_MOUSE_EVENT
        return !ml::app()->stopEventPropagationMap()[event];
    }

    void Widget_impl::_onMouseAnyClick(Event event, int numbers, double x, double y, const std::function<void (EventInfos&)>& callback)
    {
        EventInfos e;
        if (_setEventInfosClick(event, e, numbers, x, y))
            callback(e);
        _lastX = x;
        _lastY = y;
    }

    void Widget_impl::_addOnMouseDown(Event event, const std::function<void (EventInfos&)>& callback)
    {
        _createControllerAnyClick();
        auto f = [callback, this, event](int numbers, double x, double y)
        {
            _onMouseAnyClick(event, numbers, x, y, callback);
        };
        _controller_anyclick->signal_pressed().connect(f);
    }

    void Widget_impl::_addOnMouseUp(Event event, const std::function<void (EventInfos&)>& callback)
    {
        _createControllerAnyClick();
        auto f = [callback, this, event](int numbers, double x, double y)
        {
            _onMouseAnyClick(event, numbers, x, y, callback);
        };
        _controller_anyclick->signal_released().connect(f);
    }

    void Widget_impl::_addOnLeftDown(Event event, const std::function<void (EventInfos&)>& callback)
    {
        _createControllerLeftClick();
        auto f = [callback, this, event](int numbers, double x, double y)
        {
            _onMouseAnyClick(event, numbers, x, y, callback);
        };
        _controller_leftclick->signal_pressed().connect(f);
    }

    void Widget_impl::_addOnLeftUp(Event event, const std::function<void (EventInfos&)>& callback)
    {
        _createControllerLeftClick();
        auto f = [callback, this, event](int numbers, double x, double y)
        {
            _onMouseAnyClick(event, numbers, x, y, callback);
        };
        _controller_leftclick->signal_released().connect(f);
    }

    void Widget_impl::_addOnRightDown(Event event, const std::function<void (EventInfos&)>& callback)
    {
        _createControllerRightClick();
        auto f = [callback, this, event](int numbers, double x, double y)
        {
            _onMouseAnyClick(event, numbers, x, y, callback);
        };
        _controller_rightclick->signal_pressed().connect(f);
    }

    void Widget_impl::_addOnRightUp(Event event, const std::function<void (EventInfos&)>& callback)
    {
        _createControllerRightClick();
        auto f = [callback, this, event](int numbers, double x, double y)
        {
            _onMouseAnyClick(event, numbers, x, y, callback);
        };
        _controller_rightclick->signal_released().connect(f);
    }

    void Widget_impl::_addOnMiddleDown(Event event, const std::function<void (EventInfos&)>& callback)
    {
        _createControllerMiddleClick();
        auto f = [callback, this, event](int numbers, double x, double y)
        {
            _onMouseAnyClick(event, numbers, x, y, callback);
        };
        _controller_middleclick->signal_pressed().connect(f);
    }

    void Widget_impl::_addOnMiddleUp(Event event, const std::function<void (EventInfos&)>& callback)
    {
        _createControllerMiddleClick();
        auto f = [callback, this, event](int numbers, double x, double y)
        {
            _onMouseAnyClick(event, numbers, x, y, callback);
        };
        _controller_middleclick->signal_released().connect(f);
    }

#define SET_KEY_EVENT \
            EventInfos e; \
            e.type = event; \
            e.keyval = keyval; \
            e.keycode = keycode; \
            gtk::setModifiersOnEventInfos(state, e); \
            e.key = gdk_keyval_name(keyval); \

    void Widget_impl::_addOnKeyDown(Event event, const std::function<void (EventInfos&)>& callback)
    {
        _createControllerKey();
        auto f = [callback, event](guint keyval, guint keycode, Gdk::ModifierType state)
        {
            SET_KEY_EVENT
            if (!ml::app()->stopEventPropagationMap()[event])
            {
                callback(e); 
                return e.preventDefault;
            }
            return false;
        };
        _controller_key->signal_key_pressed().connect(f, true);
    }

    void Widget_impl::_addOnKeyUp(Event event, const std::function<void (EventInfos&)>& callback)
    {
        _createControllerKey();
        auto f = [callback, event](guint keyval, guint keycode, Gdk::ModifierType state)
        {
            SET_KEY_EVENT
            if (!ml::app()->stopEventPropagationMap()[event])
                callback(e); 
        };
        _controller_key->signal_key_released().connect(f);
    }

    void Widget_impl::_createBasicEvents()
    {
        lg("GTK : Widget_impl::createBasicEvents()");
        _createControllerFocus();
        this->addEventListener(MOUSE_ENTER, [this](EventInfos&){_hovered=true;});
        this->addEventListener(MOUSE_LEAVE, [this](EventInfos&){_hovered=false;});
        lg("GTK : Widget_impl::createBasicEvents() done");
    }

    void Widget_impl::_addOnWheel(Event event, const std::function<void (EventInfos&)>& callback)
    {
        auto window = _abstract->window()->impl();
        auto f = [callback, this, event](EventInfos& e)
        {
            e.type = event;
            if (this->hovered() && callback && !ml::app()->stopEventPropagationMap()[event])
                callback(e); 
        };

        window->addWheelEventListener(f);
    }

    void Widget_impl::_addOnShown(Event event, const std::function<void (EventInfos&)>& callback)
    {
        lg("Adding a function on shown");
        _gtk->signal_show().connect([callback, event]
        {
            lg("GTKWidget shown");
            EventInfos e;
            e.type = event;
            e.visible = true;
            callback(e);
        });

        _gtk->signal_map().connect([callback, event]
        {
            lg("GTKWidget shown");
            EventInfos e;
            e.type = event;
            e.visible = true;
            callback(e);
        });
    }

    void Widget_impl::_addOnHidden(Event event, const std::function<void (EventInfos&)>& callback)
    {
        _gtk->signal_hide().connect([callback, event]
        {
        lg("GTKWidget hidden");
            EventInfos e;
            e.type = event;
            e.visible = false;
            callback(e);
        });

        _gtk->signal_unmap().connect([callback, event]
        {
            lg("GTKWidget hidden");
            EventInfos e;
            e.type = event;
            e.visible = false;
            callback(e);
        });
    }

    void Widget_impl::_addOnResize(Event event, const std::function<void (EventInfos&)>& callback)
    {
            _gtk->add_tick_callback([this,callback, event](const Glib::RefPtr<Gdk::FrameClock>&){
                EventInfos e; 
                e.type = event;
                e.width = _gtk->get_width();
                e.height = _gtk->get_height();
                if (_oldWidth == e.width && _oldHeight == e.height)
                    return true;

                e.visible = _gtk->is_visible();
                callback(e);
                _oldWidth = e.width;
                _oldHeight = e.height;
                return true;
            });
    }

    void Widget_impl::setCursor(const std::string& name)
    {
        auto cursor = Gdk::Cursor::create(name);
        _gtk->set_cursor(cursor);
    }

    float Widget_impl::fontSize() const
    {
        auto ctx = _gtk->get_pango_context();
        auto font_desc = ctx->get_font_description();
        double sz = font_desc.get_size();
        float _r;

        if (!font_desc.get_size_is_absolute())
            _r = sz;
        else
            _r = sz / PANGO_SCALE;

        return _r;
    }

    void Widget_impl::setMargins(int left,int top,int right,int bottom)
    {
        _gtk->set_margin_start(left);
        _gtk->set_margin_end(right);
        _gtk->set_margin_top(top);
        _gtk->set_margin_bottom(bottom);
    }

    void Widget_impl::setMargins(int margin)
    {
        _gtk->set_margin_start(margin);
        _gtk->set_margin_end(margin);
        _gtk->set_margin_top(margin);
        _gtk->set_margin_bottom(margin);
    }

    void Widget_impl::setLeftMargin(int margin)
    {
        _gtk->set_margin_start(margin);
    }

    void Widget_impl::setTopMargin(int margin)
    {
        _gtk->set_margin_top(margin);
    }

    void Widget_impl::setRightMargin(int margin)
    {
        _gtk->set_margin_end(margin);
    }

    void Widget_impl::setBottomMargin(int margin)
    {
        _gtk->set_margin_bottom(margin);
    }

    void Widget_impl::_createCssProviderIfNeeded()
    {
        if (!_cssProvider)        
        {
            _cssProvider = Gtk::CssProvider::create();
            _gtk->get_style_context()->add_provider(_cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
    }

    std::string Widget_impl::_generatedCss() const
    {
        std::string res; 
        for (auto& c : _css)
            res += c.first + ":" + c.second + ";";
        return res;
    }

    void Widget_impl::_updateCssProvider()
    {
        std::string gcss = "*{" + _generatedCss() + ";}";
        _cssProvider->load_from_string(gcss);
    }

    ml::Ret<> Widget_impl::addCss(const std::string& css)
    {
        _createCssProviderIfNeeded();
        auto tmp = str::split(css,":");
        if (tmp.size() != 2)
            return ml::ret::fail("Invalid css given, couldn't split by ':'. Given : " + css);

        _css[tmp[0]] = tmp[1];
        _updateCssProvider();
        return ml::ret::success();
    }

    void Widget_impl::addCss(const std::string& attr,const std::string& value)
    {
        _createCssProviderIfNeeded();
        _css[attr] = value;
        _updateCssProvider();
    }

    void Widget_impl::setCssClasses(const std::vector<std::string>& classes)
    {
        std::vector<Glib::ustring> vec;        
        vec.reserve(classes.size());
        for (int i=0; i<classes.size(); i++)
            vec.push_back(classes[i]);
        _gtk->set_css_classes(vec);
    }

    geometry::Point<double> Widget_impl::position() const 
    {
        auto alloc = _gtk->get_allocation();
        return geometry::Point<double>(alloc.get_x(), alloc.get_y());
    }

    bool Widget_impl::isEditable() const
    {
        auto edit = dynamic_cast<Gtk::Editable*>(_gtk.get());        
        if(edit)
            return true;
        auto textview = dynamic_cast<Gtk::TextView*>(_gtk.get());
        if (textview)
            return true;
        return false;
    }

    bool Widget_impl::isOnelineEditable() const
    {

        auto edit = dynamic_cast<Gtk::Editable*>(_gtk.get());        
        if(edit)
            return true;
        return false;
    }

    bool Widget_impl::isMultilineEditable() const
    {
        auto textview = dynamic_cast<Gtk::TextView*>(_gtk.get());
        if (textview)
            return true;
        return false;
    }
}
