import json
import re

#version could be "gtk" or "wasm"
def css_vars(jsonfile, version) : 
    data = json.load(open(jsonfile))
    if (version == "wasm"): 
        css = ":root{\n"
        for k in data : 
            css += "--" + k + ":" + data[k] + ";\n"
        css += "}"
        return css
    elif (version == "gtk"):
        css = ""
        for k in data : 
            css += "@define-color " + k + " " + data[k] + ";\n"
        return css

def transform_std_to_gtk(css) : 
    return re.sub(r"var\(\s*--([A-Za-z0-9_-]+)\s*\)", r"@\1", css)
