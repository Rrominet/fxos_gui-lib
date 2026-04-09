# PROJECT
**mlgui** — Cross-platform C++ GUI framework abstracting App/Window/Widget/Property/Command concepts over GTK4 (desktop) and Emscripten/DOM (web).

---

# STACK

| Item | Detail |
|------|--------|
| Language | C++17 |
| Backends | GTK4 (gtkmm-4.0), Emscripten (WebAssembly + DOM via emscripten::val) |
| Conditionals | `#ifdef __EMSCRIPTEN__` selects em/ vs gtk/ impl |
| Audio | FMOD (VideoSound) |
| Process | Boost.Process (VideoSound, exec_async) |
| Markdown | libmd4c (MdView) |
| JSON | nlohmann/json |
| Image | GDK Pixbuf (gtk), HTML img (em) |
| Threading | Custom `th::ThreadPool`, `std::thread` |
| Video | ffmpeg/ffprobe subprocess piped JPEG frames |
| CSS | GTK CssProvider / DOM style attribute |
| Build | [AMBIGUOUS: no Makefile/CMakeLists provided] |

---

# ARCHITECTURE

## Directory Layout
```
/ (root)
├── gtk/          # GTK4-specific _impl files
├── em/           # Emscripten-specific _impl files
├── *_gen.h       # Code-generated accessors/creators (DO NOT EDIT)
├── *_impl.h/.cpp # Backend-specific implementation classes
├── App.h/.cpp/.hpp
├── Widget.h/.cpp
├── Window.h/.cpp
├── Box.h/.cpp/.hpp
├── Scrollable.h/.cpp/.hpp
└── ...
```

## Core Abstraction Pattern
Every GUI class has three layers:
1. **Abstract class** (`Box`, `Button`, `Widget`, etc.) — user-facing API, in root dir
2. **Impl class** (`Box_impl`, `Button_impl`) — backend-specific, in `gtk/` or `em/`
3. **`_impl` member** (`std::shared_ptr<Widget_impl> _impl`) in each abstract class

## Widget Lifecycle (critical)
```cpp
// ALL widgets created via WidgetsFactory — NEVER with new/make_shared directly
ml::app()->checker().set("can-construct-widget", true);
auto widget = std::make_shared<W>();
widget->_impl = std::make_shared<W_impl>(widget.get());
widget->_impl->_createWidget();
widget->_impl->_createBasicEvents();
widget->_createBasicEvents();
ml::app()->checker().set("can-construct-widget", false);
parent->append(widget);
widget->init();
widget->setEvents();
```
Use `box->createButton()`, `box->createBox()`, etc. — never construct directly.

## Window Lifecycle
Windows created only via `App::createWindow<T>()` / `App::createDialog<T>()` → `WindowsFactory`.

## Key Data Flow
- `App` (singleton via `ml::app()`) owns: `_windows`, `_cmds`, `_props`, `_panels`, `_menusFactory`, `_widgetsFactory`, `_windowsFactory`, `_pool`
- `Window` owns: `_content` (Box) → `_head`, `_body` (→ `_menuBar`, `_main` Scrollable), `_foot`; plus per-window `_cmds` (CommandsManager)
- `Widget::_window` → back-pointer to owning Window (set via `setWindow()` on append)
- `Widget::_parent` → back-pointer to parent Widget

## Composed Widgets
`ComposedWidget` base for multi-widget components. Must populate `_composed` (Vec of `variant<Widget*, ComposedWidget*>`). Created via `box->createComposedWidget<T>(...)`.

## Property/Observer System
- `Property` extends `Observed`; inputs extend `Observer`
- `props::connect(prop, input)` wires bidirectional: property→widget via `addObserver`, widget→property via `addEventListener(CHANGE,...)`
- `PropertyWidget<Prop>` / `ComposedPropertyWidget<Prop>` templates handle full UI creation

## Command System
- `Command` base → `GuiCommand` (queues exec on main thread) → `AsyncGuiCommand` (execAsync) → `GuiBackendCommand` (IPC to Process)
- Commands registered in `CommandsManager` (per-app or per-window)
- Keybinds matched in `Window::setBasicEvents()` KEY_DOWN handler

---

# CONVENTIONS

## Naming
- Abstract classes: PascalCase (`Box`, `AbsoluteBox`)
- Impl classes: `ClassName_impl` in `gtk/` or `em/` subdirs
- Private members: `_camelCase`
- Generated files: `*_gen.h` — never edit manually
- `//bp cg` comment → field has generated getter/setter in `*_gen.h`
- `//bp cgs` → getter/setter + custom setter
- `//bp g` → getter only

## Code-Generation
`*_gen.h` files are auto-generated — provide accessors. Included with `#include` directly inside class bodies. Regenerated on rebuild.

## Event Handling
```cpp
widget->addEventListener(Event::LEFT_UP, [](const EventInfos& e){ ... });
// EventInfos fields: x, y, dx, dy, mvtx, mvty, key, ctrl, alt, shift, super, preventDefault, type
```
- `e.preventDefault = true` (default) blocks propagation
- `e.stopPropagation()` stops all listeners of same event type this tick

## CSS
- GTK: `CssProvider` per widget, inline `attr:value` string
- EM: `dom["style"].set(attr, value)` or `addCssClass()`
- `widget->addCss("attr:value")` or `widget->addCss(attr, val)`

## Async / Threading
- `ml::app()->queue(callback)` — always runs on main/GUI thread
- `ml::app()->execAsync(torun, onfinished)` — `torun` on pool thread, `onfinished` queued to main
- NEVER call GUI methods from non-main thread; use `queue()`

---

# CONSTRAINTS

- **NEVER** construct widgets with `new`/`make_shared`/stack — only via `create*()` factory methods
- **NEVER** construct windows directly — only via `app->createWindow<T>()`/`createDialog<T>()`
- **NEVER** call `widget->setWindow()` directly — only `append()`/`prepend()`/`setChild()` trigger it
- **NEVER** edit `*_gen.h` files
- **DO NOT** perform GUI operations off the main thread — use `ml::app()->queue()`
- `ComposedWidget` subclasses **must** populate `_composed` or `createComposedWidget` will assert
- `AskPropertyDialog::drawProp()` must be called **after** `set()`
- `Widget` constructor asserts `can-construct-widget` checker — will fail without factory

---

# CONTEXT INJECTIONS

## EventInfos struct
```cpp
struct EventInfos {
    double x, y, dx, dy, mvtx, mvty;
    int click_numbers = -1;
    unsigned int keyval, keycode;
    std::string key;
    bool preventDefault = true;
    bool ctrl=false, alt=false, shift=false, super=false;
    bool visible=true;
    double width=0, height=0;
    Event type = NONE;
    void stopPropagation();
};
```

