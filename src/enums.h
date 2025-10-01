#pragma once

namespace ml
{
    enum Orient 
    {
        VERTICAL,
        HORIZONTAL
    };

    enum Event
    {
        CLICK = 0,
        DOUBLE_CLICK,
        MOUSE_ENTER,
        MOUSE_LEAVE,
        MOUSE_MOVE,
        MOUSE_UP,
        MOUSE_DOWN,
        LEFT_UP,
        LEFT_DOWN,
        RIGHT_UP,
        RIGHT_DOWN,
        MIDDLE_UP,
        MIDDLE_DOWN,
        KEY_DOWN,
        KEY_UP,
        WHEEL,
        FOCUS,
        UNFOCUS,
        CHANGE,
        VALID,
        SHOWN,
        HIDDEN,
        RESIZE,
    };

    enum HAlignment
    {
        FILL,
        LEFT,
        RIGHT,
        CENTER,
        BASELINE,
    };

    enum VAlignment
    {
        TOP=1,
        BOTTOM,
        VCENTER,
    };

    enum DrawType
    {
        AUTO = 0,
        LABEL,
        ENTRY,
        MULTILINE_ENTRY,
        SLIDER,
        PROGRESS,
        CHECKBOX,
        SWITCH,
        SPINBUTTON,
        TOGGLEBUTTON,
        PASSWORD,
        COMBOBOX,
        FILE_PATH,
        DIR_PATH,
    };

    enum ImageState
    {
        IMG_NORMAL = 0,
        FILE_NOT_FOUND,
        WRONG_FORMAT
    };

    enum ImageFormat
    {
        UNKNOWN = 0,
        PNG,
        JPEG,
        WEBP,
        TIFF,
        EXR,
        HDR,
        TGA,
    };

    enum EllipsizeMode
    {
       ELLIPSIZE_NONE = 0,
       ELLIPSIZE_START,
       ELLIPSIZE_MIDDLE,
       ELLIPSIZE_END
    };
}
