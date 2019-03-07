#pragma once
#include "State.h"
namespace GEX {
	class ShopState : public State
	{
	public:
		ShopState(GEX::StateStack& stack, Context context);
		void					draw() override;
		bool					update(sf::Time dt) override;
		bool					handleEvents(const sf::Event& event) override;
	private:
		sf::Sprite			_backgroundSprite;
	};
}

