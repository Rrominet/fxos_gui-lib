
#include "./Button_impl.h"
#include "../Button.h"
#include "../EventInfos.h"
#include <gdkmm/cursor.h>
#include "../Window.h"

namespace ml
{
    Button_impl::Button_impl(Button* abstract) : Widget_impl((Widget*)abstract)
    {
    }

    void Button_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::Button>();
        _box = std::make_shared<Gtk::Box>();
        _label = std::make_shared<Gtk::Label>();
        _label->set_hexpand();
        _label->set_halign(Gtk::Align::FILL);
        _spinner = std::make_shared<Gtk::Spinner>();
        _spinner->set_halign(Gtk::Align::END);

        _box->append(*_label);
        _box->append(*_spinner);
        _spinner->hide();

        this->button()->set_child(*_box);
    }

    void Button_impl::setText(const std::string& text)
    {
        _label->set_text(text);	
    }

    std::string Button_impl::text()
    {
        return _label->get_text();
    }

    void Button_impl::_addOnMouseUp(Event event, const std::function<void (EventInfos&)>& callback)
    {
        this->button()->signal_clicked().connect([callback](){
                EventInfos e;
                callback(e);
                });
    }

    void Button_impl::_addOnLeftUp(Event event, const std::function<void (EventInfos&)>& callback)
    {
        this->button()->signal_clicked().connect([callback](){
                EventInfos e;
                callback(e);
                });
    }

    void Button_impl::mkLoading()
    {
        _spinner->show();
        _spinner->start();
    }

    void Button_impl::stopLoading()
    {
        _spinner->stop();
        _spinner->hide();
    }
}
