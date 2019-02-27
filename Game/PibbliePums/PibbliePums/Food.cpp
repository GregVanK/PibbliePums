#include "Food.h"



GEX::Food::Food(FoodType type):
	_type(type)
{
	//give states based on type
	switch (_type) {
	case FoodType::Burger:
		_happiness = 3;
		_fullness = 2;
		_weight = 3;
		_price = 20;
		_name = "Burger";
		break;
	case FoodType::Carrot:
		_happiness = 1;
		_fullness = 2;
		_weight = 0;
		_price = 7;
		_name = "Carrot";
		break;
	case FoodType::Icecream:
		_happiness = 3;
		_fullness = 1;
		_weight = 2;
		_price = 5;
		_name = "Icecream";
		break;
	}

}

GEX::Food::Food()
{
}

