#pragma once
#include"State.h"
class InventoryState : public GEX::State
{
public:
	InventoryState(GEX::StateStack& stack,Context context);
	void					draw() override;
	bool					update(sf::Time dt) override;
	bool					handleEvents(const sf::Event& event) override;
private:
	sf::Sprite				_backgroundSprite;
	sf::Text				_demoText;

};

