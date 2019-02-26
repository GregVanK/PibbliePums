#include "InventoryState.h"
#include "Utility.h"
#include "FontManager.h"
#include <algorithm>


InventoryState::InventoryState(GEX::StateStack & stack, Context context):
	State(stack, context),
	_backgroundSprite(),
	_inventory(GEX::Pet::getInstance().getInventory())
{
	_backgroundSprite.setTexture(context.textures->get(GEX::TextureID::InventoryScreen));
	_backgroundSprite.scale(2, 2);
	//create text
	generateInventoryDisplay();
}

void InventoryState::draw()
{
	//draw all
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(_backgroundSprite);
	for (auto text : _itemTexts) {
		window.draw(text);
	}
}

bool InventoryState::update(sf::Time dt)
{
	return false;
}

bool InventoryState::handleEvents(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;
	if (event.key.code == sf::Keyboard::Space)
		requestStackPop();
	if (event.key.code == sf::Keyboard::Left)
		requestStackPop();
	if (event.key.code == sf::Keyboard::Right)
		requestStackPop();
	return false;
}

void InventoryState::generateInventoryDisplay()
{
	int i = 1;
	for (auto item : _inventory.getItems()) {
		sf::Text foodDisplay;
		foodDisplay.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
		foodDisplay.setString(item.getName());
		foodDisplay.setCharacterSize(120);
		centerOrigin(foodDisplay);
		foodDisplay.setPosition(120, i * 40);
		i++;
		foodDisplay.setFillColor(sf::Color::Black);
		_itemTexts.push_back(foodDisplay);
	}

}
