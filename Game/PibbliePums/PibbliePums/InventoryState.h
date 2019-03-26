#pragma once
#include"State.h"
#include "Pet.h"
#include "Inventory.h"
	class InventoryState : public GEX::State
	{
	public:
		InventoryState(GEX::StateStack& stack, Context context);
		void					draw() override;
		bool					update(sf::Time dt) override;
		bool					handleEvents(const sf::Event& event) override;
		void					generateInventoryDisplay();
		void					itemNavDown();
		void					itemNavUp();
		void					itemSelect();
		void					updateCursor();
	private:
		sf::Sprite				_backgroundSprite;
		std::vector<sf::Text>	_itemTexts;
		std::vector<sf::Text>	_statTexts;
		sf::Sprite				_cursor;

		GEX::Inventory			_inventory;
		int						_selectedIndex;
		sf::Vector2f			_viewSize;
		GEX::SoundPlayer*			_sounds;
	};