## Event enum (key values)
`NONE, CLICK, DOUBLE_CLICK, MOUSE_ENTER, MOUSE_LEAVE, MOUSE_MOVE, MOUSE_UP, MOUSE_DOWN, LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN, MIDDLE_UP, MIDDLE_DOWN, KEY_DOWN, KEY_UP, WHEEL, FOCUS, UNFOCUS, CHANGE, VALID, SHOWN, HIDDEN, RESIZE, DRAG_START, DRAG_END, DRAGGING`

## Property types
`BoolProperty`, `IntProperty`, `FloatProperty`, `DoubleProperty`, `StringProperty`, `EnumProperty`, `ColorProperty`
- Create only via `ml::app()->props().create<T>(name, value, min, max, desc)`
- Destroy via `ml::app()->props().destroy(prop)`

## DrawType enum (for PropertyWidget)
`AUTO, LABEL, ENTRY, MULTILINE_ENTRY, SLIDER, PROGRESS, CHECKBOX, SWITCH, SPINBUTTON, TOGGLEBUTTON, PASSWORD, COMBOBOX, FILE_PATH, DIR_PATH, DATE, TIME, DATE_TIME, COLOR_BUTTON, COLOR_PICKER`

## App singleton API (key methods)
```cpp
ml::app()                          // global App* accessor
app->createMainWindow<T>()         // creates + sets as main
app->createWindow<T>(parent, id)
app->createDialog<T>(parent, id)
app->cmds().createCommand<GuiCommand>(name, id)
app->props().create<BoolProperty>(...)
app->menusFactory().create(id, name)
app->panels().create(id, drawFunc)
app->queue(callback)               // run on GUI thread
app->setTimeout(cb, ms)            // returns id
app->setInterval(cb, ms, nb, done) // nb=-1 = infinite
app->removeTimeout(id)
app->execAsync(torun, onfinished)
app->info/warning/error/confirm/ask(message, parent)
app->openFile/openFolder/saveFile(title, dir, cb)
app->isDarkTheme() -> bool
app->paths().path(relative) -> std::string
app->paths().libdata() -> std::string (icons, CSS)
app->widgetsFactory() / windowsFactory() / menusFactory()
app->focused() -> Window*
app->focusedWidget() -> Widget*
```

## Window layout structure
```
Window
└── _content (Box)
    ├── _head (Box, HORIZONTAL)
    ├── _body (Box, VERTICAL)
    │   ├── _menuBar (MenuBar)
    │   └── _main (Scrollable) ← primary content area
    └── _foot (Box, HORIZONTAL)
```
Override `Window::init()` → call `Window::init()` first, then use `_main->createX()`.

## Widget creator pattern (Box/Scrollable/AbsoluteBox/Fixed/Popover)
```cpp
auto btn   = box->createButton("text");
auto lbl   = box->createLabel("text");
auto entry = box->createEntry();
auto spin  = box->createSpinButton();
auto sl    = box->createSlider();
auto cb    = box->createCheckBox("text");
auto sw    = box->createSwitch();
auto img   = box->createImage();
auto prog  = box->createProgressBar();
auto sub   = box->createScrollable();
auto abox  = box->createAbsoluteBox();
auto fixed = box->createFixed();
auto pop   = box->createPopover();
auto canvas= box->createCanvas();             // template, default ml::Canvas
auto cw    = box->createComposedWidget<T>(args...); // returns shared_ptr<T>
```

## GuiCommand usage
```cpp
auto cmd = app->cmds().createCommand<GuiCommand>("Name", "id");
cmd->setExec([](const std::any& args){ /* runs queued on main thread */ });
cmd->setKeybind("ctrl s");
cmd->setHelp("description");
cmd->setConfirm(true); // ask confirmation before exec
// Exec fires: _before → queue(_exec + _after)
```

## GuiBackendCommand usage
```cpp
auto cmd = app->createBackendCommand(process, "functionName", json_args, cb, onetime);
cmd->exec(); // calls ipc::call, response cb queued to main thread
// setExec() is FORBIDDEN on GuiBackendCommand
```

## Keybind format
String: `"ctrl s"`, `"ctrl shift s"`, `"alt F4"`, `"Return"`, `"Escape"`
Matched case-sensitive on `e.key` (GTK keyval name or JS key name).

## AbsoluteBox (Overlay) note
`AbsoluteBox` is actually a GTK `Gtk::Overlay` / CSS `position:relative` container.
Children stacked absolutely. Use `setBackground(widget)` for base layer, `append()` for overlay layers.
`sendToFront/sendToBack/moveDepth()` control z-order.

## ml::Vec<T>
Custom vector wrapper. Key extras: `push(x)`, `prepend(x)`, `remove(x)` (by value), `removeByIndex(i)`, `contains(x)`, `first()`, `last()`, `move(from, to)`, `setPosition(x, pos)`, `.vec` exposes `std::vector<T>` directly.

## VerticalTable / VerticalTableModel
Virtual scrolling table. `linkToModel(shared_ptr<VerticalTableModel>)`. Model notifies: `attributes-changed`, `data-added`, `data-removed`, `data-modified`. Max 50 rows rendered (`max_row_size()`). Events: `row-clicked` (data=`VerticalRow*`), `header-clicked` (data=`Label*`).

## List<T, Dynamic, MaxDrawn> template
- `T` needs: `draw()` (if MaxDrawn=true), `gui() -> Widget*`, `searchStr() -> string`
- `createElmt(args...)` adds elements
- `SelectionType`: `NONE`, `SINGLE`, `MULTIPLE`
- Dynamic=true adds add/remove context menu commands# PROJECT
**mlgui** — Cross-platform C++ GUI framework abstracting App/Window/Widget/Property/Command over GTK4 (desktop) and Emscripten/DOM (web).

---

# STACK

| Item | Detail |
|------|--------|
| Language | C++17 |
| Backends | GTK4 (gtkmm-4.0), Emscripten (WebAssembly + DOM via `emscripten::val`) |
| Conditionals | `#ifdef __EMSCRIPTEN__` selects `em/` vs `gtk/` impl |
| Audio | FMOD (VideoSound) |
| Process | Boost.Process (VideoSound, exec_async) |
| Markdown | libmd4c (MdView) |
| JSON | nlohmann/json |
| Image | GDK Pixbuf (gtk), HTML `<img>` (em) |
| Video | ffmpeg/ffprobe subprocess, piped MJPEG frames |
| Threading | Custom `th::ThreadPool`, `std::thread` |
| CSS | GTK CssProvider / DOM style attribute |
| Build | [AMBIGUOUS: no CMakeLists/Makefile present] |

