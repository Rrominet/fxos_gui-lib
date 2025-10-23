from ml import fileTools as ft
import os

d = "/media/romain/Donnees/Programmation/C++/cmake/mlgui.2/src/em"

def newLine(l) : 
    tmp = l.split("=")
    first = tmp[0]
    tmp = tmp[1].split("\"createElement\"")
    arg = tmp[1]
    arg = arg.replace(", ", "")
    arg = arg.replace("));", "")
    arg = arg.replace(");", "")

    if ("make_shared" in l) :
        return first + " = std::make_shared<emval>(em::createElement(" + arg + "));"
    else : 
        return first + " = em::createElement(" + arg + ");"

for name in os.listdir(d):
    if ft.ext(name) != "cpp" : 
        continue
    if name == "em.cpp" : 
        continue

    content = ft.read(d + "/" + name)
    lines = content.split("\n")
    nlines = []
    for l in lines : 
        if "\"createElement\"" in l : 
            print ("old : " + l)
            print ("new : " + newLine(l))
            nlines.append(newLine(l))
        else : 
            nlines.append(l)

    ft.write("\n".join(nlines), d + "/" + name)

