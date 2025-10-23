#!/usr/local/bin/python
import sys
import os
from ml import fileTools as ft

if len(sys.argv) < 2:
    print("Usage: create-element.py <ElementType>")
    sys.exit(1)

#*elmt_min* is for *elmt* but with no maj

elmtHContent = """
#pragma once
#include "./Widget.h"

#include <memory>
#ifdef __EMSCRIPTEN__
#include "./em/*elmt*_impl.h"
#else
#include "./gtk/*elmt*_impl.h"
#endif

namespace ml
{
    class *elmt* : public Widget
    {
        public : 
            *elmt*();
            virtual ~*elmt*() = default;
            virtual void init() override;

            std::shared_ptr<ml::*elmt*_impl> *elmt_min*(){return std::static_pointer_cast<*elmt*_impl>(_impl);}
    };
}
"""

elmtCppContent = """
#include "./*elmt*.h"

namespace ml
{
    *elmt*::*elmt*() : Widget()
    {

    }
    void *elmt*::init()
    {
        this->addCssClass("*elmt_min*");
    }
}
"""

elmtHGtkImplContent = """
#pragma once
#include <gtkmm/*elmt_min*.h>
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class *elmt*;
    class *elmt*_impl : public Widget_impl
    {
        public:
            *elmt*_impl(*elmt** abstract);
            virtual ~*elmt*_impl() = default;

            virtual void _createWidget() override;
            std::shared_ptr<Gtk::*elmt*> *elmt_min*(){return std::static_pointer_cast<Gtk::*elmt*>(_gtk);}
    };
}
"""

elmtCppGtkImplContent = """
#include "./*elmt*_impl.h"
#include "../*elmt*.h"

namespace ml
{
    *elmt*_impl::*elmt*_impl(*elmt** abstract) : Widget_impl((Widget*)abstract)
    {
    }
    void *elmt*_impl::_createWidget()
    {
        _gtk = std::make_shared<Gtk::*elmt*>();
        // implement sepecific stuff here if necessecary.
    }
}
"""

elmtHEmImplContent = """
#pragma once
#include "./em.h"
#include <memory>
#include "./Widget_impl.h"

namespace ml
{
    class *elmt*;
    class *elmt*_impl : public Widget_impl
    {
        public:
            *elmt*_impl(*elmt** win);
            virtual ~*elmt*_impl();

            virtual void _createWidget() override;
    };
}
"""

elmtCppEmImplContent = """
#include "./*elmt*_impl.h"
#include "../*elmt*.h"

namespace ml
{
    *elmt*_impl::*elmt*_impl(*elmt** abstract) : Widget_impl((Widget*)abstract)
    {
    }

    *elmt*_impl::~*elmt*_impl()
    {
    }

    void *elmt*_impl::_createWidget()
    {
        auto domWidget = em::createElement("*elmt_min*");
        _dom = std::make_shared<emval>(domWidget);
        (*_dom)["classList"].call<void, std::string>("add", "*elmt_min*");
    }
}
"""

contents = {
    'h' : elmtHContent,
    'cpp' : elmtCppContent,
    'h_gtk_impl' : elmtHGtkImplContent,
    'cpp_gtk_impl' : elmtCppGtkImplContent,
    'h_em_impl' : elmtHEmImplContent,
    'cpp_em_impl' : elmtCppEmImplContent
}


elmt = sys.argv[1]
elmt_min = elmt[0].lower() + elmt[1:]

for c in contents : 
    contents[c] = contents[c].replace("*elmt*", elmt)
    contents[c] = contents[c].replace("*elmt_min*", elmt_min)

root = ft.parent(__file__)
root = root + "/../src"

if not os.path.exists(root + "/" + elmt + ".h"):
    ft.write(contents["h"], root + "/" + elmt + ".h")
if not os.path.exists(root + "/" + elmt + ".cpp"):
    ft.write(contents["cpp"], root + "/" + elmt + ".cpp")
if not os.path.exists(root + "/gtk/" + elmt + "_impl.h"):
    ft.write(contents["h_gtk_impl"], root + "/gtk/" + elmt + "_impl.h")
if not os.path.exists(root + "/gtk/" + elmt + "_impl.cpp"):
    ft.write(contents["cpp_gtk_impl"], root + "/gtk/" + elmt + "_impl.cpp")
if not os.path.exists(root + "/em/" + elmt + "_impl.h"):
    ft.write(contents["h_em_impl"], root + "/em/" + elmt + "_impl.h")
if not os.path.exists(root + "/em/" + elmt + "_impl.cpp"):
    ft.write(contents["cpp_em_impl"], root + "/em/" + elmt + "_impl.cpp")

print("Element " + elmt + " created.")
