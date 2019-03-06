#include "StatsState.h"


namespace GEX {
	namespace
	{
		const std::map<PetName, PetData> TABLE = initalizePetData();
	}

	StatsState::StatsState(GEX::StateStack & stack, Context context) :
		State(stack, context),
		_pet(),
		_backgroundSprite()
	{	
		_backgroundSprite.setTexture(context.textures->get(GEX::TextureID::StatsScreen));
		intializeDisplay(context.textures);
		
	}

	void StatsState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());
		window.draw(_backgroundSprite);
		//draw all icons
		for (auto icon : _statIcons) {
			window.draw(icon);
		}
		//draw all texts
		for (auto text : _statTexts) {
			window.draw(text);
		}
	}

	bool StatsState::update(sf::Time dt)
	{
		
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
	void StatsState::intializeDisplay(TextureManager* c)
	{
		const int PET_ICON_YOFFSET = 90;
		const int STAT_ICON_XOFFSET = 40;
		const int STAT_ICON_YOFFSET = 120;
		const int STAT_ICON_YPADDING = 75;
		const int METER_XOFFSET = 100;
		const int WEIGHT_TEXT_XOFFSET = 115;
		const int METER_YCORRECTION = -10;
		const int MONEY_ICON_XOFFSET = 190;
		const int MONEY_TEXT_XOFFSET = 265;

		//Display pet icon
		_pet.setTexture(c->get(TABLE.at(Pet::getInstance().getPetName()).iconTexture));
		
		_pet.setPosition(192, PET_ICON_YOFFSET);
		centerOrigin(_pet);
		_statIcons.push_back(_pet);

		//initialize stat icons
		sf::Sprite happinessIcon;
		happinessIcon.setTexture(c->get(TextureID::HappinessIcon));
		happinessIcon.setPosition(STAT_ICON_XOFFSET, STAT_ICON_YOFFSET);
		_statIcons.push_back(happinessIcon);

		sf::Sprite fullnessIcon;
		fullnessIcon.setTexture(c->get(TextureID::FullnessIcon));
		fullnessIcon.setPosition(STAT_ICON_XOFFSET, STAT_ICON_YOFFSET +  (STAT_ICON_YPADDING * 1));
		_statIcons.push_back(fullnessIcon);

		sf::Sprite weightIcon;
		weightIcon.setTexture(c->get(TextureID::WeightIcon));
		weightIcon.setPosition(STAT_ICON_XOFFSET, STAT_ICON_YOFFSET + (STAT_ICON_YPADDING * 2));
		_statIcons.push_back(weightIcon);

		//intalize stat meters

		sf::Sprite happinessMeter;
		setMeterTexture(happinessMeter, Pet::getInstance().getHappiness(), c);
		happinessMeter.setPosition(METER_XOFFSET, happinessIcon.getPosition().y + METER_YCORRECTION);
		_statIcons.push_back(happinessMeter);

		sf::Sprite fullnessMeter;
		setMeterTexture(fullnessMeter, Pet::getInstance().getFullness(), c);
		fullnessMeter.setPosition(METER_XOFFSET, fullnessIcon.getPosition().y + METER_YCORRECTION);
		_statIcons.push_back(fullnessMeter);

		sf::Text weightText;
		weightText.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
		weightText.setCharacterSize(60);
		weightText.setStyle(sf::Text::Bold);
		weightText.setString(std::to_string(Pet::getInstance().getWeight()));
		weightText.setPosition(WEIGHT_TEXT_XOFFSET, weightIcon.getPosition().y);
		_statTexts.push_back(weightText);

		sf::Sprite moneyIcon;
		moneyIcon.setTexture(c->get(TextureID::MoneyIcon));
		moneyIcon.setPosition(MONEY_ICON_XOFFSET, weightIcon.getPosition().y);
		_statIcons.push_back(moneyIcon);

		sf::Text moneyText;
		moneyText.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
		moneyText.setCharacterSize(60);
		moneyText.setStyle(sf::Text::Bold);
		moneyText.setString(std::to_string(Pet::getInstance().getMoney()));
		moneyText.setPosition(MONEY_TEXT_XOFFSET, weightIcon.getPosition().y);
		_statTexts.push_back(moneyText);

	}
	
	//assigns a meter texture to a given sprite based on a stat value
	void StatsState::setMeterTexture(sf::Sprite &meter, int value ,GEX::TextureManager* textures)
	{

		//TODO: add switch for other agegroups

		switch (value) {
		case 0:
			meter.setTexture(textures->get(TextureID::BabyMeter0));
			break;
		case 1:
			meter.setTexture(textures->get(TextureID::BabyMeter1));
			break;
		case 2:
			meter.setTexture(textures->get(TextureID::BabyMeter2));
			break;
		case 3:
			meter.setTexture(textures->get(TextureID::BabyMeter3));
			break;
		}
	}
}