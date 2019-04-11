#pragma once
#include "Inventory.h"
#include <chrono>
/*
*@author: Greg VanKampen
*@file: ShopData
*@description: Singleton dataholder which contains the shop inventory
*/
namespace GEX {
	class ShopData
	{
	public:

		static ShopData*	getInstance();
		
		Inventory			getInventory();
		void				setInventory(Inventory i) { _inventory = i; }

	private:

		ShopData() {};
		ShopData(ShopData const&) {};
		ShopData& operator=(ShopData const&) {};

		void				generateInventory();
	private:
		static ShopData* _instance;
		Inventory _inventory;
		std::chrono::system_clock::time_point _resetTime;
	};
}
