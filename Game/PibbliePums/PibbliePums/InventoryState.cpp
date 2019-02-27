#include "InventoryState.h"
#include "Utility.h"
#include "FontManager.h"
#include <algorithm>


InventoryState::InventoryState(GEX::StateStack & stack, Context context) :
	State(stack, context),
	_backgroundSprite(),
	_inventory(GEX::Pet::getInstance().getInventory()),
	_selectedIndex(0)
{
	_backgroundSprite.setTexture(context.textures->get(GEX::TextureID::InventoryScreen));
	_cursor.setTexture(context.textures->get(GEX::TextureID::Cursor));
	centerOrigin(_cursor);
	//create text
	generateInventoryDisplay();
	updateCursor();
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
	if(_itemTexts.size() != 0)
		window.draw(_cursor);
}

bool InventoryState::update(sf::Time dt)
{
	return false;
}

bool InventoryState::handleEvents(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;
	if(event.key.code == sf::Keyboard::Escape)
		requestStackPop();
	if (event.key.code == sf::Keyboard::Space) {
		itemSelect();
		requestStackPop();
	}
	if (event.key.code == sf::Keyboard::Up)
		itemNavUp();
	if (event.key.code == sf::Keyboard::Down)
		itemNavDown();
	return false;
}

void InventoryState::generateInventoryDisplay()
{
	const int DISPLAY_X_OFFESET = 40;
	const int DISPLAY_Y_OFFESET = 35;
	const int ITEM_SIZE = 60;
	const int ITEM_PADDING = 0;

	int i = 0;
	for (auto item : _inventory.getItems()) {
		sf::Text foodDisplay;
		foodDisplay.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
		foodDisplay.setString(item.getName());
		foodDisplay.setCharacterSize(ITEM_SIZE);

		foodDisplay.setPosition(DISPLAY_X_OFFESET, DISPLAY_Y_OFFESET + i * (ITEM_SIZE + ITEM_PADDING));
		foodDisplay.setStyle(sf::Text::Bold);
		i++;
		foodDisplay.setFillColor(sf::Color(217,87,99));
		_itemTexts.push_back(foodDisplay);
	}

}

void InventoryState::itemNavDown()
{
	_selectedIndex++;
	if (_selectedIndex > _itemTexts.size()-1)
		_selectedIndex = 0;
	updateCursor();
}

void InventoryState::itemNavUp()
{
	_selectedIndex--;
	if (_selectedIndex < 0)
		_selectedIndex = _itemTexts.size() -1;
	updateCursor();
}

void InventoryState::itemSelect()
{
	if(_inventory.getSize() !=0)
	GEX::Pet::getInstance().feed(GEX::Pet::getInstance().getInventory().removeFood(_selectedIndex));
}

//place the cursor
void InventoryState::updateCursor()
{
	if (_inventory.getSize() != 0) {
		_cursor.setPosition(_itemTexts[_selectedIndex].getPosition().x - 20,
			_itemTexts[_selectedIndex].getPosition().y + 45);
	}
}
