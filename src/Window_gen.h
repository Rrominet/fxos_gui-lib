//This is a generated file, don't change it manually, it will be override when rebuild.

std::shared_ptr<Box> content(){return _content;}


std::shared_ptr<Box> head(){return _head;}


std::shared_ptr<Box> body(){return _body;}


std::shared_ptr<Scrollable> main(){return _main;}


std::shared_ptr<Box> foot(){return _foot;}


std::shared_ptr<Label> footLabel(){return _footLabel;}


std::shared_ptr<Spinner> footSpinner(){return _footSpinner;}


bool visible(){return _visible;}


WindowEventState& state(){return _state;}
const WindowEventState& state() const {return _state;}


std::shared_ptr<MenuBar> menuBar(){return _menuBar;}
const std::shared_ptr<MenuBar> menuBar() const {return _menuBar;}


ml::CommandsManager& cmds(){return _cmds;}
const ml::CommandsManager& cmds() const {return _cmds;}


std::string id(){return _id;}
const std::string& id() const {return _id;}


bool stayHiddenFirstRun(){return _stayHiddenFirstRun;}
const bool stayHiddenFirstRun() const {return _stayHiddenFirstRun;}
void setStayHiddenFirstRun(bool stayHiddenFirstRun){_stayHiddenFirstRun = stayHiddenFirstRun;}

