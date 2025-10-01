//This is a generated file, don't change it manually, it will be override when rebuild.

std::string id(){return _id;}
const std::string& id() const {return _id;}


std::string name(){return _name;}
const std::string& name() const {return _name;}
void setName(const std::string& name){_name = name;}

ml::Vec<std::shared_ptr<ml::MenuButton>>& buttons(){return _buttons;}
const ml::Vec<std::shared_ptr<ml::MenuButton>>& buttons() const {return _buttons;}


std::shared_ptr<ml::Popover> popover(){return _popover;}
const std::shared_ptr<ml::Popover> popover() const {return _popover;}


Events& events(){return _events;}
const Events& events() const {return _events;}


