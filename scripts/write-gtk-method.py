#!/usr/local/bin/python
import sys
import os
from ml import fileTools as ft

if (len(sys.argv) < 4):
    print("Usage: write-gtk-method.py <filepath> <start> <end>")
    sys.exit(1)

filepath = sys.argv[1]
start = int(sys.argv[2])
try : 
    end = int(sys.argv[3])
    if end < start :
        end = start
except:
    end = start

content = ft.read(filepath)
lines = content.split("\n")

for i in range(start, end):
    if not "Gtk::" in lines[i] : 
        continue

    l = lines[i]
    l = l.replace("Gtk::", "ml::")
    l = l.replace(";", "{*impl*;}")

    tmp = l
    while "  " in tmp:
        tmp = tmp.replace("  ", "")
    while "\t" in tmp:
        tmp = tmp.replace("\t", "")
    
    tmp = tmp.split(" ")
    if len(tmp) < 2 :
        continue

    method = tmp[1].split("(")[0]

    l = l.replace("*impl*", "_gtk->" + method + "(*args*)")

    args = lines[i].split("(")
    args = args[1].split(")")[0]
    args = args.split(",")
    for j in range(len(args)) : 
        a = args[j]
        a = a.replace("const ", "")
        a = a.replace("&", "")
        a = a.replace("*", "")
        if a[0] == " " :
            a = a[1:]

        a = a.split(" ")
        a = a[1]

        args[j] = a

    argsStr = ""
    for a in args : 
        argsStr += a + ", "

    argsStr = argsStr[:-2]
    l = l.replace("*args*", argsStr)
    lines[i] = l

newContent = "\n".join(lines)
ft.write(newContent, filepath)
