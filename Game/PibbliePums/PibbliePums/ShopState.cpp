#include "ShopState.h"

namespace GEX {
	GEX::ShopState::ShopState(GEX::StateStack & stack, Context context) :
		State(stack, context),
		_backgroundSprite()
	{
		_backgroundSprite.setTexture(context.textures->get(GEX::TextureID::ShopScreen));

		std::srand(std::time(NULL));

		_shopkeepQuotes.push_back("Welcome friend.");
		_shopkeepQuotes.push_back("Bubba here to help.");
		_shopkeepQuotes.push_back("You hungry?\nMe hungry...");
		_shopkeepQuotes.push_back("You here to buy?");
		_shopkeepQuotes.push_back("It's Bubba time.");
		_shopkeepQuotes.push_back("Bubba always here to help.");
		_shopkeepQuotes.push_back("You like food as much as Bubba?");

		updateDisplay();
	}

	void ShopState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());
		window.draw(_backgroundSprite);

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
		return false;
	}
	void ShopState::updateDisplay()
	{
		const int SHOP_SPEECH_TEXT_X = 150;
		const int SHOP_SPEECH_TEXT_Y = 250;
		const int SHOP_SPEECH_TEXT_SIZE = 20;

		sf::Text shopKeepSpeech;
		shopKeepSpeech.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
		int quoteIndex = rand() % _shopkeepQuotes.size();
		shopKeepSpeech.setString(_shopkeepQuotes[quoteIndex]);
		shopKeepSpeech.setPosition(SHOP_SPEECH_TEXT_X, SHOP_SPEECH_TEXT_Y);
		shopKeepSpeech.setCharacterSize(SHOP_SPEECH_TEXT_SIZE);
		shopKeepSpeech.setStyle(sf::Text::Bold);
		shopKeepSpeech.setFillColor(sf::Color::Black);
		_drawableTexts.push_back(shopKeepSpeech);
		
		
	}
}
