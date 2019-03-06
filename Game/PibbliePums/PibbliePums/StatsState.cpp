#include "StatsState.h"

namespace GEX {
	namespace {
		const std::map<PetName, PetData> TABLE = initalizePetData();
	}
}
namespace GEX {
	StatsState::StatsState(GEX::StateStack & stack, Context context) :
		State(stack, context),
		_pet(),
		_backgroundSprite()
	{	
		context.textures->load(GEX::TextureID::EggBaby, "Media/Textures/pets/eggie/baby_egg.png");
		_pet.setTexture(context.textures->get(TABLE.at(Pet::getInstance().getPetName()).texture));
		
		_backgroundSprite.setTexture(context.textures->get(GEX::TextureID::StatsScreen));
		auto animation = GEX::initalizePetData().at(GEX::Pet::getInstance().getPetName()).animations[GEX::Pet::State::Idle];
		
		_pet.setPosition(192, 75);
	}

	void StatsState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());

		window.draw(_backgroundSprite);
		window.draw(_pet);
	}

	bool StatsState::update(sf::Time dt)
	{
		auto rec = _idleAnimation.update(dt);
		_pet.setTextureRect(rec);
		centerOrigin(_pet);
		return false;
	}

	bool StatsState::handleEvents(const sf::Event & event)
	{
		if (event.type != sf::Event::KeyPressed)
			return false;
		if (event.key.code == sf::Keyboard::Escape)
			requestStackPop();
		return false;
	}
}