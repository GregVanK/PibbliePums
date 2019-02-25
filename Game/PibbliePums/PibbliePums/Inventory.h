#pragma once
#include <list>
#include "Food.h"
namespace GEX {
	class Inventory
	{
	public:
		Inventory();
		Inventory(std::list<Food> inventory);
	public:
		void addFood(Food f);
		Food removeFood(int index);
		std::list<Food> getItems() { return _items; }
	private:
		std::list<Food> _items;
	};
}

