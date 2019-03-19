#pragma once
#include "State.h"
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
		void					updateDisplay();
		void					itemNavDown();
		void					itemNavUp();
		void					updateCursor();
		void					itemSelect();
		sf::Sprite				_backgroundSprite;
		sf::Sprite				_cursor;
		std::vector<sf::Sprite> _drawbleSprites;
		std::vector<sf::Sprite> _selectableIcons;
		
		int						_selectedIndex;

		TextureManager*			_textures;
		

	};
}

