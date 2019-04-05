#include "ShopState.h"

namespace GEX {
	GEX::ShopState::ShopState(GEX::StateStack & stack, Context context) :
		State(stack, context),
		_backgroundSprite(),
		_selectedIndex(0),
		_sounds(context.sound),
		_purchaseFailed(false)
	{
		_backgroundSprite.setTexture(context.textures->get(GEX::TextureID::ShopScreen));

		_cursor.setTexture(context.textures->get(GEX::TextureID::Cursor));

		std::srand(std::time(NULL));

		_shopkeepQuotes.push_back("welcome friend.");
		_shopkeepQuotes.push_back("grubbooba");
		_shopkeepQuotes.push_back("you hungry?\nme hungry...");
		_shopkeepQuotes.push_back("you here to buy?");
		_shopkeepQuotes.push_back("it's bubba time.");
		_shopkeepQuotes.push_back("bubba always here\nto help.");
		_shopkeepQuotes.push_back("you like food\nas much as bubba?");
		_shopkeepQuotes.push_back("food is nice");
		_shopkeepQuotes.push_back("don't eat too much");
		_shopkeepQuotes.push_back(":)");

		_inventory = ShopData::getInstance()->getInventory();
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
		if (event.key.code == sf::Keyboard::Escape) {
			_sounds->play(SoundEffectID::Back);
			ShopData::getInstance()->setInventory(_inventory);
			requestStackPop();
		}
		if (event.key.code == sf::Keyboard::Space) {
			//if pet has inventory space and money
			if (testErrors()) {
					_sounds->play(SoundEffectID::Select);
						itemSelect();
						repositionCursor();
						updateDisplay();

			}
			else 
			{
			_purchaseFailed = true;

			updateDisplay();
		}

		}
		if (event.key.code == sf::Keyboard::Up) {
			_sounds->play(SoundEffectID::CursorMove);
			itemNavUp();
		}
		if (event.key.code == sf::Keyboard::Down) {
			_sounds->play(SoundEffectID::CursorMove);
			itemNavDown();
		}
		return false;
	}

	bool ShopState::testErrors()
	{
		if (_inventory.getFood(_selectedIndex).getPrice() > Pet::getInstance().getMoney())
		{
			_currentError = Error::noMoney;
			return false;
		}
		if (Pet::getInstance().getInventory().getSize() >= 5) {
			_currentError = Error::noSpace;
			return false;
		}
		_currentError = Error::empty;
		return true;
	}

	void ShopState::updateDisplay()
	{
		const int SHOP_SPEECH_TEXT_X = 150;
		const int SHOP_SPEECH_TEXT_Y = 250;
		const int SHOP_SPEECH_TEXT_SIZE = 20;

		const int DISPLAY_X_OFFESET = 40;
		const int DISPLAY_Y_OFFESET = 35;
		const int ITEM_SIZE = 35;
		const int ITEM_PADDING_X = 150;

		_drawableTexts.clear();
		_itemTexts.clear();
		
		_shopKeepSpeech.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));		
		_shopKeepSpeech.setPosition(SHOP_SPEECH_TEXT_X, SHOP_SPEECH_TEXT_Y);
		_shopKeepSpeech.setCharacterSize(SHOP_SPEECH_TEXT_SIZE);
		_shopKeepSpeech.setStyle(sf::Text::Bold);
		_shopKeepSpeech.setFillColor(sf::Color::Black);
		if(!_purchaseFailed){
			int quoteIndex = rand() % _shopkeepQuotes.size();
			_shopKeepSpeech.setString(_shopkeepQuotes[quoteIndex]);
		}
		else
		{
			switch (_currentError) {
			case Error::noMoney:
				_shopKeepSpeech.setString("need more money");
				break;
			case Error::noSpace:
				_shopKeepSpeech.setString("your bag full!");
			}
		}

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

			sf::Text priceDisplay;
			priceDisplay.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
			priceDisplay.setString(std::to_string(item.getPrice()));
			priceDisplay.setCharacterSize(ITEM_SIZE);
			priceDisplay.setPosition(DISPLAY_X_OFFESET + ITEM_PADDING_X, DISPLAY_Y_OFFESET + i * (ITEM_SIZE));
			priceDisplay.setStyle(sf::Text::Bold);
			priceDisplay.setFillColor(sf::Color::Yellow);
			_drawableTexts.push_back(priceDisplay);
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
		else {
			_selectedIndex = -1;
		}
	}
	void ShopState::repositionCursor()
	{
		if (_selectedIndex + 1 > _inventory.getSize())
			_selectedIndex--;
		updateCursor();
	}
	void ShopState::itemSelect() {
		if (_selectedIndex >= 0) {
			Food food = _inventory.removeFood(_selectedIndex);
			Pet::getInstance().addMoney(-food.getPrice());
			Pet::getInstance().getInventory().addFood(food);
		}
	}
}
