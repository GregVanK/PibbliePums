#pragma once
#include "State.h"
#include "Pet.h"
#include "Inventory.h"
#include "FontManager.h"

#include <vector>
#include <string>
#include <random>
#include <time.h>
namespace GEX {
	class ShopState : public State
	{
	public:
		ShopState(GEX::StateStack& stack, Context context);
		void					draw() override;
		bool					update(sf::Time dt) override;
		bool					handleEvents(const sf::Event& event) override;
	private:
		void				updateDisplay();
	private:
		sf::Sprite			_backgroundSprite;
		Inventory			_inventory;
		std::vector<std::string> _shopkeepQuotes;

		std::vector<sf::Text> _drawableTexts;
		
	};
}