---

# ARCHITECTURE

## Directory Layout
```
/ (root)
├── gtk/                  # GTK4-specific _impl .h/.cpp
├── em/                   # Emscripten-specific _impl .h/.cpp
├── *_gen.h               # Code-generated accessors/creators (DO NOT EDIT)
├── *.h / *.cpp / *.hpp   # Abstract classes + template implementations
├── commands/             # Command system (Command, CommandsManager, ProcessCommand)
├── observers/            # Observer/Observed base classes
├── em.h / em.cpp         # DOM utility namespace (em::)
├── enums.h               # All enums (Event, HAlignment, DrawType, ImageState, etc.)
├── entries_macros.h      # ENTRY_GET_SET, NB_ENTRY_GET_SET macros
├── keybinds.h/.cpp       # Keybind string matching
└── main.cpp              # Example entry point
```

## Core Abstraction Pattern (3 layers)
1. **Abstract** (`Box`, `Button`, `Widget`) — user-facing API, root dir
2. **Impl** (`Box_impl`, `Button_impl`) — backend-specific, in `gtk/` or `em/`
3. **`_impl` member** (`std::shared_ptr<Widget_impl> _impl`) in each abstract

## Widget Lifecycle (CRITICAL — must follow exactly)
```cpp
// Internal factory pattern only — never construct directly
ml::app()->checker().set("can-construct-widget", true);
auto widget = std::make_shared<W>();
widget->_impl = std::make_shared<W_impl>(widget.get());
widget->_impl->_createWidget();        // creates GTK widget or DOM element
widget->_impl->_createBasicEvents();   // hover tracking, etc.
widget->_createBasicEvents();          // focus tracking, double-click
ml::app()->checker().set("can-construct-widget", false);
parent->append(widget);                // sets parent + window, appends to DOM/GTK
widget->init();                        // CSS class + layout setup
widget->setEvents();                   // post-parent event wiring (em: setEvents() needed)
```

## Window Lifecycle
Only via `App::createWindow<T>()` / `App::createDialog<T>()` → `WindowsFactory::createWindow<T>()`.  
Window gets `_impl = make_shared<Window_impl>`, then `_impl->_createWindow()`, then `init()`.

## Key Data Flow
```
App (singleton ml::app())
├── _windows: unordered_map<string, shared_ptr<Window>>
├── _cmds: CommandsManager (app-global)
├── _props: PropertiesManager
├── _panels: PanelsManager
├── _menusFactory: MenusFactory (holds Menu → Popover)
├── _widgetsFactory: WidgetsFactory
├── _windowsFactory: WindowsFactory
├── _pool: th::ThreadPool
└── _impl: App_impl (GTK: Glib::Dispatcher queue; EM: JS event loop)

Window
├── _impl: Window_impl (GTK: Gtk::Window; EM: DOM div.window)
├── _content (Box) → _head (Box), _body (Box), _foot (Box)
│   └── _body: _menuBar (MenuBar), _main (Scrollable) ← primary content
├── _cmds: CommandsManager (per-window)
└── _state: WindowEventState {x,y,alt,ctrl,shift,meta,key}

Widget
├── _impl: Widget_impl (GTK: Gtk::Widget; EM: emval DOM)
├── _parent: Widget*
└── _window: Window*
```

## Scrollable Internals
`Scrollable` contains an embedded `Box _box` (not a pointer). Content is accessed via `scrollable->content()` (returns `Box&`). All `create*()` methods delegate to `_box`.

## Composed Widget System
- `ComposedWidget` base: must populate `_composed` (Vec of `variant<Widget*, ComposedWidget*>`)
- Created via `box->createComposedWidget<T>(args...)` → calls `T(args...)`, checks `_composed.size() > 0`
- `ComposedWidget` operations (show/hide/addEventListener/setHelp) iterate `_composed`
- `ComposedInput` extends `ComposedWidget` with `setValue/valueAsAny` interface
- `ComposedPropertyWidget<Prop>` handles full label+input UI for composed inputs

## Property/Observer System
- `Property` extends `Observed`; widgets extend `Observer`
- `props::connect(prop, input)`: 
  - property→input: `addObserver(input, "value")` → `input->setValue(valueAsString(a))`
  - input→property: `addEventListener(CHANGE)` → `prop->set(val, input)`
- `PropertyWidget<Prop>` / `ComposedPropertyWidget<Prop>` — full UI in one template call
- `prop->widgetsConnected()` → `Vec<shared_ptr<Box>>` tracks UI boxes for show/hide

## Command System
```
Command (base)
└── GuiCommand: exec() queues via ml::app()->queue()
    ├── AsyncGuiCommand: exec() via ml::app()->execAsync()
    └── GuiBackendCommand: exec() via ipc::call(process, function, args, cb)
GuiProcessCommand: exec() via ml::app()->execAsync() wrapping ProcessCommand
```
- Keybind priority in `Window::setBasicEvents()`: windowKeyBinds → window cmds → app cmds
- `setConfirm(true)` must be called BEFORE `setExec()` on GuiCommand

## Code Generation (`*_gen.h`)
All `*_gen.h` included **inside class bodies** via `#include`. Provide:
- Accessors for `//bp cg` fields (getter+setter)
- `//bp cgs` → getter + custom setter
- `//bp g` → getter only
- `Widget_creators_gen.h` / `Container_creators_gen.h` → `create*()` declarations
- `Widget_creators_impl_gen.h` etc. → `create*()` implementations delegating to `WidgetsFactory`

---

# CONVENTIONS

## Naming
- Abstract classes: `PascalCase` (`Box`, `AbsoluteBox`, `TimeSliderInOut`)
- Impl classes: `ClassName_impl` in `gtk/` or `em/` subdir
- Private/protected members: `_camelCase`
- Generated files: `*_gen.h` — **never edit**
- `//bp cg` = getter+setter generated; `//bp cgs` = getter+custom setter; `//bp g` = getter only

## Widget Creator Methods
All containers (`Box`, `Scrollable`, `AbsoluteBox`, `Fixed`, `Popover`, `Window`) expose:
```cpp
createButton(text), createLabel(text), createEntry(text), createSpinButton(),
createSlider(), createCheckBox(text), createSwitch(), createToggleButton(text),
createProgressBar(), createImage(), createSpinner(), createMultilineEntry(),
createWebView(), createPasswordEntry(), createDateEntry(), createTimeEntry(),
createDateTimeEntry(), createBox(), createScrollable(), createAbsoluteBox(),
createFixed(), createPopover(), createCanvas<T>(), createComposedWidget<T>(args...)
```
Scrollable additionally proxies all `Box` creators through `_box`.

