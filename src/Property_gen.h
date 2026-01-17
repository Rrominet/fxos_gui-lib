//This is a generated file, don't change it manually, it will be override when rebuild.

std::string name(){return _name;}
const std::string& name() const {return _name;}
void setName(const std::string& name){_name = name;}

std::string description(){return _description;}
const std::string& description() const {return _description;}
void setDescription(const std::string& description){_description = description;}

ml::Vec<std::function<void()>>& onUpdate(){return _onUpdate;}
const ml::Vec<std::function<void()>>& onUpdate() const {return _onUpdate;}


ml::Vec<std::function<void()>>& onValid(){return _onValid;}
const ml::Vec<std::function<void()>>& onValid() const {return _onValid;}


ml::Vec<std::shared_ptr<Box>>& widgetsConnected(){return _widgetsConnected;}
const ml::Vec<std::shared_ptr<Box>>& widgetsConnected() const {return _widgetsConnected;}


std::unordered_map<std::string,std::any>& attrs(){return _attrs;}
const std::unordered_map<std::string,std::any>& attrs() const {return _attrs;}


