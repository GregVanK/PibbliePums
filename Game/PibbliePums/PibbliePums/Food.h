#pragma once
#include <string>
namespace GEX {
	enum class FoodType {
		Burger,
		Icecream,
		Carrot
	};
	class Food
	{

	public:
		Food(FoodType type);
		Food();
		int			getHappiness() { return _happiness; }
		int			getFullness() { return _fullness; }
		int			getWeight() { return _weight; }
		int			getPrice() { return _price; }
		std::string getName() { return _name; }
	private:
		FoodType	_type;
		int			_happiness;
		int			_fullness;
		int			_weight;
		int			_price;
		std::string _name;
	};
}