## Event Handling Pattern
```cpp
widget->addEventListener(Event::LEFT_UP, [](EventInfos& e){ 
    e.preventDefault = true;  // default, blocks JS default
    // e.stopPropagation() → stops all listeners of same type this tick
});
```
Events initialized lazily: first `addEventListener` for each type wires the underlying impl listener.

## CSS Application
- GTK: `_cssProvider` per widget, `_css` map, `_updateCssProvider()` rebuilds `*{attr:value;...}`
- EM: `dom["style"].set(attr, value)` directly
- `widget->addCss("attr:value")` — splits on `:`, stores in map (GTK) or sets style (EM)
- `widget->addCssClass("name")` / `removeCssClass("name")`

## Async / Threading Rules
- `ml::app()->queue(cb)` — GTK: Glib::Dispatcher; EM: JS event loop (synchronous)
- `ml::app()->execAsync(torun, onfinished)` — `torun` on pool, `onfinished` queued to main
- **NEVER** touch GUI from non-main thread — wrap in `app()->queue()`
- `GuiEvents` wraps `Events` to automatically queue all `emit()` to main thread

## Entry Macros
```cpp
ENTRY_GET_SET(entryVar)       // string entries: value(), setValue(string/double), text(), setHelp(→placeholder)
NB_ENTRY_GET_SET(entryVar)    // numeric entries: value(), setValue(double/string), setRange, setPrecision, setStep
```

---

# CONSTRAINTS

- **NEVER** construct widgets with `new`/`make_shared`/stack — only `create*()` factory methods (checker asserts)
- **NEVER** construct windows directly — only `app->createWindow<T>()`/`createDialog<T>()`
- **NEVER** call `widget->setWindow()` directly — only `append()`/`prepend()`/`setChild()` trigger it via checker
- **NEVER** edit `*_gen.h` files
- **NEVER** perform GUI operations off main thread — use `ml::app()->queue()`
- `ComposedWidget` subclasses **must** populate `_composed` — `createComposedWidget` asserts on empty
- `AskPropertyDialog::drawProp()` must be called **after** `set()` — has assert
- `GuiBackendCommand::setExec()` is **forbidden** (asserts false) — use `setProcessCommand()`
- `GuiCommand::setConfirm(true)` must be called **before** `setExec()` — asserts if called after
- `Widget` constructor itself asserts `can-construct-widget` checker

---

# CONTEXT INJECTIONS

## EventInfos struct
```cpp
struct EventInfos {
    double x, y, dx, dy, mvtx, mvty;
    int click_numbers = -1;
    unsigned int keyval, keycode;
    std::string key;
    bool preventDefault = true;
    bool ctrl=false, alt=false, shift=false, super=false;
    bool visible=true;
    double width=0, height=0;
    Event type = NONE;
    void stopPropagation(); // sets app stopEventPropagationMap[type]=true, queues reset
};
```

## Event Enum
`NONE, CLICK, DOUBLE_CLICK, MOUSE_ENTER, MOUSE_LEAVE, MOUSE_MOVE, MOUSE_UP, MOUSE_DOWN, LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN, MIDDLE_UP, MIDDLE_DOWN, KEY_DOWN, KEY_UP, WHEEL, FOCUS, UNFOCUS, CHANGE, VALID, SHOWN, HIDDEN, RESIZE, DRAG_START, DRAG_END, DRAGGING`

## HAlignment / VAlignment
`HAlignment: FILL, LEFT, RIGHT, CENTER, BASELINE`  
`VAlignment: TOP=1, BOTTOM, VCENTER`

## DrawType Enum
`AUTO, LABEL, ENTRY, MULTILINE_ENTRY, SLIDER, PROGRESS, CHECKBOX, SWITCH, SPINBUTTON, TOGGLEBUTTON, PASSWORD, COMBOBOX, FILE_PATH, DIR_PATH, DATE, TIME, DATE_TIME, COLOR_BUTTON, COLOR_PICKER`

## Property Types
```cpp
BoolProperty(name, value=0, min, max, desc)
IntProperty(name, value=0, min, max, desc)
FloatProperty(name, value=0, min, max, desc)
DoubleProperty(name, value=0, min, max, desc)
StringProperty(name, value="", desc)
EnumProperty(name, value="", desc, choices={})  // extends StringProperty, isEnum()=true
ColorProperty(name, desc="", value=Color<double>)  // isColor()=true
```
Create via: `ml::app()->props().create<T>(args...)` — returns `T*` (owned by PropertiesManager)  
Destroy via: `ml::app()->props().destroy(prop*)`  
`prop->set(std::any value, Observer* observer=nullptr, bool preventUpdate=false)`  
`prop->value()` → typed; `prop->asAny/asInt/asFloat/asDouble/asBool/asString()`  
`prop->addOnUpdate(f)` / `prop->addOnValid(f)` — callbacks on change/enter  
`prop->widgetsConnected()` → `Vec<shared_ptr<Box>>` (UI containers)  
`prop->hide()` / `prop->show()` — hides/shows all connected UI boxes  
`prop->focus()` — focuses the input widget in connected UI  

