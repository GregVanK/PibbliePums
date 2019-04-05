#pragma once
#include "State.h"
#include "Pet.h"
#include "Inventory.h"
#include "FontManager.h"
#include "ShopData.h"
#include <vector>
#include <string>
#include <random>

namespace GEX {
	
	class ShopState : public State
	{
	public:
		enum class Error {
			noSpace,
			noMoney,
			empty
			
		};
		ShopState(GEX::StateStack& stack, Context context);
		void					draw() override;
		bool					update(sf::Time dt) override;
		bool					handleEvents(const sf::Event& event) override;
		//void					generateInventory();
	private:
		bool					testErrors();
		void				updateDisplay();
		void itemNavDown();
		void itemNavUp();
		void updateCursor();
		void repositionCursor();
		void itemSelect();
	private:
		sf::Sprite			_backgroundSprite;
		Inventory			_inventory;
		std::vector<std::string> _shopkeepQuotes;

		std::vector<sf::Text> _drawableTexts;
		std::vector<sf::Text> _itemTexts;
		sf::Text			_shopKeepSpeech;
		sf::Sprite			_cursor;
		int					_selectedIndex;
		SoundPlayer*		_sounds;
		bool				_purchaseFailed;
		Error				_currentError;
		MusicPlayer*			_music;
	};
}

