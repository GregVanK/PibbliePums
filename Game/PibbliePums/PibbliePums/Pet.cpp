#include "Pet.h"
#include <iostream>
#include "Utility.h"
#include "DataTables.h"
#include <map>
using namespace std::placeholders;
namespace GEX {
	namespace {
		const std::map<PetName,PetData> TABLE = initalizePetData();
	}
}

GEX::Pet* GEX::Pet::_instance = nullptr;

GEX::Pet::Pet():
	_sprite(),
	_position(Position::Center),
	_movementTimer(sf::Time::Zero),
	_isFlippable(false),
	_facing(Facing::Left),
	_state(State::Idle),
	_agedUp(false),
	_petType(PetName::EggBaby),
	_textureManager(),
	_inventory()
{
}

GEX::Pet::Pet(PetName type, const TextureManager & textures, bool flippable = true) :
	Entity(),
	_sprite(textures.get(TABLE.at(type).texture), sf::IntRect(1, 1, 1, 1)),
	_position(Position::Center),
	_movementTimer(sf::Time::Zero),
	_isFlippable(flippable),
	_facing(Facing::Left),
	_state(State::Idle),
	_agedUp(false),
	_petType(type),
	_textureManager(&textures),
	_inventory(),
	_happiness(0),
	_fullness(0),
	_weight(10),
	_maxStatValue(3),
	_money(100)

{
	_birthday = std::chrono::system_clock::now();
	_evoTime = _birthday + std::chrono::seconds(30);
	//intalize aniamtions
	for (auto a : TABLE.at(type).animations)
	{
		_animations[a.first] = a.second;
	}
	
	centerOrigin(_sprite);
	_sprite.scale(4, 4);
	srand(time(NULL));
	_animations[_state].restart();

	_inventory.addFood(Food::FoodType::Burger);
	_inventory.addFood(Food::FoodType::Icecream);

	_instance = this;
	//test if instant must be updated
	_inventory.addFood(Food::FoodType::Carrot);

}


void GEX::Pet::drawcurrent(sf::RenderTarget & target, sf::RenderStates states) const
{

	target.draw(_sprite, states);
}

unsigned int GEX::Pet::getCategory() const
{
	return Category::Pet;
}

sf::FloatRect GEX::Pet::getBoundingBox() const
{
	return sf::FloatRect();
}

int GEX::Pet::getHappiness()
{
	if (_happiness > _maxStatValue)
		return _maxStatValue;
	else if (_happiness < 0)
		return 0;
	else
		return _happiness;

}

int GEX::Pet::getFullness()
{
	if (_fullness > _maxStatValue)
		return _maxStatValue;
	else if (_fullness < 0)
		return 0;
	else
		return _fullness;
}



GEX::Pet & GEX::Pet::getInstance()
{
	//if (!_instance) {
	//	Pet::_instance = new Pet();
	//}
	return *Pet::_instance;
}

void GEX::Pet::updateCurrent(sf::Time dt, CommandQueue & commands)
{

	centerOrigin(_sprite);
	updateMovement(dt);
	Entity::updateCurrent(dt, commands);

	//update animations
	auto rec = _animations.at(_state).update(dt);
	_sprite.setTextureRect(rec);
	centerOrigin(_sprite);
	//update evolution;
	if (_agedUp == false && std::chrono::system_clock::now() > _evoTime) {
		_petType = PetName::MelonChan;
		_sprite.setTexture(_textureManager->get(TABLE.at(_petType).texture));
		for (auto a : TABLE.at(_petType).animations)
		{
			_animations[a.first] = a.second;
		}
		_animations[_state].restart();
		_agedUp = true;
		std::cout << "TADA!";
		auto rec = _animations.at(_state).update(dt);
		_sprite.setTextureRect(rec);
		centerOrigin(_sprite);
	}
		
}

void GEX::Pet::remove()
{
}

void GEX::Pet::updateMovement(sf::Time dt)
{
	if (_movementTimer >= sf::seconds(3)) {
		if (_position == Position::Left) {
			if (rand() % 2 == 0) {
				Entity::setVelocity(20, 0);
				_position = Position::Center;
				_movementTimer = sf::Time::Zero;
				_state = State::Walking;
				if (_isFlippable) {
					_sprite.setTextureRect(flip(_sprite.getTextureRect()));
					_facing = Facing::Right;
				}
				return;
			}
			else {
				Entity::setVelocity(0, 0);
				if (rand() % 2 == 0)
					_state = State::Idle;
				else
					_state = State::Happy;
				_position = Position::Left;
				_movementTimer = sf::Time::Zero;
			}
		}

		if (_position == Position::Right) {
			if (rand() % 2 == 0) {
				Entity::setVelocity(-20, 0);
				_position = Position::Center;
				_movementTimer = sf::Time::Zero;
				_state = State::Walking;
				if (_isFlippable) {
					_sprite.setTextureRect(flip(_sprite.getTextureRect()));
					_facing = Facing::Left;
				}
				return;
			}
			else {
				Entity::setVelocity(0, 0);
				if (rand() % 2 == 0)
					_state = State::Idle;
				else
					_state = State::Happy;
				_position = Position::Right;
				_movementTimer = sf::Time::Zero;
			}
		}
		if (_position == Position::Center) {
			int randPos = rand() % 6;
			if (randPos == 1) {
				Entity::setVelocity(-20, 0);
				_position = Position::Left;
				_state = State::Walking;
				if (_isFlippable && _facing == Facing::Right) {
					_sprite.setTextureRect(flip(_sprite.getTextureRect()));
					_facing = Facing::Left;
				}
				_movementTimer = sf::Time::Zero;
				
			}
			else if (randPos == 2) {
				Entity::setVelocity(20, 0);
				_position = Position::Right;
				_state = State::Walking;
				if (_isFlippable && _facing == Facing::Left) {
					_sprite.setTextureRect(flip(_sprite.getTextureRect()));
					_facing = Facing::Right;
				}
				_movementTimer = sf::Time::Zero;
			}
			else {
				Entity::setVelocity(0, 0);
				_position = Position::Center;
				_movementTimer = sf::Time::Zero;
				if (rand() % 2 == 0)
					_state = State::Idle;
				else
					_state = State::Happy;
			}
		}
	}
	/*if (_position == Position::Left) {
		std::cout << "Left";
	}

	if (_position == Position::Right) {
		std::cout << "Right";
	}
	if (_position == Position::Center) {
		std::cout << "Center";
	}*/

	_movementTimer += dt;
}

void GEX::Pet::updateAnimations()
{
	
}

void GEX::Pet::feed(Food f)
{
	_happiness += f.getHappiness();
	_fullness += f.getFullness();
	_weight += f.getWeight();
}
