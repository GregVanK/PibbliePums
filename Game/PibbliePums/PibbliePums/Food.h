#pragma once
#include <string>
namespace GEX {
	enum class FoodType {
		Burger
	};
	class Food
	{

	public:
		Food(FoodType type);
		Food();
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

