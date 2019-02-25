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
	private:
		sf::Sprite				_backgroundSprite;
		std::vector<sf::Text>	_itemTexts;
		GEX::Inventory			_inventory;
		sf::Vector2f			_viewSize;

	};

