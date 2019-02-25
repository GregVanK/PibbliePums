#include "Food.h"



GEX::Food::Food(FoodType type):
	_type(type)
{
	//give states based on type
	switch (_type) {
	case FoodType::Burger:
		_happiness = 3;
		_fullness = 2;
		_weight = 5;
		_price = 20;
		_name = "Burger";
	}
}

GEX::Food::Food()
{
}

