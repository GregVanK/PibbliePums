#pragma once
#include"State.h"
#include "DataTables.h"
#include "Pet.h"
#include "Animation2.h"
#include "FontManager.h"
namespace GEX {
	class StatsState : public GEX::State
	{
	public:
		StatsState(GEX::StateStack& stack, Context context);
		void					draw() override;
		bool					update(sf::Time dt) override;
		bool					handleEvents(const sf::Event& event) override;
	private:
		void					intializeDisplay(TextureManager* c);

		void setMeterTexture(sf::Sprite &meter,int value, GEX::TextureManager* textures);
		sf::Sprite			_backgroundSprite;
		sf::Sprite			_pet;
		GEX::Animation2     _idleAnimation;
		std::vector<sf::Sprite>	_statIcons;
		std::vector<sf::Text>	_statTexts;
		SoundPlayer*			_sounds;
		MusicPlayer*			_music;
	};
}

