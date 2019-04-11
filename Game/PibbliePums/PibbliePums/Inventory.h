#pragma once
#include <list>
#include "Food.h"
/*
*@author: Greg VanKampen
*@file: Inventory
*@description: Special food container class
*/
namespace GEX {
	class Inventory
	{
	public:
		Inventory();
		Inventory(std::list<Food> inventory);
	public:
		void			addFood(Food f);
		Food			removeFood(int index);
		Food			getFood(int index);
		std::list<Food> getItems() { return _items; }
		int				getSize() { return _items.size(); }
		
	private:
		std::list<Food> _items;
	};
}

