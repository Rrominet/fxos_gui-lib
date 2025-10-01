#pragma once
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/spinner.h>
#include <memory>
#include "./Widget_impl.h"
#include "../enums.h"

namespace ml
{
    class Button;
    class Button_impl : public Widget_impl
    {
        public:
            Button_impl(Button* abstract);
            virtual ~Button_impl() = default;

            std::shared_ptr<Gtk::Button> button()
            {
                return std::static_pointer_cast<Gtk::Button>(_gtk);
            }
            virtual void _createWidget() override;

            void setText(const std::string& text);
            std::string text();

            void mkLoading();
            void stopLoading();

        protected : 
            virtual void _addOnMouseUp(Event event, const std::function<void (EventInfos&)>& callback) override ;
            virtual void _addOnLeftUp(Event event, const std::function<void (EventInfos&)>& callback) override ;

            std::shared_ptr<Gtk::Box> _box;
            std::shared_ptr<Gtk::Label> _label;
            std::shared_ptr<Gtk::Spinner> _spinner;
    };
}