## App Singleton — Key API
```cpp
ml::app()                                              // global App* (assert if null)
app->createMainWindow<T>(parent, id)                   // creates + setMain()
app->createWindow<T>(parent, id)
app->createDialog<T>(parent, id)
app->createOrShowWindow<T>(&ptr, parent, id)
app->cmds().createCommand<GuiCommand>(name, id)        // returns shared_ptr<GuiCommand>
app->cmds().command(id)                                // returns shared_ptr<Command>
app->props().create<T>(args...)                        // returns T*
app->props().createGroup({prop1, prop2, ...})          // returns PropertyGroup*
app->props().destroy(prop*)
app->menusFactory().create<M>(id, name)                // returns shared_ptr<M>
app->menusFactory().menus()                            // unordered_map<string, shared_ptr<Menu>>
app->panels().create(id, [](Panel*p){...})             // returns PanelInfos*
app->widgetsFactory() / windowsFactory() / menusFactory()
app->queue(cb)                                         // run on GUI thread
app->setTimeout(cb, ms) -> size_t id
app->setInterval(cb, ms, nb=-1, onfinished=0) -> int id
app->removeTimeout(id) / removeInterval(id)
app->execAsync(torun, onfinished)
app->execAsync(runningMsg, torun, finishedMsg, onfinished)  // sets status bar infos
app->info/warning/error(message, parent) -> shared_ptr<XxxDialog>
app->confirm(message, parent) -> shared_ptr<ConfirmDialog>
app->ask(prop*, message, parent) -> shared_ptr<AskPropertyDialog>
app->ask(PropertyType, name, message, parent) -> shared_ptr<AskPropertyDialog>
app->ask(PropertyGroup*, message, parent) -> shared_ptr<AskPropertyGroupDialog>
app->work(message, parent) -> shared_ptr<WorkDialog>
app->progress(message, parent) -> shared_ptr<ProgressDialog>
app->message<T>(message, parent) -> shared_ptr<T>
app->openFile(title, dir, cb) / openFiles / openFolder / openFolders / saveFile
app->isDarkTheme() -> bool
app->paths().path(relative) -> string (absolute path, respects root)
app->paths().libdata() -> string (icons, CSS data dir: root + "/data")
app->focused() -> Window*         // currently focused window
app->focusedWidget() -> Widget*   // currently focused widget
app->setFocused(Window*)
app->setCursor(name)              // sets cursor on all windows
app->setClipboardText(text) / copyToClipboard(text)
app->clipboardText() -> string
app->windowFromId(id) -> Window*  // nullptr if not found
app->windowExists(id) -> bool
app->windows() -> unordered_map<string, shared_ptr<Window>>&
app->checker().set(key, bool) / check(key)
app->events()  -> Events& (app-level events: "quit")
app->setAbout(string)
app->quit()
```

## Window Layout Structure
```
Window
└── _content (Box, "content")
    ├── _head (Box, "head", HORIZONTAL)
    ├── _body (Box, "body", VERTICAL)
    │   ├── _menuBar (MenuBar) → wraps Box
    │   └── _main (Scrollable, "main") ← primary content
    └── _foot (Box, "foot", HORIZONTAL)
        ├── _footLabel (Label, lazy)
        └── _footSpinner (Spinner, lazy)
```
Override `Window::init()` → call `Window::init()` first, then use `_main->createX()`.

## Window Key API
```cpp
win->show() / hide() / toggle()
win->setTitle(string) / title()
win->setSize(w,h) / setWidth / setHeight / fitToContent()
win->setChild(shared_ptr<Widget>)    // replaces window content
win->addEventListener(event, cb)     // delegates to _content
win->showMenu(id)                    // shows menu popover at mouse pos
win->mousePos() -> math::vec2d
win->setInfos(string)                // sets foot label
win->setWorking(bool)                // shows/hides foot spinner
win->setInfosFromCommand(GuiCommand*)
win->createBackendCommand(process, fn, args, cb)
win->hideOnClose(bool) / doHideOnClose()
win->destroy()                       // removes from app + destroys impl
win->addOnClose(cb) / addOnHide(cb)
win->createCommander() -> Commander*
win->createCommanderFromAppCmds() / createCommanderFromThisWindowCmds()
win->showCommander()
win->addKeybind(string, fn->bool)    // fn returns true = consumed
win->removeKeybind(string) -> bool
win->cmds()                          // per-window CommandsManager
win->menu(id, name) -> Menu*         // create+add to menubar if needed
win->pop(popover, sx, sy, px, py)    // show popover at mouse pos
win->createPopover() -> Popover*
win->loadMenusFromFile(path) / loadMenusFromData(json)
win->serialize() / deserialize(json)
win->state() -> WindowEventState& {x,y,alt,ctrl,shift,meta,key}
win->visible() -> bool
win->id() -> string
win->stayHiddenFirstRun() / setStayHiddenFirstRun(bool)
```

## Box Key API
```cpp
box->append(shared_ptr<Widget>) / prepend(...)
box->removeChild(shared_ptr<Widget>) / removeChild(Widget*) / removeChild(ComposedWidget*)
box->setOrient(Orient::VERTICAL/HORIZONTAL)
box->setSpacing(int) / spacing()
box->clear()                          // removes all children, frees memory
box->children() -> Vec<shared_ptr<Widget>>&
box->composedChildren() -> Vec<shared_ptr<ComposedWidget>>&
box->childIndex(Widget*) -> int       // -1 if not found
box->child<T>(size_t i) -> shared_ptr<T>  // dynamic_cast, nullptr if wrong type
box->childrenCount() -> size_t
box->swap(i, j) / swap(Widget*, Widget*)
box->moveChildTop(Widget*) / moveChildBottom(Widget*)
box->containsChild(Widget*) -> bool
box->appendProp<Prop>(prop*, DrawType) -> shared_ptr<PropertyWidget<Prop>>
box->appendComposedProp<Prop>(prop*, DrawType) -> shared_ptr<ComposedPropertyWidget<Prop>>
box->appendPropBaseClass(Property*) -> shared_ptr<Box>
box->appendPropertyGroup(PropertyGroup*) -> shared_ptr<Box>
box->appendEnumProp(EnumProperty*) -> shared_ptr<ComposedPropertyWidget<EnumProperty>>
box->appendColorProp(ColorProperty*, DrawType) -> shared_ptr<ComposedPropertyWidget<ColorProperty>>
box->appendCommand(Command*/id, overrideText) -> shared_ptr<Button>
box->createIcon(name) -> shared_ptr<Image>      // from libdata/images/icons/name.png, 24px
box->createIconFromPath(path) -> shared_ptr<Image>
box->createSeparator() -> shared_ptr<Box>
box->searchStr() -> string  // recursive text content of children
```

## Scrollable Key API
```cpp
scrollable->content() -> Box&          // the inner Box
scrollable->append/prepend/removeChild (delegates to _box)
scrollable->setOrient(Orient)
scrollable->scrollDown/Up/Left/Right(double)
scrollable->scrollX() / scrollY() -> double
scrollable->addOnXScroll(cb) / addOnYScroll(cb)
// All create*() methods available, delegate to content()
```

## AbsoluteBox (Overlay) API
```cpp
abox->append(shared_ptr<Widget>)      // adds as overlay layer
abox->prepend(...)
abox->removeChild(...)
abox->setBackground(Widget*)          // sets base/background layer
abox->removeBackground()
abox->sendToFront(Widget*) / sendToBack(Widget*)
abox->moveDepth(Widget*, unsigned int x)  // x=0 is front
// GTK: Gtk::Overlay; EM: position:relative + position:absolute children
```

## Fixed API
```cpp
fixed->append(shared_ptr<Widget>)
fixed->moveChild(Widget*, double x, double y)  // set absolute position
fixed->widgetPos(Widget*) -> geometry::Point<double>
fixed->removeChild(...) / clear() / containsChild() / childIndex()
```

