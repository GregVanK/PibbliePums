#include "Inventory.h"




namespace GEX {
	Inventory::Inventory()
	{
	}
	Inventory::Inventory(std::list<Food> inventory)
	{
	}

	void Inventory::addFood(Food f)
	{
		if (_items.size() <= 5) {
			_items.push_back(f);
		}
	}

	Food Inventory::removeFood(int index)
	{
		Food returnFood;
		if (_items.size() > index) {
			std::list<Food>::iterator it = _items.begin();
			std::advance(it, index);
			returnFood = *it;
		}
		return returnFood;
	}


}
