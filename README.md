# fxos_gui-lib (mlgui)

## Goals and philosophy

This shared library written in c++ has 2 principle goals : 
 - Be portable to any backend (for now is fully ported on `GTK4` (via `gtkmm`) and partially on `emscripten` - but has the achitecture to be ported on any backend)
 - Abstract the concept of inputs as GUI (Entry, Button, Label, ...) in something called `Property` and `Command`

> [!NOTE]
> For now, it has only been tested on linux but in the future it should work on any unix system and Windows.

### Portable to any backend

The library works as wrapper around the functions of the backend that you can choose at *build time*.
For now you'll see 2 subfolders into `src/`: 
 - `src/gtk` (backend implementation based on `gtkmm4`)
 - `src/em` (backend implementation based on `emscripten`)

As of today, the backend port on `gtkmm4` is done.
The backend port on `emscripten` is still in progress.

You can add your own bakend re-implementing all the classes and methods that are present in `src/gtk` folder.

> [!NOTE]
> Even if the architecture to implement any backend is here, there is still a lot of work to do to be able to really do it in practice.  
> For now, consider that only the `gtkmm4` backend is implemented, stable and running correctly.

### Properties and Commands

#### Properties
The concept is simple : 
The developer do not have to draw all the interface by himself. (he still can if he wants to).

For example, in a classic GUI frameworks, you would have something like this to create a text input : 
(It's pseudo code and not based on a real lib but you get the idea)
```c++
auto container = parent->createBox();
auto label = container->createLabel("Name : ");
auto input = container->createEntry("", "Your name here...");

// and if you want to get the value of the name you would do : 
auto name = input->getValue();
```

This system has a lot of boilerplate : 
 - If you need to draw the same data at 2 different places, you basicly need to duplicate your code.
 - A lot of data a drawn very similary (often a label and some kind of `entry`), and so this lead to a lot of really similar and repetitive code.
 - And finally this force the developer to think about every details of the GUI (which can be cool if wanted) but often we only want a standard GUI with a visual logic that has already beed done millions of times.

This is where the `Property` system save the day !

The idea is to create a Property that present the value that a user can read and/or modify.
And this property can be `drawn` any where on your GUI even at multiple places in different forms.

Here how it works in syntax with `fxos_gui-lib` :
```c++
//this code create the property but does not actually show it in the gui
auto p1 = ml::app()->props().create<StringProperty>("Name", "Value as default", "What is your name ?");

//to show it in the gui, you need to add it in a 'container' like this :
your_container->appendProp(p1);

//and you can even add it in a second container elsewhere in the gui and the property will keep the inputs synced : 
another_container->appendProp(p1, MULTILINE_ENTRY); //here for example we use a multiline entry to display the prop (before is was a single line one by default)
```

With this system you don't worry about your GUI details anymore, you can focus on the logic of your app.
That being said, with `fxos_gui-lib`, you also have access to the buildings blocks like Input, Button, etc if you want more fine control.
Using the `Property` system is not mendatory.

#### Commands

The concept is really similar but it's for `actions` and not information.

Once again, here how you would create an action in a classic GUI framework :
```c++
auto container = parent->createBox();
auto button = container->createButton("Click me !");
button->addOnClick(your_on_click_function);
```

The problem with this is that your action is completely decoupled from the logic of your app.  
No Undo/Redo logic possible, no Keybind system that can be linked to it and if you want this action to be available in multiple places, you need to duplicate your code.

With the `Command` system, you can create a command that can be executed from anywhere in your app.

Here is the syntax in `fxos_gui-lib` :
```c++
auto cmd1 = ml::app()->cmds().create("MyCommand", "my-command-id");
cmd1->setHelp("Description of the command"); //tool tip buble in the gui
cmd1->setExec(your_cmd_function);
cmd1->setReverse(your_reverse_cmd_function); //to be able to undo/redo automaticly
cmd1->setKeybind("ctrl d"); //available in all the app or per window.

//right now, the command only works if the user press the keybind
//But it could be cool if we can draw it in a button or a menu. (or anywhere else)

//Well as a button:
your_container->appendCommand(cmd1.get()) // cmd1 is a shared_ptr but appendCommand take a raw pointer as arg
//or you can even use the id directly, no need to keep the pointer around.
your_container->appendCommand("my-command-id");

// And in a menu
your_menu->addCommand(cmd1.get());
//or you can even use th id directly
your_menu->addCommand("my-command-id");
```

And of course you can still create a `Button` and use `addEventListner` on it if you want a more fine grained control.
Like the `Property` system, the `Command` system is not mendatory. (but pretty useful :) )

> [!NOTE]
> The `Property` and `Command` system is really close to the philosophy of the *Blender Python API*.

## Installation

This shared lib depends on 2 projects : 
 - [fxmake](https://github.com/Rrominet/py-utils/tree/main/build) (my c++ builder because `cmake` sucks - lol)
 - [cpp-utils](https://github.com/Rrominet/cpp-utils) (my c++ utils lib)

For the GTK4 backend, it depends obviously on `GTK4` but also on `gtkmm4` (bindings for `GTK4` in `c++`).

But don't worry about any of that, because I've made you a little script that install make all for you !
All you have to do in to execute `./build-n-install` as `sudo` and your done.

Alright, here is the full code you need to type from 0 to get this shared lib build and installed on your system : 
```bash
git clone https://github.com/Rrominet/fxos_gui-lib
cd fxos_gui-lib
sudo chmod +x ./build-n-install
sudo ./build-n-install
```

It's that simple.

> [!NOTE]
> For now, this script only works on `debian` based system because it calls `apt` directly.
> But it will very soon be portable accross all the major distros. Stay tuned for that !
>  
> Also, it is planned to add a pre-build binaries system so you don't have to build it yourself.

## Usage

For now, it's really just a lib that is a dependency for all the cpp projects that I'm currently working on that uses a GUI.  
But in a (really short) future, I will write the documentation so you can use it as a shared lib in your own cpp GUI project. (It's already possible, but without documentation it can be a bit hardcore (a))

## TODO

Well, SOOOO MUCH haha !
 - Like test and port it on Windows and IOS.
 - Complete and test the `emscripten` backend. (for a web based GUI rendered with Chrome, Firefox, etc)
 - Make it usable as shared lib in your own cpp projects with a proper documentation on building, linking and using it. 
 - And there is still a lot *widgets* I wish to implement
 - And certainly a lot of others stuffs, we'll see how it goes haha !
