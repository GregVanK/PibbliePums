#pragma once
#include"State.h"
#include "DataTables.h"
#include "Pet.h"
#include "Animation2.h"
namespace GEX {
	class StatsState : public GEX::State
	{
	public:
		StatsState(GEX::StateStack& stack, Context context);
		void					draw() override;
		bool					update(sf::Time dt) override;
		bool					handleEvents(const sf::Event& event) override;
	private:
		sf::Sprite			_backgroundSprite;
		sf::Sprite			_pet;
		GEX::Animation2     _idleAnimation;
	};
}

