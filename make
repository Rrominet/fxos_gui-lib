#!/usr/bin/env python3

from ml import build
from ml.boilerplate import cpp
from ml import fileTools as ft
import os
import sys
sys.path.append("../")
from scripts import widgets
from scripts import widgets_events
from scripts import props


def replaceCss() : 
    #building css file
    cssPath = "../src/mlgui.css"
    cssGtkPath = "../src/gtk/mlgui.css"
    cssEmPath = "../src/em/mlgui.css"

    gtkdest = "./mlgui_gtk.css"
    emdest = "./mlgui_em.css"

    if not os.path.exists(cssPath):
        print ("Commun css not found.")
    if not os.path.exists(cssGtkPath):
        print ("gtk css not found.")
    if not os.path.exists(cssEmPath):
        print ("em css not found.")

    css = ""
    css = ft.read(cssPath)

    cssGtk = ""
    cssGtk = ft.read(cssGtkPath)

    cssEm = ""
    cssEm = ft.read(cssEmPath)

    finalGtk = css + cssGtk
    finalEm = css + cssEm

    finalGtk = finalGtk.replace("\n", "")
    finalGtk = finalGtk.replace("  ", "")
    finalGtk = finalGtk.replace("\t", "")

    finalEm = finalEm.replace("\n", "")
    finalEm = finalEm.replace("  ", "")
    finalEm = finalEm.replace("\t", "")

    ft.write(finalGtk, gtkdest)
    ft.write(finalEm, emdest)

    print ("Css replaced.")

if (sys.argv[1] == "css"):
    replaceCss()
    exit()

fm = "/media/romain/Donnees/Programmation/cpp/frameworks"
libs = "/media/romain/Donnees/Programmation/cpp/libs"

cpp.generate("../src")

includes = [
    "../src",
    fm,
    libs + "/json",
    #not needed anymore
#libs + "/boost-install/include",
    libs + "/eigen",
    libs + "/fmodstudioapi20000linux/api/core/inc",
        ]

srcs = [
        "../src",
        ]

libs = [
        ]

defs = ["NO_LOG"]

gbl = build.create("mlgui", sys.argv)

widgets_gen = widgets.get()
print("Generating the widgets factory constructors...")
gbl.write("../src/WidgetsFactory_types_gen.h", widgets_gen["containersFactoryH"] + "\n" + widgets_gen["widgetsFactoryH"])
gbl.write("../src/WidgetsFactory_types_impl_gen.h", widgets_gen["containersFactoryCpp"] + "\n" + widgets_gen["widgetsFactoryCpp"])
gbl.write("../src/Widget_types_classes_gen.h", widgets_gen["classes"])
gbl.write("../src/Widget_types_includes_gen.h", widgets_gen["includes"])
gbl.write("../src/Widget_creators_gen.h", widgets_gen["widgetsCreators"])
gbl.write("../src/Container_creators_gen.h", widgets_gen["containersCreators"])
gbl.write("../src/Widget_creators_impl_gen.h", widgets_gen["widgetsCreators_cpp"])
gbl.write("../src/Container_creators_impl_gen.h", widgets_gen["containersCreators_cpp"])
gbl.write("../src/Widget_creators_implsc_gen.h", widgets_gen["widgetsCreators_cpp"].replace("Box::", "Scrollable::"))
gbl.write("../src/Container_creators_implsc_gen.h", widgets_gen["containersCreators_cpp"].replace("Box::", "Scrollable::"))
gbl.write("../src/Widget_creators_implab_gen.h", widgets_gen["widgetsCreators_cpp"].replace("Box::", "AbsoluteBox::"))
gbl.write("../src/Container_creators_implab_gen.h", widgets_gen["containersCreators_cpp"].replace("Box::", "AbsoluteBox::"))
gbl.write("../src/Widget_types_widgets_classes_gen.h", widgets_gen["widgets_classes"])
gbl.write("../src/creators_implpopover_gen.h", widgets_gen["popover_widgets_impl"])
print("Widgets factory constructors generated.")

print ("generating the widget events vectors and binding with impl...")
events = widgets_events.get()
gbl.write("../src/Widget_events_gen.h", events[0])
gbl.write("../src/Widget_events_impl_gen.h", events[1])
print ("Widget events generated.")

print ("generating props subclasses...")
props_gen = props.props()
gbl.write("../src/props_gen.h", props_gen["h"])
gbl.write("../src/props_impl_gen.h", props_gen["cpp"])
print ("props generated.")

if ("gtk" not in sys.argv):
    #build for wasm
    em = build.create("mlgui", sys.argv, "em++")
    em.static = False

    em.includes = includes
    em.addToSrcs(srcs)
    em.addToSrcs([
        "../src/em",
        ])
    em.addEmiscriptenFlags()
    em.addToLibs(libs)
    em.definitions += defs

    if("clean" in sys.argv or "clear" in sys.argv):
        em.clean()
        exit()
    else:
        em.build()

if ("wasm" not in sys.argv):
    #build with g++
    cpp = build.create("mlgui", sys.argv)
    cpp.static = False

    cpp.includes = includes
    cpp.addToSrcs(srcs)
    cpp.addToSrcs([
        "../src/gtk",
        ])
    cpp.addToLibs(libs)
    cpp.definitions += defs
    cpp.addInstalledLibrary("gtkmm-4.0")

    cpp.addToLibs([
        "pthread",
        "stdc++fs",
        "X11",
        "fmod",
        "fmodL",
        ])

    if not cpp.release : 
        cpp.addToLibs([
            "../../../frameworks/build/libmlapi.so",
            ])
    elif cpp.release : 
        cpp.addToLibs([
            "mlapi"
            ])

    if ("shared" in sys.argv):
        cpp.shared = True

    if("clean" in sys.argv or "clear" in sys.argv):
        cpp.clean()
        exit()
    else:
        cpp.build()

replaceCss()
