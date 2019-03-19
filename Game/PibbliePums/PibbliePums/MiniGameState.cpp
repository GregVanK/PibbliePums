#include "MiniGameState.h"


namespace GEX {
	MiniGameState::MiniGameState(GEX::StateStack & stack, Context context):
		State(stack, context),
		_textures(context.textures),
		_backgroundSprite(),
		_selectedIndex(0)
	{
		_backgroundSprite.setTexture(context.textures->get(GEX::TextureID::MinigameScreen));
		_cursor.setTexture(context.textures->get(GEX::TextureID::Cursor));
		centerOrigin(_cursor);

		_textures->load(GEX::TextureID::RockIcon, "Media/Textures/icons/rock.png");
		_textures->load(GEX::TextureID::PaperIcon, "Media/Textures/icons/paper.png");
		_textures->load(GEX::TextureID::ScissorsIcon, "Media/Textures/icons/scissors.png");
		updateDisplay();
		updateCursor();

	}
	void MiniGameState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());
		window.draw(_backgroundSprite);
		for (sf::Sprite s : _drawbleSprites)
			window.draw(s);
		window.draw(_cursor);
	}
	bool MiniGameState::update(sf::Time dt)
	{
		return false;
	}
	bool MiniGameState::handleEvents(const sf::Event & event)
	{
		if (event.type != sf::Event::KeyPressed)
			return false;
		if (event.key.code == sf::Keyboard::Escape)
			requestStackPop();
		if (event.key.code == sf::Keyboard::Space) {
			itemSelect();
			//DO AN ANIMATION?
			requestStackPop();
		}
		if (event.key.code == sf::Keyboard::Up)
			itemNavUp();
		if (event.key.code == sf::Keyboard::Down)
			itemNavDown();
		return false;
	}
	void MiniGameState::updateDisplay()
	{
		const int GAME_ICON_Y = 150;
		const int GAME_ICON_X = 20;
		const int GAME_ICON_PADDING = 140;
		int column = 0;

		sf::Sprite rock;
		rock.setTexture(_textures->get(TextureID::RockIcon));
		rock.setPosition(GAME_ICON_X +( GAME_ICON_PADDING * column), GAME_ICON_Y);
		_drawbleSprites.push_back(rock);
		_selectableIcons.push_back(rock);
		column++;

		sf::Sprite paper;
		paper.setTexture(_textures->get(TextureID::PaperIcon));
		paper.setPosition(GAME_ICON_X + (GAME_ICON_PADDING * column), GAME_ICON_Y);
		_drawbleSprites.push_back(paper);
		_selectableIcons.push_back(paper);
		column++;

		sf::Sprite scissors;
		scissors.setTexture(_textures->get(TextureID::ScissorsIcon));
		scissors.setPosition(GAME_ICON_X + (GAME_ICON_PADDING * column), GAME_ICON_Y);
		_drawbleSprites.push_back(scissors);
		_selectableIcons.push_back(scissors);
		column++;

	}
	void MiniGameState::itemNavDown()
	{
		_selectedIndex++;
		updateCursor();
	}
	void MiniGameState::itemNavUp()
	{
		_selectedIndex--;
		updateCursor();
	}
	void MiniGameState::updateCursor()
	{
		//_selectableIcons[_selectedIndex] 
		//do something with index
	}
	void MiniGameState::itemSelect()
	{
	}
}