## GuiCommand Usage
```cpp
auto cmd = app->cmds().createCommand<GuiCommand>("Name", "id");
// OR per-window: win->cmds().createCommand<GuiCommand>("Name", "id")
cmd->setExec([](const std::any& args){ /* main thread */ });
cmd->setKeybind("ctrl s");    // format: "ctrl s", "alt F4", "Return", "Escape"
cmd->setHelp("description");
cmd->setConfirm(true);        // MUST be before setExec()
cmd->setBefore([](const std::any&){ /* before exec, sets wait cursor */ });
cmd->setAfter([](const std::any&){ /* after exec, resets cursor */ });
cmd->toQueue()                // Vec<function<void()>> — queued after _after
cmd->buttons()                // Vec<shared_ptr<Button>> linked to this cmd
cmd->exec() / exec(std::any args)
// exec() flow: check() → _before(args) → queue(_exec(args) + _after(args) + toQueue items)
```

## AsyncGuiCommand
```cpp
auto cmd = app->cmds().createCommand<AsyncGuiCommand>("Name", "id");
cmd->setExec([](const std::any&){ /* runs on thread pool */ });
// exec() flow: _before → execAsync(runningMsg, _exec, finishedMsg, _after)
cmd->async() -> true
```

## GuiBackendCommand
```cpp
auto cmd = app->createBackendCommand(process*, "fnName", json_args, cb, onetime=false);
// OR: cmd->setProcessCommand(process*, fn, args, cb, onetime)
// OR: cmd->setProcessCommand(process*, fn, [](){ return json{}; }, cb, onetime)  // dynamic args
cmd->addCallback(cb, onetime=false)
cmd->execJson(json args)      // bypasses getjsonArgs lambda
cmd->setSync(true)            // force sequential backend execution
cmd->waiting() -> bool        // true between exec() and response
// setExec() is FORBIDDEN (asserts)
// cb always queued to main thread by internal _cb
```

## Menu / MenusFactory API
```cpp
auto menu = app->menusFactory().create<SearchableMenu>(id, name);
menu->addButton(text, onClick, keybind) -> shared_ptr<MenuButton>
menu->addCommand(Command*, overrideArgs, overrideText) -> shared_ptr<MenuButton>
menu->addSeparator()
menu->removeButton(text)
menu->clear()
menu->show() / hide()
menu->id() / name() / setName()
menu->buttons() -> Vec<shared_ptr<MenuButton>>&
menu->popover() -> shared_ptr<Popover>
menu->events()  // emits: "shown"

// SearchableMenu adds search Entry above buttons, valid() executes first match
// On Window:
win->menu(id, name) -> Menu*    // creates if not exists, adds to menubar
win->showMenu(id)               // shows at mouse position

// MenuBar
win->menuBar() -> shared_ptr<MenuBar>
_menuBar->addMenu(id)
_menuBar->containsMenu(id) -> bool
```

## Tabs API
```cpp
auto tabs = std::make_unique<Tabs>(box/scrollable);
auto tab = tabs->createTab("Label") -> TabButton*
tab->body() -> shared_ptr<Box>   // the tab content area
tabs->show(index)
tabs->hideAll()
tabs->active() -> TabButton*
tabs->activeIdx() -> int
tabs->setActiveIdx(index)
tabs->removeTab(TabButton*) / removeTab(string label)
tabs->header() -> shared_ptr<Box>
tabs->body() -> shared_ptr<Scrollable>
```

## Paned / Panel API
```cpp
auto paned = new Paned(box);
paned->createFirst() / createSecond() -> Panel*
paned->createFirstFromInfos(PanelInfos*) / createSecondFromInfos(PanelInfos*)
paned->setOrient(HORIZONTAL/VERTICAL)
paned->setRatio(float 0-1)
paned->split() / merge() / swap() / changeOrient()
paned->removeFirst() / removeSecond()
paned->active() -> Panel*
panel->drawFromInfos(PanelInfos*)
panel->split()                   // creates nested Paned
panel->box() -> shared_ptr<Box>

// PanelsManager
app->panels().create(id, [](Panel* p){ p->box()->createLabel("..."); })
app->panels().get(id) -> PanelInfos*
app->panels().has(id) -> bool
```

## Collapsable API
```cpp
auto c = box->createComposedWidget<Collapsable>(box, "Title", collapsed=false);
// cast: (Collapsable*)c.get()
c->body() -> shared_ptr<Box>    // content area
c->header() -> shared_ptr<Box>
c->label() -> shared_ptr<Label>
c->collapse() / expand() / toggle()
c->collapsed() -> bool
```

## List<T, Dynamic, MaxDrawn> Template
```cpp
// T requirements: gui() -> Widget*, searchStr() -> string
// If MaxDrawn=true: draw() method required, called lazily
auto list = box->createComposedWidget<List<T, Dynamic, MaxDrawn>>(box, search=true, selectionType, maxDrawn=50);
list->createElmt(args...) -> T*
list->removeElmt(idx) / removeElmt(T*)
list->select(idx/T*) / unselect / selectAll / unselectAll / selectRange
list->replaceSelection(T*)
list->selected(T*) -> bool
list->selected() -> Vec<unsigned int>
list->elmts() -> Vec<shared_ptr<T>>&
list->listbox() -> Box*          // the inner content Box for appending
list->list() -> shared_ptr<ListWidget>
list->setSelectionType(NONE/SINGLE/MULTIPLE)
list->clear()
list->addOnAddElmt(cb) / addBeforeRemoveElmt(cb)
list->search() -> StringProperty&
list->hideSearch() / showSearch()
list->maxDrawn() -> int (-1 if not MaxDrawn)
list->runOnSelected(cb) / runOnUnselected(cb) / runOnDrawn(cb) / runOnVisible(cb)
list->moveSelection(offset) / extendSelection(offset) / invertSelection()
list->lastSearchedMatched() -> Vec<unsigned int>
```

## LabelList Convenience
```cpp
LabelList<Dynamic=false>(box/scrollable, search=true)
// items: LabelListItem<Dynamic> — gui()=Label*, text(), searchStr()
list->remove(labelText)
list->contains(labelText) -> bool
```

