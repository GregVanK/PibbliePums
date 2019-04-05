#include "MiniGameState.h"
#include "Utility.h"
#include <iostream>

namespace GEX {
	namespace
	{
		const std::map<PetName, PetData> TABLE = initalizePetData();
	}

	MiniGameState::MiniGameState(GEX::StateStack & stack, Context context):
		State(stack, context),
		_textures(context.textures),
		_backgroundSprite(),
		_selectedIndexPlayer(0),
		_displayResults(false),
		_displayResultsOver(false),
		_resultsWait(sf::Time::Zero),
		_sounds(context.sound)
	{
			
		_backgroundSprite.setTexture(context.textures->get(GEX::TextureID::MinigameScreen));
		_cursorPlayer.setTexture(context.textures->get(GEX::TextureID::Cursor));
		_cursorCPU.setTexture(context.textures->get(GEX::TextureID::CPUCursor));

		updateDisplay();
		updatePlayerCursor();
		_cursorCPU.setPosition(-32, -32);

		context.music->stop();
		context.music->play(MusicID::MiniGame);
		_music = context.music;
		
	}
	void MiniGameState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());
		window.draw(_backgroundSprite);
		for (sf::Sprite s : _drawbleSprites)
			window.draw(s);
		window.draw(_cursorPlayer);
		window.draw(_cursorCPU);
		window.draw(_resultText);
	}
	bool MiniGameState::update(sf::Time dt)
	{
		const int WAIT_TIME = 2;
		if (_displayResults) {
			if (_resultsWait >= sf::seconds(WAIT_TIME)) {
				_sounds->play(SoundEffectID::Back);
				_displayResults = false;
				_music->stop();
				_music->play(MusicID::Room);
				requestStackPop();
				return true;
			}
			else {
				_resultsWait += dt;
			}
		}
		return false;
	}
	bool MiniGameState::handleEvents(const sf::Event & event)
	{
		if (!_displayResults) {
			if (event.type != sf::Event::KeyPressed)
				return false;
			if (event.key.code == sf::Keyboard::Escape) {
				_sounds->play(SoundEffectID::Back);
				_music->stop();
				_music->play(MusicID::Room);
				requestStackPop();
			}
			if (event.key.code == sf::Keyboard::Space) {
				playerSelect();
				_displayResults = true;
			}
			if (event.key.code == sf::Keyboard::Left)
				itemNavUp();
			if (event.key.code == sf::Keyboard::Right)
				itemNavDown();
		}
		return false;
	}
	void MiniGameState::updateDisplay()
	{
		const int PET_ICON_X = 192;
		const int PET_ICON_Y = 80;
		const double PET_SCALE = 1.75;
		const int GAME_ICON_Y = 150;
		const int GAME_ICON_X = 20;
		const int GAME_ICON_PADDING = 140;
		int column = 0;
		_drawbleSprites.clear();

		//TODO: ADD PET display TO MINIGAME
		sf::Sprite pet;
		pet.setTexture(_textures->get(TABLE.at(Pet::getInstance().getPetName()).iconTexture));
		pet.scale(PET_SCALE, PET_SCALE);
		centerOrigin(pet);
		pet.setPosition(PET_ICON_X, PET_ICON_Y);
		_drawbleSprites.push_back(pet);
			
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

		
		_resultText.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
		_resultText.setString("SELECT");
		_resultText.setCharacterSize(100);
		_resultText.setStyle(sf::Text::Bold);
		_resultText.setFillColor(sf::Color::Black);
		centerOrigin(_resultText);
		_resultText.setPosition(192, 240);

	}
	void MiniGameState::itemNavDown()
	{
		_sounds->play(SoundEffectID::CursorMove);
		_selectedIndexPlayer++;
		if (_selectedIndexPlayer > _selectableIcons.size() - 1)
			_selectedIndexPlayer = 0;
		updatePlayerCursor();
	}
	void MiniGameState::itemNavUp()
	{
		_sounds->play(SoundEffectID::CursorMove);
		_selectedIndexPlayer--;
		if (_selectedIndexPlayer < 0)
			_selectedIndexPlayer = _selectableIcons.size() - 1;
		updatePlayerCursor();
	}
	void MiniGameState::updatePlayerCursor()
	{
		const int PLAYER_Y_OFFSET = 74;
		const int PLAYER_X_OFFSET = 16;
		sf::Vector2f pos = _selectableIcons[_selectedIndexPlayer].getPosition();
		_cursorPlayer.setPosition(pos.x + PLAYER_X_OFFSET, pos.y + PLAYER_Y_OFFSET);
	}
	void MiniGameState::playerSelect()
	{
		_sounds->play(SoundEffectID::Select);
		cpuSelect();
		if (_selectedIndexPlayer == _selectedIndexCPU) {
			_resultText.setString("DRAW");
			_resultText.setFillColor(sf::Color::Blue);
			setResults(Results::Draw);
		}
		else if ((_selectedIndexPlayer == 0 && _selectedIndexCPU == 2) ||
			(_selectedIndexPlayer == 1 && _selectedIndexCPU == 0) ||
			(_selectedIndexPlayer == 2 && _selectedIndexCPU == 1)) {

			_resultText.setString("WIN");
			_resultText.setFillColor(sf::Color::Yellow);
			setResults(Results::Win);
		}
		else {
			_resultText.setString("LOSE");
			_resultText.setFillColor(sf::Color::Red);
			setResults(Results::Lose);
		}
		centerOrigin(_resultText);
		updatePlayerCursor();
	}
	void MiniGameState::cpuSelect()
	{
		const int CPU_Y_OFFSET = -32;
		const int CPU_X_OFFSET = 16;
		_selectedIndexCPU = rand() % 3;

		sf::Vector2f pos = _selectableIcons[_selectedIndexCPU].getPosition();
		_cursorCPU.setPosition(pos.x + CPU_X_OFFSET, pos.y + CPU_Y_OFFSET);

	}
	void MiniGameState::setResults(Results r)
	{
		_gameResult = r;
		if(_gameResult == Results::Win) 
			Pet::getInstance().addMoney(250);
	}
}