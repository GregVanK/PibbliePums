#pragma once
#include "State.h"
#include "FontManager.h"
#include <random>
#include <time.h>
namespace GEX {
	class MiniGameState : public GEX::State
	{
	public:
		MiniGameState(GEX::StateStack& stack, Context context);
		void					draw() override;
		bool					update(sf::Time dt) override;
		bool					handleEvents(const sf::Event& event) override;
	private:
		enum class Results {
			Win,
			Lose,
			Draw
		};
		void					updateDisplay();
		void					itemNavDown();
		void					itemNavUp();
		void					updatePlayerCursor();
		void					playerSelect();
		void					cpuSelect();
		void					setResults(Results r);
	private:
		sf::Sprite				_backgroundSprite;
		sf::Sprite				_cursorPlayer;
		sf::Sprite				_cursorCPU;
		sf::Text				_resultText;
		std::vector<sf::Sprite> _drawbleSprites;
		std::vector<sf::Sprite> _selectableIcons;
		
		int						_selectedIndexPlayer;
		int						_selectedIndexCPU;
		
		Results					_gameResult;
		bool					_displayResults;
		bool					_displayResultsOver;
		sf::Time				_resultsWait;

		SoundPlayer*			_sounds;
		TextureManager*			_textures;
		

	};
}

