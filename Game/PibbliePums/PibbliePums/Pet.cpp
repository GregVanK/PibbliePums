#include "Pet.h"
#include <iostream>

GEX::Pet::Pet(const TextureManager & textures):
	Entity(),
	_sprite(textures.get(TextureID::Pet),sf::IntRect(0,0,32,32)),
	_position(Position::Center),
	_movementTimer(sf::Time::Zero)
	
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
			Entity::setVelocity(20, 0);
			_position = Position::Center;
			_movementTimer = sf::Time::Zero;
			return;
		}

		if (_position == Position::Right) {
			Entity::setVelocity(-20, 0);
			_position = Position::Center;
			_movementTimer = sf::Time::Zero;
			return;
		}
		if (_position == Position::Center) {
			if (rand() % 2 == 0) {
				Entity::setVelocity(-20, 0);
				_position = Position::Left;
				_movementTimer = sf::Time::Zero;
			}
			else {
				Entity::setVelocity(20, 0);
				_position = Position::Right;
				_movementTimer = sf::Time::Zero;
			}
		}
	}
	std::cout << "Position-  X: " << this->getPosition().x << "Y:" << this->getPosition().y << "\n";
	std::cout << "Velocity-  X: " << this->getVelocity().x << "Y:" << this->getVelocity().y << "\n";
	_movementTimer += dt;
}
