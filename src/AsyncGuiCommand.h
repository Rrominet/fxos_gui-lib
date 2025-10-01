#include "./GuiCommand.h"

//TODO
//Launch the _exec function on a separate thread via a thread pool. (redefining the _exec function when using setExec(...))
//Put the good cursor.
//add a state system to be able to check if a command is in running mode. (NOT_STARTED, RUNNING, PAUSED, CANCELED, DONE)
//add a specefic list for the running commands. (this list will be modified in the _before and _after function)
//Create the ProgressDialog (and add a _useProgressDialog Property t oshow it or not)
//Show that an action is taking place in the footer of the main window with its name and a turning spinner.
//Add a Popover that show all Commands being executed. accessible from the main window footer. (visible only if there is more that one command that is in running mode...)
//add the possibility for the user to cancel the running commands at any time.
//add the possibility to react to the user starting, pausing, canceling and finishing the running commands (the Events class seams appropriate here - need to be execute from mainthread.).
//
//add the possibility to add the option to pause and resume the running command at a given point
//add the possibility to the Command to display notification at certain event (starting, pausing, etc...)
//and so create the NotificationWidget class and the Window::notif(...) & App::notif(){_focused->notif();} function
