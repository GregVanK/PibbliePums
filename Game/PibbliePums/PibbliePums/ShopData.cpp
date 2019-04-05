#include "ShopData.h"


namespace GEX {

	ShopData* ShopData::_instance = NULL;

	ShopData * ShopData::getInstance()
	{
		if (!_instance) {
			_instance = new ShopData;
			_instance->generateInventory();
			_instance->_resetTime = std::chrono::system_clock::now() + std::chrono::minutes(5);
		}
		return _instance;
	}

	void ShopData::generateInventory()
	{
		_inventory.addFood(Food::FoodType::Medicine);
		for (int i = 0; i < 4; i++) {
			//generate a random food up to the "last" food type
			Food::FoodType item = static_cast<Food::FoodType>(rand() % (int)Food::FoodType::last);
			_inventory.addFood(item);
		}
	}


	Inventory ShopData::getInventory()
	{
		if (std::chrono::system_clock::now() > _resetTime) {
			generateInventory();
			_resetTime = std::chrono::system_clock::now() + std::chrono::minutes(5);
		}
		return _inventory;
	}
}
