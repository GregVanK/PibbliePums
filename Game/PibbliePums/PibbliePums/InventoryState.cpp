#include "InventoryState.h"
#include "Utility.h"
#include "FontManager.h"


InventoryState::InventoryState(GEX::StateStack & stack, Context context):
	State(stack,context),
	_backgroundSprite(),
	_demoText()
{
	_backgroundSprite.setTexture(context.textures->get(GEX::TextureID::InventoryScreen));
	_backgroundSprite.scale(2, 2);
	//create text
	_demoText.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
	_demoText.setString("This is a demo of the Inventory Screen");
	_demoText.setCharacterSize(30);
	centerOrigin(_demoText);
	//position text
	sf::Vector2f viewSize = context.window->getView().getSize();
	_demoText.setPosition(0.5f * viewSize.x, 0.2f * viewSize.y);
	_demoText.setFillColor(sf::Color::Black);
	
}

void InventoryState::draw()
{
	//draw all
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	window.draw(_backgroundSprite);
	//window.draw(_demoText);
}

bool InventoryState::update(sf::Time dt)
{
	return false;
}

bool InventoryState::handleEvents(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;
	if (event.key.code == sf::Keyboard::Down)
		requestStackPop();
	return false;
}
