
#pragma once
#include <gtkmm/spinner.h>
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class Spinner;
    class Spinner_impl : public Widget_impl
    {
        public:
            Spinner_impl(Spinner* abstract);
            virtual ~Spinner_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::Spinner> spinner(){return std::static_pointer_cast<Gtk::Spinner>(_gtk);}

            virtual void show() override;
            virtual void hide() override;
    };
}
