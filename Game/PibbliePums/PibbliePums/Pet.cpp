#include "Pet.h"
#include <iostream>
#include "Utility.h"

GEX::Pet::Pet(const TextureManager & textures, bool flippable = true) :
	Entity(),
	_sprite(textures.get(TextureID::Pet), sf::IntRect(0, 0, 32, 32)),
	_position(Position::Center),
	_movementTimer(sf::Time::Zero),
	_isFlippable(flippable),
	_facing(Facing::Left)

{
	centerOrigin(_sprite);
	_sprite.scale(4, 4);
	srand(time(NULL));
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

void GEX::Pet::updateCurrent(sf::Time dt, CommandQueue & commands)
{

	centerOrigin(_sprite);
	updateMovement(dt);
	Entity::updateCurrent(dt, commands);
}

void GEX::Pet::remove()
{
}

void GEX::Pet::updateMovement(sf::Time dt)
{
	if (_movementTimer >= sf::seconds(5)) {
		if (_position == Position::Left) {
			if (rand() % 2 == 0) {
				Entity::setVelocity(20, 0);
				_position = Position::Center;
				_movementTimer = sf::Time::Zero;
				if (_isFlippable) {
					_sprite.setTextureRect(flip(_sprite.getTextureRect()));
					_facing = Facing::Right;
				}
				return;
			}
			else {
				Entity::setVelocity(0, 0);
				_position = Position::Left;
				_movementTimer = sf::Time::Zero;
			}
		}

		if (_position == Position::Right) {
			if (rand() % 2 == 0) {
				Entity::setVelocity(-20, 0);
				_position = Position::Center;
				_movementTimer = sf::Time::Zero;
				if (_isFlippable) {
					_sprite.setTextureRect(flip(_sprite.getTextureRect()));
					_facing = Facing::Left;
				}
				return;
			}
			else {
				Entity::setVelocity(0, 0);
				_position = Position::Right;
				_movementTimer = sf::Time::Zero;
			}
		}
		if (_position == Position::Center) {
			int randPos = rand() % 6;
			if (randPos == 1) {
				Entity::setVelocity(-20, 0);
				_position = Position::Left;
				if (_isFlippable && _facing == Facing::Right) {
					_sprite.setTextureRect(flip(_sprite.getTextureRect()));
					_facing = Facing::Left;
				}
				_movementTimer = sf::Time::Zero;
				
			}
			else if (randPos == 2) {
				Entity::setVelocity(20, 0);
				_position = Position::Right;
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
