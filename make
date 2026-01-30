#!/usr/bin/env python3

from ml import build
from ml.boilerplate import cpp
from ml import fileTools as ft
from ml import log
import os
import sys
import shutil
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
        log.print("Commun css not found.", "red")
    if not os.path.exists(cssGtkPath):
        log.print("gtk css not found.", "red")
    if not os.path.exists(cssEmPath):
        log.print("em css not found.", "red")

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

    if (os.path.exists("../src/mlgui_dark.css")) : 
        shutil.copyfile("../src/mlgui_dark.css", "./mlgui_dark.css")
        log.print("Dark theme variable copied.", "green")

    if (os.path.exists("../src/mlgui_light.css")) : 
        shutil.copyfile("../src/mlgui_light.css", "./mlgui_light.css")
        log.print("Light theme variable copied.", "green")

    log.print("Css replaced.", "green")

if (sys.argv[1] == "css"):
    replaceCss()
    exit()

fm = "/media/romain/Donnees/Programmation/cpp/frameworks"
libs = "/media/romain/Donnees/Programmation/cpp/libs"

for arg in sys.argv:
    if "libs=" in arg:
        libs = arg.split("=")[1]
    elif "fm=" in arg or "cpp-utils=" in arg:
        fm = arg.split("=")[1]

cpp.generate("../src")

includes = [
    "../src",
    fm,
    libs + "/json",
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
gbl.flags = ["-std=c++17"]

widgets_gen = widgets.get()
log.print("Generating the widgets factory constructors...", "yellow")
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
gbl.write("../src/Widget_creators_impl_fixed_gen.h", widgets_gen["widgetsCreators_cpp"].replace("Box::", "Fixed::"))
gbl.write("../src/Container_creators_impl_fixed_gen.h", widgets_gen["containersCreators_cpp"].replace("Box::", "Fixed::"))
gbl.write("../src/Widget_types_widgets_classes_gen.h", widgets_gen["widgets_classes"])
gbl.write("../src/creators_implpopover_gen.h", widgets_gen["popover_widgets_impl"])
log.print("Widgets factory constructors generated.", "green")

log.print("generating the widget events vectors and binding with impl...", "yellow")
events = widgets_events.get()
gbl.write("../src/Widget_events_gen.h", events[0])
gbl.write("../src/Widget_events_impl_gen.h", events[1])
gbl.write("../src/Widget_events_trigger_impl_gen.h", events[2])
log.print("Widget events generated.", "green")

log.print("generating props subclasses...")
props_gen = props.props()
gbl.write("../src/props_gen.h", props_gen["h"])
gbl.write("../src/props_impl_gen.h", props_gen["cpp"])
log.print("props generated.", "green")

if ("gtk" not in sys.argv):
    #build for wasm
    cpp = build.create("mlgui", sys.argv, "em++")
    cpp.static = False

    cpp.includes = includes
    cpp.addToSrcs(srcs)
    cpp.addToSrcs([
        "../src/em",
        ])
    cpp.addEmiscriptenFlags()
    cpp.addToLibs(libs)
    cpp.definitions += defs

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

    # sudo apt install libwebkitgtk-6.0-dev
    cpp.addInstalledLibrary("webkitgtk-6.0")

    cpp.addToLibs([
        "pthread",
        "stdc++fs",
        "X11",
        "fmod",
        "fmodL",
        ])

#should add a way to add the version of mlapi in dependencies here.
if not cpp.release : 
    cpp.addToLibs([
        fm + "/build/libmlapi.so",
        ])
    #cpp.flags += ["-fsanitize=thread"]

else : 
    #add the version dependencis for it
    cpp.addProject("/opt/mlapi/lib")

if ("shared" in sys.argv):
    cpp.shared = True

if("clean" in sys.argv or "clear" in sys.argv):
    cpp.clean()
    exit()
else:
    cpp.build()

replaceCss()
