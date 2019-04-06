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
		_price = 150;
		_name = "Burger";
		break;
	case FoodType::Carrot:
		_happiness = 1;
		_fullness = 2;
		_weight = 0;
		_price = 80;
		_name = "Carrot";
		break;
	case FoodType::Icecream:
		_happiness = 3;
		_fullness = 1;
		_weight = 2;
		_price = 100;
		_name = "Icecream";
		break;
	case FoodType::Apple:
		_happiness = 2;
		_fullness = 1;
		_weight = 1;
		_price = 70;
		_name = "Apple";
		break;
	case FoodType::Bread:
		_happiness = 1;
		_fullness = 2;
		_weight = 4;
		_price = 125;
		_name = "Bread";
		break;
	case FoodType::Cake:
		_happiness = 5;
		_fullness = 2;
		_weight = 5;
		_price = 250;
		_name = "Cake";
		break;
	case FoodType::Cheese:
		_happiness = 2;
		_fullness = 2;
		_weight = 4;
		_price = 85;
		_name = "Cheese";
		break;
	case FoodType::FishSticks:
		_happiness = 3;
		_fullness = 3;
		_weight = 3;
		_price = 150;
		_name = "Fish Sticks";
		break;
	case FoodType::Fries:
		_happiness = 3;
		_fullness = 2;
		_weight = 5;
		_price = 130;
		_name = "French Fries";
		break;
	case FoodType::Pie:
		_happiness = 4;
		_fullness = 3;
		_weight = 5;
		_price = 220;
		_name = "Pie";
		break;
	case FoodType::Salad:
		_happiness = 1;
		_fullness = 4;
		_weight = 0;
		_price = 160;
		_name = "Salad";
		break;
	case FoodType::Sandwich:
		_happiness = 2;
		_fullness = 4;
		_weight = 3;
		_price = 180;
		_name = "Sandwhich";
		break;
	case FoodType::Soup:
		_happiness = 2;
		_fullness = 3;
		_weight = 1;
		_price = 145;
		_name = "Soup";
		break;
	case FoodType::Steak:
		_happiness = 4;
		_fullness = 4;
		_weight = 5;
		_price = 300;
		_name = "Steak";
		break;
	case FoodType::Strawberry:
		_happiness = 1;
		_fullness = 1;
		_weight = 0;
		_price = 180;
		_name = "Salad";
		break;
	case FoodType::Sushi:
		_happiness = 3;
		_fullness = 5;
		_weight = 1;
		_price = 260;
		_name = "Sushi";
		break;
	case FoodType::Medicine:
		_happiness = 0;
		_fullness = 0;
		_weight = 0;
		_price = 200;
		_name = "Medicine";
	}

}

GEX::Food::Food()
{
}

