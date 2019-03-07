#include "ShopState.h"

namespace GEX {
	GEX::ShopState::ShopState(GEX::StateStack & stack, Context context) :
		State(stack, context),
		_backgroundSprite()
	{
		_backgroundSprite.setTexture(context.textures->get(GEX::TextureID::ShopScreen));
	}

	void ShopState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());
		window.draw(_backgroundSprite);
	}

	bool GEX::ShopState::update(sf::Time dt)
	{
		return false;
	}

	bool GEX::ShopState::handleEvents(const sf::Event & event)
	{
		if (event.type != sf::Event::KeyPressed)
			return false;
		if (event.key.code == sf::Keyboard::Escape)
			requestStackPop();
		return false;
	}
}
