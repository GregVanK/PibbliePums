#include "ShopState.h"

namespace GEX {
	GEX::ShopState::ShopState(GEX::StateStack & stack, Context context) :
		State(stack, context),
		_backgroundSprite(),
		_selectedIndex(0)
	{
		_backgroundSprite.setTexture(context.textures->get(GEX::TextureID::ShopScreen));

		_cursor.setTexture(context.textures->get(GEX::TextureID::Cursor));

		std::srand(std::time(NULL));

		_shopkeepQuotes.push_back("Welcome friend.");
		_shopkeepQuotes.push_back("Bubba here to help.");
		_shopkeepQuotes.push_back("You hungry?\nMe hungry...");
		_shopkeepQuotes.push_back("You here to buy?");
		_shopkeepQuotes.push_back("It's Bubba time.");
		_shopkeepQuotes.push_back("Bubba always here\nto help.");
		_shopkeepQuotes.push_back("You like food\nas much as Bubba?");

		generateInventory();
		updateDisplay();
		updateCursor();
	}

	void ShopState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());
		window.draw(_backgroundSprite);
		window.draw(_cursor);
		for (auto text : _drawableTexts) {
			window.draw(text);
		}

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
	void ShopState::generateInventory()
	{
		for (int i = 0; i < 5; i++) {
			Food::FoodType item = static_cast<Food::FoodType>(rand() % (int)Food::FoodType::last);
			_inventory.addFood(item);
		}

	}
	void ShopState::updateDisplay()
	{
		const int SHOP_SPEECH_TEXT_X = 150;
		const int SHOP_SPEECH_TEXT_Y = 250;
		const int SHOP_SPEECH_TEXT_SIZE = 20;

		const int DISPLAY_X_OFFESET = 40;
		const int DISPLAY_Y_OFFESET = 35;
		const int ITEM_SIZE = 35;

		
		_shopKeepSpeech.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
		int quoteIndex = rand() % _shopkeepQuotes.size();
		_shopKeepSpeech.setString(_shopkeepQuotes[quoteIndex]);
		_shopKeepSpeech.setPosition(SHOP_SPEECH_TEXT_X, SHOP_SPEECH_TEXT_Y);
		_shopKeepSpeech.setCharacterSize(SHOP_SPEECH_TEXT_SIZE);
		_shopKeepSpeech.setStyle(sf::Text::Bold);
		_shopKeepSpeech.setFillColor(sf::Color::Black);
		_drawableTexts.push_back(_shopKeepSpeech);
		
		int i = 0;
		for (auto item : _inventory.getItems()) {
			sf::Text foodDisplay;
			foodDisplay.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
			foodDisplay.setString(item.getName());
			foodDisplay.setCharacterSize(ITEM_SIZE);
			foodDisplay.setPosition(DISPLAY_X_OFFESET, DISPLAY_Y_OFFESET + i * (ITEM_SIZE));
			foodDisplay.setStyle(sf::Text::Bold);
			foodDisplay.setFillColor(sf::Color::White);
			_drawableTexts.push_back(foodDisplay);
			_itemTexts.push_back(foodDisplay);
			i++;
		}

	}

	void ShopState::itemNavDown()
	{
		_selectedIndex++;
		if (_selectedIndex > _itemTexts.size() - 1)
			_selectedIndex = 0;
		updateCursor();
	}

	void ShopState::itemNavUp()
	{
		_selectedIndex--;
		if (_selectedIndex < 0)
			_selectedIndex = _itemTexts.size() - 1;
		updateCursor();
	}

	void ShopState::updateCursor()
	{
		if (_inventory.getSize() != 0) {
			_cursor.setPosition(_itemTexts[_selectedIndex].getPosition().x-30,
				_itemTexts[_selectedIndex].getPosition().y + 15);
		}
	}
	void ShopState::itemSelect() {
		if (_inventory.getFood(_selectedIndex).getPrice() <= Pet::getInstance().getMoney()) {
			Food food = _inventory.removeFood(_selectedIndex);
			Pet::getInstance().addMoney(-food.getPrice());
			Pet::getInstance().getInventory().addFood(food);
		}
		else {
			_shopKeepSpeech.setString("Need more money...");
		}
		
	}
}
