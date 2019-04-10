/**
*@author: Greg VanKampen & Vaugn Rowse
*@file: Datatable.cpp
*@description: Storage of attributes for entities
*/
#include "DataTables.h"
#include "JsonFrameParser.h"
#include <SFML\System\Time.hpp>
#include <SFML/Graphics/Transformable.hpp>


std::map<GEX::PetName, GEX::PetData> GEX::initalizePetData()
{
	std::map<GEX::PetName, GEX::PetData> data;
	JsonFrameParser frames = JsonFrameParser("Media/Textures/pets/eggie/baby_egg.json");
	data[PetName::EggBaby].texture = TextureID::EggBaby;
	data[PetName::EggBaby].iconTexture = TextureID::EggIcon;
	data[PetName::EggBaby].nextEvolution = PetName::TouchFuzzy;
	data[PetName::EggBaby].ageGroup = AgeGroup::Baby;
	data[PetName::EggBaby].animations[Pet::State::Idle].addFrameSet(frames.getFramesFor("egg_idle"));
	data[PetName::EggBaby].animations[Pet::State::Idle].setDuration(sf::seconds(2.f));
	data[PetName::EggBaby].animations[Pet::State::Idle].setRepeating(true);

	data[PetName::EggBaby].animations[Pet::State::Walking].addFrameSet(frames.getFramesFor("egg_walking"));
	data[PetName::EggBaby].animations[Pet::State::Walking].setDuration(sf::seconds(1.5));
	data[PetName::EggBaby].animations[Pet::State::Walking].setRepeating(true);

	data[PetName::EggBaby].animations[Pet::State::Happy].addFrameSet(frames.getFramesFor("egg_happy"));
	data[PetName::EggBaby].animations[Pet::State::Happy].setDuration(sf::seconds(1.5));
	data[PetName::EggBaby].animations[Pet::State::Happy].setRepeating(true);

	data[PetName::EggBaby].animations[Pet::State::Sick].addFrameSet(frames.getFramesFor("egg_sick"));
	data[PetName::EggBaby].animations[Pet::State::Sick].setDuration(sf::seconds(1.5));
	data[PetName::EggBaby].animations[Pet::State::Sick].setRepeating(true);

	data[PetName::EggBaby].animations[Pet::State::Upset].addFrameSet(frames.getFramesFor("egg_upset"));
	data[PetName::EggBaby].animations[Pet::State::Upset].setDuration(sf::seconds(1.5));
	data[PetName::EggBaby].animations[Pet::State::Upset].setRepeating(true);


	frames = JsonFrameParser("Media/Textures/pets/melon-chan/melon-chan.json");
	data[PetName::MelonChan].texture = TextureID::MelonChan;
	data[PetName::MelonChan].iconTexture = TextureID::MelonChanIcon;
	data[PetName::MelonChan].nextEvolution = PetName::END;
	data[PetName::MelonChan].ageGroup = AgeGroup::Adult;
	data[PetName::MelonChan].animations[Pet::State::Idle].addFrameSet(frames.getFramesFor("melon_idle"));
	data[PetName::MelonChan].animations[Pet::State::Idle].setDuration(sf::seconds(2.f));
	data[PetName::MelonChan].animations[Pet::State::Idle].setRepeating(true);

	data[PetName::MelonChan].animations[Pet::State::Walking].addFrameSet(frames.getFramesFor("melon_walking"));
	data[PetName::MelonChan].animations[Pet::State::Walking].setDuration(sf::seconds(1.5));
	data[PetName::MelonChan].animations[Pet::State::Walking].setRepeating(true);

	data[PetName::MelonChan].animations[Pet::State::Happy].addFrameSet(frames.getFramesFor("melon_happy"));
	data[PetName::MelonChan].animations[Pet::State::Happy].setDuration(sf::seconds(1.5));
	data[PetName::MelonChan].animations[Pet::State::Happy].setRepeating(true);


	data[PetName::MelonChan].animations[Pet::State::Sick].addFrameSet(frames.getFramesFor("melon_sick"));
	data[PetName::MelonChan].animations[Pet::State::Sick].setDuration(sf::seconds(1.5));
	data[PetName::MelonChan].animations[Pet::State::Sick].setRepeating(true);

	data[PetName::MelonChan].animations[Pet::State::Upset].addFrameSet(frames.getFramesFor("melon_upset"));
	data[PetName::MelonChan].animations[Pet::State::Upset].setDuration(sf::seconds(1.5));
	data[PetName::MelonChan].animations[Pet::State::Upset].setRepeating(true);


	//touch fuzzy
	frames = JsonFrameParser("Media/Textures/pets/touch-fuzzy/touch-fuzzy.json");
	data[PetName::TouchFuzzy].texture = TextureID::TouchFuzzy;
	data[PetName::TouchFuzzy].iconTexture = TextureID::TouchFuzzyIcon;
	data[PetName::TouchFuzzy].nextEvolution = PetName::MelonChan;
	data[PetName::TouchFuzzy].ageGroup = AgeGroup::Teen;
	data[PetName::TouchFuzzy].animations[Pet::State::Idle].addFrameSet(frames.getFramesFor("touch_fuzzy_idle"));
	data[PetName::TouchFuzzy].animations[Pet::State::Idle].setDuration(sf::seconds(2.f));
	data[PetName::TouchFuzzy].animations[Pet::State::Idle].setRepeating(true);

	data[PetName::TouchFuzzy].animations[Pet::State::Walking].addFrameSet(frames.getFramesFor("touch_fuzzy_walking"));
	data[PetName::TouchFuzzy].animations[Pet::State::Walking].setDuration(sf::seconds(1.5));
	data[PetName::TouchFuzzy].animations[Pet::State::Walking].setRepeating(true);

	data[PetName::TouchFuzzy].animations[Pet::State::Happy].addFrameSet(frames.getFramesFor("touch_fuzzy_happy"));
	data[PetName::TouchFuzzy].animations[Pet::State::Happy].setDuration(sf::seconds(1.5));
	data[PetName::TouchFuzzy].animations[Pet::State::Happy].setRepeating(true);


	data[PetName::TouchFuzzy].animations[Pet::State::Sick].addFrameSet(frames.getFramesFor("touch_fuzzy_sick"));
	data[PetName::TouchFuzzy].animations[Pet::State::Sick].setDuration(sf::seconds(1.5));
	data[PetName::TouchFuzzy].animations[Pet::State::Sick].setRepeating(true);

	data[PetName::TouchFuzzy].animations[Pet::State::Upset].addFrameSet(frames.getFramesFor("touch_fuzzy_upset"));
	data[PetName::TouchFuzzy].animations[Pet::State::Upset].setDuration(sf::seconds(1.5));
	data[PetName::TouchFuzzy].animations[Pet::State::Upset].setRepeating(true);

	frames = JsonFrameParser("Media/Textures/pets/slip/slip.json");
	data[PetName::Slip].texture = TextureID::Slip;
	data[PetName::Slip].iconTexture = TextureID::SlipIcon;
	data[PetName::Slip].nextEvolution = PetName::Lily;
	data[PetName::Slip].ageGroup = AgeGroup::Baby;
	data[PetName::Slip].animations[Pet::State::Idle].addFrameSet(frames.getFramesFor("slip_idle"));
	data[PetName::Slip].animations[Pet::State::Idle].setDuration(sf::seconds(2.f));
	data[PetName::Slip].animations[Pet::State::Idle].setRepeating(true);

	data[PetName::Slip].animations[Pet::State::Walking].addFrameSet(frames.getFramesFor("slip_walking"));
	data[PetName::Slip].animations[Pet::State::Walking].setDuration(sf::seconds(1.5));
	data[PetName::Slip].animations[Pet::State::Walking].setRepeating(true);

	data[PetName::Slip].animations[Pet::State::Happy].addFrameSet(frames.getFramesFor("slip_happy"));
	data[PetName::Slip].animations[Pet::State::Happy].setDuration(sf::seconds(1.5));
	data[PetName::Slip].animations[Pet::State::Happy].setRepeating(true);


	data[PetName::Slip].animations[Pet::State::Sick].addFrameSet(frames.getFramesFor("slip_sick"));
	data[PetName::Slip].animations[Pet::State::Sick].setDuration(sf::seconds(1.5));
	data[PetName::Slip].animations[Pet::State::Sick].setRepeating(true);

	data[PetName::Slip].animations[Pet::State::Upset].addFrameSet(frames.getFramesFor("slip_upset"));
	data[PetName::Slip].animations[Pet::State::Upset].setDuration(sf::seconds(1.5));
	data[PetName::Slip].animations[Pet::State::Upset].setRepeating(true);

	frames = JsonFrameParser("Media/Textures/pets/lily/lily.json");
	data[PetName::Lily].texture = TextureID::Lily;
	data[PetName::Lily].iconTexture = TextureID::LilyIcon;
	data[PetName::Lily].nextEvolution = PetName::DandyLion;
	data[PetName::Lily].ageGroup = AgeGroup::Teen;
	data[PetName::Lily].animations[Pet::State::Idle].addFrameSet(frames.getFramesFor("lily_idle"));
	data[PetName::Lily].animations[Pet::State::Idle].setDuration(sf::seconds(2.f));
	data[PetName::Lily].animations[Pet::State::Idle].setRepeating(true);

	data[PetName::Lily].animations[Pet::State::Walking].addFrameSet(frames.getFramesFor("lily_walking"));
	data[PetName::Lily].animations[Pet::State::Walking].setDuration(sf::seconds(1.0));
	data[PetName::Lily].animations[Pet::State::Walking].setRepeating(true);

	data[PetName::Lily].animations[Pet::State::Happy].addFrameSet(frames.getFramesFor("lily_happy"));
	data[PetName::Lily].animations[Pet::State::Happy].setDuration(sf::seconds(1.5));
	data[PetName::Lily].animations[Pet::State::Happy].setRepeating(true);


	data[PetName::Lily].animations[Pet::State::Sick].addFrameSet(frames.getFramesFor("lily_sick"));
	data[PetName::Lily].animations[Pet::State::Sick].setDuration(sf::seconds(1.5));
	data[PetName::Lily].animations[Pet::State::Sick].setRepeating(true);

	data[PetName::Lily].animations[Pet::State::Upset].addFrameSet(frames.getFramesFor("lily_upset"));
	data[PetName::Lily].animations[Pet::State::Upset].setDuration(sf::seconds(1.5));
	data[PetName::Lily].animations[Pet::State::Upset].setRepeating(true);

	frames = JsonFrameParser("Media/Textures/pets/dandy-lion/dandy-lion.json");
	data[PetName::DandyLion].texture = TextureID::DandyLion;
	data[PetName::DandyLion].iconTexture = TextureID::DandyLionIcon;
	data[PetName::DandyLion].nextEvolution = PetName::END;
	data[PetName::DandyLion].ageGroup = AgeGroup::Adult;
	data[PetName::DandyLion].animations[Pet::State::Idle].addFrameSet(frames.getFramesFor("dandy-lion_idle"));
	data[PetName::DandyLion].animations[Pet::State::Idle].setDuration(sf::seconds(2.f));
	data[PetName::DandyLion].animations[Pet::State::Idle].setRepeating(true);

	data[PetName::DandyLion].animations[Pet::State::Happy].addFrameSet(frames.getFramesFor("dandy-lion_happy"));
	data[PetName::DandyLion].animations[Pet::State::Happy].setDuration(sf::seconds(1.5));
	data[PetName::DandyLion].animations[Pet::State::Happy].setRepeating(true);


	data[PetName::DandyLion].animations[Pet::State::Sick].addFrameSet(frames.getFramesFor("dandy-lion_sick"));
	data[PetName::DandyLion].animations[Pet::State::Sick].setDuration(sf::seconds(1.5));
	data[PetName::DandyLion].animations[Pet::State::Sick].setRepeating(true);

	data[PetName::DandyLion].animations[Pet::State::Upset].addFrameSet(frames.getFramesFor("dandy-lion_upset"));
	data[PetName::DandyLion].animations[Pet::State::Upset].setDuration(sf::seconds(1.5));
	data[PetName::DandyLion].animations[Pet::State::Upset].setRepeating(true);

	frames = JsonFrameParser("Media/Textures/pets/death/death.json");
	data[PetName::Death].texture = TextureID::Death;
	data[PetName::Death].nextEvolution = PetName::END;
	data[PetName::Death].ageGroup = AgeGroup::Baby;
	data[PetName::Death].animations[Pet::State::Dead].addFrameSet(frames.getFramesFor("death"));
	data[PetName::Death].animations[Pet::State::Dead].setDuration(sf::seconds(2.f));
	data[PetName::Death].animations[Pet::State::Dead].setRepeating(true);

	return data;
}

