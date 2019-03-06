#include "Icon.h"
#include "Utility.h"
namespace GEX {

	Icon::Icon(const TextureManager & textures, IconID id, bool isActive):
		_isActive(isActive)
	{
		switch (id) {
		case IconID::Stats:
				_sprite = sf::Sprite(textures.get(TextureID::StatIcon), sf::IntRect(0, 0, 32, 32));
				_state = GEX::StateID::Stats;
				break;
			case IconID::FoodInv:
				_sprite = sf::Sprite(textures.get(TextureID::FoodInvIcon), sf::IntRect(0, 0, 32, 32));
				_state = GEX::StateID::Inventory;
				break;
			case IconID::Games:
				_sprite = sf::Sprite(textures.get(TextureID::GameIcon), sf::IntRect(0, 0, 32, 32));
				break;
			case IconID::Shop:
				_sprite = sf::Sprite(textures.get(TextureID::ShopIcon), sf::IntRect(0, 0, 32, 32));
				break;

		}
		_sprite.scale(2, 2);
		centerOrigin(_sprite);
	}

	void Icon::drawcurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(_sprite, states);
	}

	unsigned int Icon::getCategory() const
	{
		return NULL;
	}

	sf::FloatRect Icon::getBoundingBox() const
	{
		return sf::FloatRect();
	}

	StateID Icon::getState()
	{
		return _state;
	}

	void Icon::updateCurrent(sf::Time dt, CommandQueue & commands)
	{
		if (!_isActive) {
			_sprite.setColor(sf::Color(255,255,255,125));
		}
		else {
			_sprite.setColor(sf::Color(255, 255, 255, 255));
		}
	}

}
