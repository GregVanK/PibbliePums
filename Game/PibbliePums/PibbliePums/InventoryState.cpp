#include "InventoryState.h"
#include "Utility.h"
#include "FontManager.h"
#include <algorithm>


InventoryState::InventoryState(GEX::StateStack & stack, Context context,GEX::Pet& pet):
	State(stack, context),
	_backgroundSprite(),
	_inventory(pet.getInventory())
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
		window.draw(_backgroundSprite);
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
	std::list<GEX::Food>::iterator it = _inventory.getItems().begin();
	int i = 1;
	for (it = _inventory.getItems().begin(); it != _inventory.getItems().end(); ++it) {
		sf::Text foodDisplay;
		foodDisplay.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
		foodDisplay.setString(it->getName());
		foodDisplay.setCharacterSize(30);
		centerOrigin(foodDisplay);
		foodDisplay.setPosition(40,i *40);
		i++;
		foodDisplay.setFillColor(sf::Color::Magenta);
		_itemTexts.push_back(foodDisplay);
	}
}
