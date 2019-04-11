#include "Pet.h"
#include <iostream>
#include "Utility.h"
#include "DataTables.h"
#include <map>
/*
*@author: Greg VanKampen
*@file: Pet
*@description: A pet class that grows up and gets hungry
*/
using namespace std::placeholders;
namespace GEX {
	namespace {
		const std::map<PetName,PetData> TABLE = initalizePetData();
	}
}

GEX::Pet* GEX::Pet::_instance = nullptr;

GEX::Pet::Pet(PetName type, const TextureManager & textures, bool flippable = true) :
	Entity(),
	_sprite(textures.get(TABLE.at(type).texture), sf::IntRect(1, 1, 1, 1)),
	_position(Position::Center),
	_movementTimer(sf::Time::Zero),
	_isFlippable(flippable),
	_facing(Facing::Left),
	_state(State::Idle),
	_age(AgeGroup::Baby),
	_petType(type),
	_textureManager(&textures),
	_inventory(),
	_happiness(0),
	_fullness(0),
	_weight(10),
	_maxStatValue(3),
	_isSick(true),
	_money(100),
	EVO_TIME(1),
	STAT_DECREASE_TIME(1)

{
	//sets timers
	_birthday = std::chrono::system_clock::now();
	_evoTime = _birthday + std::chrono::minutes(EVO_TIME);
	_statDecreaseTime = _birthday + +std::chrono::minutes(STAT_DECREASE_TIME);
	//intalize aniamtions
	for (auto a : TABLE.at(type).animations)
	{
		_animations[a.first] = a.second;
	}
	
	centerOrigin(_sprite);
	_sprite.scale(4, 4);
	_animations[_state].restart();

	srand(time(NULL));

	//give a starting inventory
	_inventory.addFood(Food::FoodType::Burger);
	_inventory.addFood(Food::FoodType::Icecream);
	_inventory.addFood(Food::FoodType::Carrot);
	_inventory.addFood(Food::FoodType::Medicine);

	_instance = this;

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
//get Happiness
int GEX::Pet::getHappiness()
{
	if (_happiness > _maxStatValue)
		return _maxStatValue;
	else if (_happiness < 0)
		return 0;
	else
		return _happiness;

}
// get fullness
int GEX::Pet::getFullness()
{
	if (_fullness > _maxStatValue)
		return _maxStatValue;
	else if (_fullness < 0)
		return 0;
	else
		return _fullness;
}

//get instance 
GEX::Pet & GEX::Pet::getInstance()
{
	return *Pet::_instance;
}

//update pet
void GEX::Pet::updateCurrent(sf::Time dt, CommandQueue & commands)
{

	centerOrigin(_sprite);
	if (_state != State::Dead)
	{
		updateMovement(dt);
	}
	Entity::updateCurrent(dt, commands);

	//update animations
	auto rec = _animations.at(_state).update(dt);
	_sprite.setTextureRect(rec);
	centerOrigin(_sprite);
	//update evolution;
	if (_state != State::Dead)
	{
		//tests pets event timers
		if (std::chrono::system_clock::now() > _evoTime) {
			evolvePet(dt);
		}
		if (std::chrono::system_clock::now() > _statDecreaseTime) {
			decreaseStatsUpdate();
		}
	}	
}
//decreases pets stats based on current
void GEX::Pet::decreaseStatsUpdate()
{
	if (_happiness > _maxStatValue)
		_happiness = _maxStatValue;
	if (_fullness > _maxStatValue)
		_fullness = _maxStatValue;
	if (_isSick && _happiness<= 0 && _fullness <= 0) {
		die();
		return;
	}

	if (_isSick) {
		_happiness -= 2;
		_fullness -= 2;
		_weight -= 5;
		return;
	}
	else
	{
		if (_happiness <= 0 || _fullness <= 0)
			_isSick = true;

		_happiness--;
		_fullness--;
		_weight--;
	}
	//set next decrease time
	_statDecreaseTime = std::chrono::system_clock::now() + std::chrono::minutes(STAT_DECREASE_TIME);
}

//change pet into next form
void GEX::Pet::evolvePet(const sf::Time &dt)
{
	if (_age != AgeGroup::Adult && TABLE.at(_petType).nextEvolution != PetName::END) {
		//set new type
		_petType = TABLE.at(_petType).nextEvolution;
		_age = TABLE.at(_petType).ageGroup;

		switch (_age) {
		case AgeGroup::Teen:
			_maxStatValue = 4;
			break;
		case AgeGroup::Adult:
			_maxStatValue = 5;
			break;
		}

		//update textures
		_sprite.setTexture(_textureManager->get(TABLE.at(_petType).texture));
		for (auto a : TABLE.at(_petType).animations)
		{
			_animations[a.first] = a.second;
		}
		_animations[_state].restart();
		auto rec = _animations.at(_state).update(dt);
		_sprite.setTextureRect(rec);
		centerOrigin(_sprite);

		//imobalize pet if dandylion
		if (_petType == PetName::DandyLion) {
			Entity::setVelocity(0, 0);
			checkIdleAnimationState();
			_sprite.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - 16);
		}

		//reset timer
		
	}
	_evoTime = std::chrono::system_clock::now() + std::chrono::minutes(EVO_TIME);
}

void GEX::Pet::remove()
{
}

//Animation triggers which update velocity, current position, and animation state randomly
void GEX::Pet::updateMovement(sf::Time dt)
{
	
		if (_movementTimer >= sf::seconds(3)) {

			if (_petType == PetName::DandyLion) {
				checkIdleAnimationState();
				_movementTimer = sf::Time::Zero;
				return;
			}


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
					checkIdleAnimationState();
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
					checkIdleAnimationState();
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
					checkIdleAnimationState();
				}
			}
		}
		_movementTimer += dt;
	
}

//changes state to and idle animation
void GEX::Pet::checkIdleAnimationState()
{
	if (_isSick) {
		_state = State::Sick;
	}
	else {
		if (rand() % 2 == 0)
			_state = State::Idle;
		else
			_state = State::Happy;
	}
}

//changes state to dead
void GEX::Pet::die()
{
	_petType = PetName::Death;
	_state = State::Dead;
	_sprite.setTexture(_textureManager->get(TABLE.at(_petType).texture));
	for (auto a : TABLE.at(_petType).animations)
	{
		_animations[a.first] = a.second;
	}
	_animations[_state].restart();
	auto rec = _animations.at(_state).update(sf::Time::Zero);
	_sprite.setTextureRect(rec);
	centerOrigin(_sprite);
	//accomodate for tall sprite height centering
	_sprite.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + 32);
	this->setVelocity(0, 0);
}


void GEX::Pet::feed(Food f)
{
	//reset negative stats to lowest
	if (_happiness < 0)
		_happiness = 0;
	if (_fullness < 0)
		_fullness = 0;
	if (_weight < 0)
		_weight = 1;

	//apply food stats
	_happiness += f.getHappiness();
	_fullness += f.getFullness();
	_weight += f.getWeight();
	if (f.getType() == Food::FoodType::Medicine) {
		_isSick = false;
		if(_state == State::Sick)
		checkIdleAnimationState();
	}
}
