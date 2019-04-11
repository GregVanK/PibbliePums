#include "Inventory.h"
/*
*@author: Greg VanKampen
*@file: Inventory
*@description: Special food container class
*/
namespace GEX {

	Inventory::Inventory() {};
	Inventory::Inventory(std::list<Food> inventory)
	{
	}
	//add food to inventory
	void Inventory::addFood(Food f)
	{
		if (_items.size() <= 4) {
			_items.push_back(f);
		}
	}
	//remove and return food at index
	Food Inventory::removeFood(int index)
	{
		Food returnFood;
		if (_items.size() > index) {
			std::list<Food>::iterator it = _items.begin();
			std::advance(it, index);
			returnFood = *it;
			_items.erase(it);
		}
		return returnFood;
	}
	//return food at index
	Food Inventory::getFood(int index)
	{
		Food returnFood;
		if (_items.size() > index) {
			std::list<Food>::iterator it = _items.begin();
			std::advance(it, index);
			returnFood = *it;
			//_items.erase(it);
		}
		return returnFood;
	}


}
