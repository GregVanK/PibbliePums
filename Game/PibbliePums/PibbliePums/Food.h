#pragma once
#include <string>
namespace GEX {
	class Food
	{

	public:
		enum class FoodType {
			Burger,
			Icecream,
			Carrot,
			last,
			Medicine
			
		};
		Food(FoodType type);
		Food();
		int			getHappiness() { return _happiness; }
		int			getFullness() { return _fullness; }
		int			getWeight() { return _weight; }
		int			getPrice() { return _price; }
		std::string getName() { return _name; }
		FoodType			getType() { return _type; }
	private:
		FoodType	_type;
		int			_happiness;
		int			_fullness;
		int			_weight;
		int			_price;
		std::string _name;
	};
}