## VerticalTable / Model
```cpp
auto model = std::make_shared<VerticalTableModel>();
model->setAttributes({{name, PropertyType}, ...})
model->addAttribute({name, type}) / removeAttribute(name) / removeAttribute(idx)
model->addToData(json) / prependToData / setData / removeFromData(idx)
model->removeFromDataIf(cb) / modifyDataIf(cb, newdata)
model->data() -> Vec<json>& / size() -> size_t
// Notify events: attributes-changed, attributes-added, attributes-removed,
//   attributes-removed-idx, data-changed, data-added, data-prepended,
//   data-removed, data-modified

auto vtable = box->createComposedWidget<VerticalTable>(box);
vtable->linkToModel(shared_ptr<VerticalTableModel>)
vtable->removeModel()
vtable->events() -> Events&  // row-clicked(VerticalRow*), header-clicked(Label*),
                              // row-right-clicked, row-middle-clicked,
                              // header-right-clicked, header-middle-clicked, row-modified
vtable->setRowData(idx, json)
vtable->oneRowHeight() / allRowsHeight() / rowTop(idx/Box*)

struct VerticalRow {
    VerticalTableModel* model;
    Box* row;              // the GTK/DOM row widget
    int model_index;       // index in model data
    int gui_index;         // index in drawn rows
    const json& data();    // model->data()[model_index]
};

// VerticalSelectableTable + VerticalSelectableTableModel for click-to-select
```

## Commander Widget
```cpp
auto cmd = win->createCommander() -> Commander*
// OR
auto cmd = win->createCommanderFromAppCmds() -> Commander*
auto cmd = win->createCommanderFromThisWindowCmds() -> Commander*
win->showCommander()     // shows at mouse pos in popover

// Manual creation:
auto cmd = box->createComposedWidget<Commander>(box).get();
cmd->addCommand(Command*) / addCommand(id, CommandsManager*)
cmd->addAllCommands(CommandsManager*) / addAllCommands(Window*) / addAllCommands(App*)
cmd->removeCommand(Command*) / removeCommands(id) / removeCommand(id, mgr)
cmd->clear()
cmd->active() -> CommandButton*
cmd->activeCommand() -> Command*
cmd->moveActiveCommandButton(int offset)
cmd->setCommandsScores(json)  // {cmd_id: float_score} boosts search rank
cmd->events()  // "valid"(Command*), "changed", "context"(Command*)
cmd->setDoNothing(bool)  // if true, doesn't exec on valid
```

## ColorPicker / ColorButton
```cpp
// ColorPicker (RGBA sliders + preview):
auto cp = box->createComposedWidget<ColorPicker>(box).get();
cp->set(Color<double>) / color() -> Color<double>&
cp->css() -> string  // "* { background-color: rgba(...); }"
cp->setValue(string json) / setValue(double) / setValue(Color<double>) / setValue(json)
cp->addEventListener(CHANGE, cb)  // fires on any slider change
cp->events() -> Events&           // "change" with Color<double> data

// ColorButton (compact button that opens ColorPicker in popover):
auto cb = box->createComposedWidget<ColorButton>(box).get();
cb->color() -> Color<double>&
cb->setValue(Color<double>) / setValue(string) / setValue(json)
cb->events() -> Events&  // delegates to ColorPicker events
```

## TimeSlider / TimeSliderInOut
```cpp
auto ts = box->createComposedWidget<TimeSlider>(box, min, max, current).get();
ts->setMin/setMax/setCurrent(double, sendEvent=true)
ts->events()  // "min-changed", "max-changed", "current-changed" with double data

auto ts = box->createComposedWidget<TimeSliderInOut>(box, min, max, current, start, end).get();
ts->setStart/setEnd(double, sendEvent=true)
ts->start() / end() -> double
// Additional events: "start-changed", "end-changed"
```

## Canvas API
```cpp
auto canvas = box->createCanvas<ml::Canvas>();
// OR: box->createCanvas()  (default type)
canvas->addToDraws([canvas](int w, int h){ /* draw calls here */ }) -> unsigned int idx
canvas->clearDraws() / removeFromDraws(idx)
canvas->redraw()  // triggers GTK queue_draw

// Drawing (must be called inside a draw callback):
canvas->fillRect(x,y,w,h,color) / strokeRect(...)
canvas->fillCircle/strokeCircle(x,y,r,color,lineWidth)
canvas->fillArc/strokeArc(x,y,r,startAngle,endAngle,color,lineWidth)
canvas->drawLine(x1,y1,x2,y2,color,lineWidth)
canvas->fillPolygon/strokePolygon(points, color, lineWidth)
canvas->fillRoundedRect/strokeRoundedRect(x,y,w,h,radius,color,lineWidth)
canvas->drawText(x,y,text,TextStyle,color)  // x,y = top-left corner
canvas->textMetrics(text, TextStyle) -> TextMetrics {x_bearing,y_bearing,width,height,x_advance,y_advance}
canvas->beginPath/closePath/moveTo/lineTo/arc/fill/stroke(...)
canvas->drawImage(path,x,y,pivotx,pivoty,scaleX,scaleY)

struct TextStyle { double size=12; bool bold,italic,underline,oblique; string family="sans-serif"; };
// Color<double>: r(),g(),b(),a() → [0,1] range
```

## MdView
```cpp
auto md = box->createComposedWidget<MdView>(box).get();
md->setMdText(string) / setText(string) / setValue(string)
md->text() / mdText() / value() -> string
md->setSelectable(bool)
md->addEventListener(event, cb)
```

## Video / VideoPlayer
```cpp
auto video = box->createComposedWidget<Video>(box, filepath).get();
video->setPath(filepath)
video->play() / pause() / toggle() / playing() -> bool
video->currentFrame() / currentTime() / duration()
video->nextFrame() / prevFrame()
video->seekToFrame(long) / seek(double time) / seekToRatio(double)
video->setSpeed(double) / setVolume(double)
video->setDefaultEvents()    // wires keyboard+mouse drag controls
video->events()              // "frame-changed"(long), "played", "paused",
                             // "metadata-changed", "speed-changed"(double), "volume-changed"(double)
video->frameCount() / frameIdxFromTime(double) / timeFromFrameIdx(long)
video->loaded(long frame) -> bool
video->frameDuration() -> double (ms)

// VideoPlayer wraps Video + TimeSliderInOut:
auto vp = box->createComposedWidget<VideoPlayer>(box, filepath).get();
vp->play/pause/toggle/seek/seekToFrame/seekToRatio...
vp->slider() -> TimeSliderInOut*
vp->events() -> delegates to video events
```

## WebView
```cpp
auto wv = box->createWebView();
wv->setURI("https://...") / readFile(path)
```

