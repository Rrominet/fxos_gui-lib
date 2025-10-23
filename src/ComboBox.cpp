#include "./ComboBox.h"
#include "./Box.h"
#include "./SearchableMenu.h"
#include "./IconButton.h"
#include "enums.h"
#include "./App.h"
#include "./Window.h"
#include "./EventInfos.h"

namespace ml
{
    unsigned combo_box_count = 0;

    ComboBox::ComboBox(Box* parent, const std::vector<std::string>& items) : ComposedInput()
    {
        if (ml::app()->isDarkTheme())
            _btn = std::make_shared<IconButton>(parent, "down-arrow", "", true, true);
        else 
            _btn = std::make_shared<IconButton>(parent, "down-arrow", "", false, true); //ch
        _composed.push_back(_btn.get());
        _menu = ml::app()->menusFactory().create<SearchableMenu>("__combobox_menu_" + std::to_string(combo_box_count));
        combo_box_count++;
        _setEvents();

        this->setItems(items);

        if (items.size() > 0)
            this->setActiveIndex(0);
    }

    void ComboBox::showMenu()const
    {
        ml::app()->focused()->showMenu(_menu->id());
    }

    void ComboBox::_setEvents()
    {
        auto onclick = [this](EventInfos& event)
        {
            this->showMenu();
        };
        _btn->addEventListener(MOUSE_UP, onclick);

        auto onwheel = [this](EventInfos& event)
        {
            if(event.dy<0)
                this->setActiveIndex(this->activeIndex() - 1);
            else 
                this->setActiveIndex(this->activeIndex() + 1);
        };

        _btn->btn()->addEventListener(WHEEL, onwheel);
    }

    void ComboBox::setItems(const std::vector<std::string>& items)
    {
        lg("--------ComboBox::setItems-------------  " << items.size());
        this->clear();	
        for (auto& item : items)
            this->addItem(item);
    }

    void ComboBox::addItem(const std::string& item)
    {
        lg(" -------------CommboBox::addItem-------------  " << item);
        _items.push(item);
        _menu->addButton(item, [this, item]{
                this->setActiveItem(item);
                });
    }

    void ComboBox::removeItem(const std::string& item)
    {
        _items.remove(item);
        _menu->removeButton(item);
    }

    void ComboBox::clear()
    {
        lg(" ---------------  ComboBox::clear ------------- (clearing " << _items.size() << " items)");
        _menu->clear();
        _items.clear();
    }

    void ComboBox::removeItem(unsigned int index)
    {
        _items.removeByIndex(index);
    }

    std::string ComboBox::activeItem() const
    {
        if (_active < _items.size() && _active >= 0 && _items.size() > 0)
            return _items[_active];

        return "";
    }

    int ComboBox::activeIndex() const
    {
        return _active;
    }

    void ComboBox::setActiveItem(const std::string& item)
    {
        _btn->label()->setText(item);
        for (unsigned int i = 0; i < _items.size(); i++)
        {
            if (_items[i] == item)
            {
                _active = i;
                break;
            }
        }

        _execOnChange();
    }

    void ComboBox::setActiveIndex(int index)
    {
        if (_items.size() == 0)
        {
            _active = -1;
            return;
        }

        if (index < 0)
            index = _items.size() - 1;

        else if (index >= _items.size())
            index = 0;

        _active = index;
        _btn->label()->setText(_items[_active]);

        _execOnChange();
    }

    void ComboBox::setValue(const std::string& value)
    {
        this->setActiveItem(value);
    }

    void ComboBox::setValue(double value)
    {
        lg("ComboBox::setValue(" << value << ") (as double) is not possible. Ignored.");
    }

    std::any ComboBox::valueAsAny()
    {
        return std::any(this->activeItem());
    }

    void ComboBox::addEventListener(Event event, const std::function<void(EventInfos&)>& callback)
    {
        if (event == CHANGE)
            _onChange.push_back(callback);
        else 
            _btn->addEventListener(event, callback);
    }

    void ComboBox::setHAlign(HAlignment align)
    {
        _btn->setHAlign(align);
    }

    void ComboBox::setHExpand(bool value)
    {
        _btn->setHExpand(value);
    }

    void ComboBox::_execOnChange()
    {
        for (auto& callback : _onChange)
        {
            EventInfos e;
            callback(e);
        }
    }

    std::string ComboBox::menuId()const{return _menu->id();}
    SearchableMenu* ComboBox::menu()const{return _menu.get();}
}