## Searchable / SearchableMenu
```cpp
// SearchableMenu: Menu with built-in search Entry
auto menu = app->menusFactory().create<SearchableMenu>(id, name);
// pressing Enter in search executes first match
// Searchable mixin:
class MyClass : public SomeWidget, public Searchable {
    void init() { createSearchInput(someBox); }
    Vec<shared_ptr<SearchableWidget>> searchableWidgets() override { ... }
    void valid(const string& searched) override { ... }
};
// SearchableWidget interface: asText(), searchMatch(), searchDontMatch()
```

## ChangeChecker
```cpp
ChangeChecker cc(intervalMs=5000);
cc.setGetDataFunction([](){ return json_snapshot; });
cc.setOnchange([](){ /* fired when data changes */ });
cc.start() / stop()
cc.changed() -> bool  // compares prev vs current JSON
cc.started() -> bool
```

## Keybind Format & Matching
```cpp
// Format: "ctrl s", "ctrl shift S", "alt F4", "Return", "Escape", "super k"
// keybinds::match(keybind, eventInfos, focusedType) -> bool
// focusedType: NONE, NON_EDITABLE, ONELINE_EDITABLE, MULTILINE_EDITABLE
// In editable contexts: ctrl/alt/super combos pass through, plain keys blocked
// Exception: Escape always passes; Up/Down pass in ONELINE_EDITABLE
keybinds::label("ctrl s") -> "Ctrl S"  // human-readable
```

## ml::Vec<T>
```cpp
// Wraps std::vector<T>, extra API:
vec.push(x)          // alias push_back
vec.prepend(x)       // insert at front
vec.remove(x)        // remove by value (first match)
vec.removeByIndex(i)
vec.contains(x) -> bool
vec.first() / last() -> T&
vec.move(from, to)   // move element
vec.setPosition(x, pos)  // place element at index
vec.swap(i, j)
vec.length() -> size_t  // alias size()
vec.vec               // exposes underlying std::vector<T>
// Iterator: begin()/end() available
```

## AnyData (Widget::_data)
```cpp
widget->data().add(ptr, "key")    // store any typed pointer
widget->data().get<T*>("key")     // returns Ret<T*>
// Used by PropertyWidget to store "label", "input", "button" refs in box->data()
```

## Ret<T> utility
```cpp
struct Ret<T> { bool success; T value; string message; };
ml::ret::success(value) / ml::ret::fail<T>(message)
```

## em:: Namespace (Emscripten DOM utilities)
```cpp
em::body() / em::head() / em::dom() / em::window()
em::createElement(tag) -> emval         // auto-assigns unique id
em::newNode(parent, tag, html, classes, id) -> emval
em::show/hide/remove(dom)
em::append/prepend/insertAfter/insertBefore(parent, child, ref)
em::width/height/x/y(dom) -> numeric
em::innerWidth/innerHeight() -> unsigned int
em::addClasses/removeClasses/toggleClasses/containsClasses(dom, "cls1,cls2")
em::setCss(dom, attr, value) / addCss(dom, css_string)
em::setFocusable(dom, bool) / hovered(dom) -> bool
em::fontSize(dom) -> float
em::scrollBy/scrollTop/scrollLeft(dom, ...)
em::move(dom, x, y)         // sets left/top style + caches position
em::position(dom) -> geometry::Point<double>
em::addEventListener(dom, Event, mouseCallback)    // EmscriptenMouseEvent*
em::addEventListener(dom, Event, keyCallback)      // EmscriptenKeyboardEvent*
em::addEventListener(dom, string, jsEventCallback) // generic JS event
em::addEventListener(dom, Event, voidCallback)     // CHANGE/VALID
```

## Dialog Hierarchy
```
Dialog (Window, hideOnClose=false)
└── MessageDialog (setMessage, _ok button, _foot, events: "ok")
    ├── IconMessageDialog (adds icon image, _message_box)
    │   ├── InfoDialog (_iconName="info")
    │   ├── WarningDialog (_iconName="warning")
    │   └── ErrorDialog (_iconName="error")
    └── ConfirmDialog (adds _cancel button, events: "ok"+"cancel")
        ├── AskPropertyDialog (set(prop*), drawProp(), value() -> any)
        └── AskPropertyGroupDialog (set(PropertyGroup*), drawProp())
    WorkDialog (spinner, cancel button, events: "cancel", setState(LOADING/NOT_LOADING))
    ProgressDialog (progress bar, cancel button, setProgress(double), events: "cancel")
```

## Window::createBaseUi() Structure Notes
- `_menuBar` created via `WidgetsFactory::create<MenuBar>(_body.get())` — NOT via `createComposedWidget`
- `MenuBar` wraps a `Box`, added to `_body` before `_main`
- `_main` is a `Scrollable` with orient `VERTICAL`
- `_foot` has `setHExpand(true)`, `setVExpand(false)`, `setHAlign(RIGHT)`, `setVAlign(BOTTOM)`

## CommandButton (not ComposedWidget)
```cpp
CommandButton cb(box, cmd_id_or_cmd_ptr);
cb.draw()    // must call explicitly — deferred rendering
cb.show() / hide() / remove()
cb.setCommand(Command*)
cb.events()  // "executed", "context"
cb.button() -> shared_ptr<Box>
cb.cmd() -> Command*
```

## IconButton (ComposedWidget)
```cpp
auto ib = box->createComposedWidget<IconButton>(box, "icon-name", "label", inverted=false, reversed=false).get();
ib->btn() -> shared_ptr<Box>   // the container button box
ib->icon() -> shared_ptr<Image>
ib->label() -> shared_ptr<Label>
// reversed=true: label before icon
// inverted=true: icon CSS filter:invert(1)
```

## Image Widget
```cpp
auto img = box->createImage();          // bool icon=true (Gtk::Image, square)
auto img = box->createImage(false);     // Gtk::Picture (aspect ratio preserved)
img->load(filepath, cb=nullptr)         // async (GTK: ResourcesManager cache; EM: src=)
img->loadFromMemory(vector<uchar>, ImageFormat)
img->invert()                           // adds "invert" CSS class
img->setWidth(int)                      // GTK: set_pixel_size if icon
img->state() -> ImageState              // IMG_NORMAL, FILE_NOT_FOUND, WRONG_FORMAT
img->empty() -> bool
```

## Popover
```cpp
// Created via box->createPopover() or win->createPopover()
// On GTK: Gtk::Popover (popup/popdown), no arrow, auto-attached to parent
// On EM: position:fixed div
pop->show() / hide()
pop->setPosition(float x, float y)
pop->setAutoHide(bool) / setModal(bool)
pop->content() -> shared_ptr<Scrollable>   // popover's content
pop->setChild(shared_ptr<Widget>)
pop->redraw()
// All create*() methods delegate to content()
// GTK: show() remembers focus, restores on close
```