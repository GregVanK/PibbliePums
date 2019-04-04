/**
*@author: Greg VanKampen & Vaugn Rowse
*@file: Datatable.cpp
*@description: Storage of attributes for entities
*/
#include "DataTables.h"
#include "JsonFrameParser.h"
#include <SFML\System\Time.hpp>
#include <SFML/Graphics/Transformable.hpp>



std::map<GEX::Pickup::Type, GEX::PickupData> GEX::initalizePickupData()
{
	std::map<GEX::Pickup::Type, GEX::PickupData> data;

	return data;
}

std::map<GEX::ObstacleType, GEX::ObstacleData> GEX::initalizeObstacleData()
{
	std::map<GEX::ObstacleType, GEX::ObstacleData> data;
	JsonFrameParser frames = JsonFrameParser("Media/Textures/Atlas.json");

	data[ObstacleType::Car1].texture = TextureID::Entities;
	data[ObstacleType::Car1].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("raceCarL"));
	data[ObstacleType::Car1].animations[Obstacle::State::Idle].setDuration(sf::seconds(1.f));
	data[ObstacleType::Car1].animations[Obstacle::State::Idle].setRepeating(true);
	//data[ObstacleType::Car1].textureRect = sf::IntRect(85, 337, 40, 40);
	data[ObstacleType::Car1].spawnTime = sf::seconds(4.5);

	data[ObstacleType::Car2].texture = TextureID::Entities;
	data[ObstacleType::Car2].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("raceCarL"));
	data[ObstacleType::Car2].animations[Obstacle::State::Idle].setDuration(sf::seconds(1.f));
	data[ObstacleType::Car2].animations[Obstacle::State::Idle].setRepeating(true);
	//data[ObstacleType::Car2].textureRect = sf::IntRect(43, 337, 40, 40);
	data[ObstacleType::Car2].spawnTime = sf::seconds(5.f);

	data[ObstacleType::Car3].texture = TextureID::Entities;
	data[ObstacleType::Car3].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("raceCarR"));
	data[ObstacleType::Car3].animations[Obstacle::State::Idle].setDuration(sf::seconds(1.f));
	data[ObstacleType::Car3].animations[Obstacle::State::Idle].setRepeating(true);
	//data[ObstacleType::Car3].textureRect = sf::IntRect(85, 337, 40, 40);
	data[ObstacleType::Car3].spawnTime = sf::seconds(3.f);

	data[ObstacleType::Truck].texture = TextureID::Entities;
	data[ObstacleType::Truck].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("truck"));
	data[ObstacleType::Truck].animations[Obstacle::State::Idle].setDuration(sf::seconds(1.f));
	data[ObstacleType::Truck].animations[Obstacle::State::Idle].setRepeating(true);
	//data[ObstacleType::Truck].textureRect = sf::IntRect(137, 237, 61, 40);
	data[ObstacleType::Truck].spawnTime = sf::seconds(5.f);

	data[ObstacleType::Tractor].texture = TextureID::Entities;
	data[ObstacleType::Tractor].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("tractor"));
	data[ObstacleType::Tractor].animations[Obstacle::State::Idle].setDuration(sf::seconds(0.f));
	data[ObstacleType::Tractor].animations[Obstacle::State::Idle].setRepeating(false);
	//data[ObstacleType::Tractor].textureRect = sf::IntRect(1, 379, 40, 40);
	data[ObstacleType::Tractor].spawnTime = sf::seconds(4.f);

	data[ObstacleType::Log1].texture = TextureID::Entities;
	data[ObstacleType::Log1].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("tree1"));
	data[ObstacleType::Log1].animations[Obstacle::State::Idle].setDuration(sf::seconds(0.f));
	data[ObstacleType::Log1].animations[Obstacle::State::Idle].setRepeating(false);
	data[ObstacleType::Log1].spawnTime = sf::seconds(2.5);

	data[ObstacleType::Log2].texture = TextureID::Entities;
	data[ObstacleType::Log2].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("tree2"));
	data[ObstacleType::Log2].animations[Obstacle::State::Idle].setDuration(sf::seconds(0.f));
	data[ObstacleType::Log2].animations[Obstacle::State::Idle].setRepeating(false);
	data[ObstacleType::Log2].spawnTime = sf::seconds(2.5);

	data[ObstacleType::GatorIcon].texture = TextureID::Entities;
	data[ObstacleType::GatorIcon].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("crocIcon"));
	data[ObstacleType::GatorIcon].animations[Obstacle::State::Idle].setDuration(sf::seconds(0.f));
	data[ObstacleType::GatorIcon].animations[Obstacle::State::Idle].setRepeating(false);


	data[ObstacleType::Log2_2].texture = TextureID::Entities;
	data[ObstacleType::Log2_2].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("tree1"));
	data[ObstacleType::Log2_2].animations[Obstacle::State::Idle].setDuration(sf::seconds(0.f));
	data[ObstacleType::Log2_2].animations[Obstacle::State::Idle].setRepeating(false);
	data[ObstacleType::Log2_2].spawnTime = sf::seconds(2.5);

	data[ObstacleType::Turtle2].texture = TextureID::Entities;
	data[ObstacleType::Turtle2].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("2turtles 1"));
	data[ObstacleType::Turtle2].animations[Obstacle::State::Idle].setDuration(sf::seconds(0.f));
	data[ObstacleType::Turtle2].animations[Obstacle::State::Idle].setRepeating(false);
	data[ObstacleType::Turtle2].spawnTime = sf::seconds(2.5);


	data[ObstacleType::Turtle3].texture = TextureID::Entities;
	data[ObstacleType::Turtle3].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("3turtles 1"));
	data[ObstacleType::Turtle3].animations[Obstacle::State::Idle].setDuration(sf::seconds(0.f));
	data[ObstacleType::Turtle3].animations[Obstacle::State::Idle].setRepeating(false);
	data[ObstacleType::Turtle3].spawnTime = sf::seconds(3);

	data[ObstacleType::Turtle3Diving].texture = TextureID::LilyPad;
	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("3turtles"));
	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::Idle].setDuration(sf::seconds(2.f));
	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::Idle].setRepeating(true);

	data[ObstacleType::Gator].texture = TextureID::Entities;
	data[ObstacleType::Gator].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("croc "));
	data[ObstacleType::Gator].animations[Obstacle::State::Idle].setDuration(sf::seconds(1.f));
	data[ObstacleType::Gator].animations[Obstacle::State::Idle].setRepeating(true);

	data[ObstacleType::BonusFly].texture = TextureID::Entities;
	data[ObstacleType::BonusFly].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("bugIcon"));
	data[ObstacleType::BonusFly].animations[Obstacle::State::Idle].setDuration(sf::seconds(0.f));
	data[ObstacleType::BonusFly].animations[Obstacle::State::Idle].setRepeating(false);

	frames = JsonFrameParser("Media/Textures/LilyPad.json");
	data[ObstacleType::LilyPad].texture = TextureID::LilyPad;
	data[ObstacleType::LilyPad].animations[Obstacle::State::Idle].addFrameSet(frames.getFramesFor("lillyPad"));
	data[ObstacleType::LilyPad].animations[Obstacle::State::Idle].setDuration(sf::seconds(1.f));
	data[ObstacleType::LilyPad].animations[Obstacle::State::Idle].setRepeating(false);
	data[ObstacleType::FrogIcon].texture = TextureID::Entities;
	data[ObstacleType::FrogIcon].textureRect = sf::IntRect(127, 321,40,40);

	data[ObstacleType::Turtle2Diving].texture = TextureID::LilyPad;

	//turtles 2 aniamtions
	data[ObstacleType::Turtle2Diving].animations[Obstacle::State::Dive].addFrameSet(frames.getFramesFor("2turtles"));
	data[ObstacleType::Turtle2Diving].animations[Obstacle::State::Dive].setDuration(sf::seconds(0.5));
	data[ObstacleType::Turtle2Diving].animations[Obstacle::State::Dive].setRepeating(false);

	data[ObstacleType::Turtle2Diving].animations[Obstacle::State::Surface].addFrameSet(frames.getFramesFor("2rturtles"));
	data[ObstacleType::Turtle2Diving].animations[Obstacle::State::Surface].setDuration(sf::seconds(0.5));
	data[ObstacleType::Turtle2Diving].animations[Obstacle::State::Surface].setRepeating(false);

	data[ObstacleType::Turtle2Diving].animations[Obstacle::State::SwimUnder].addFrameSet(frames.getFramesFor("2turtles 4"));
	data[ObstacleType::Turtle2Diving].animations[Obstacle::State::SwimUnder].setDuration(sf::seconds(0.5));
	data[ObstacleType::Turtle2Diving].animations[Obstacle::State::SwimUnder].setRepeating(false);

	data[ObstacleType::Turtle2Diving].animations[Obstacle::State::SwimOver].addFrameSet(frames.getFramesFor("2turtles 1"));
	data[ObstacleType::Turtle2Diving].animations[Obstacle::State::SwimOver].setDuration(sf::seconds(2.f));
	data[ObstacleType::Turtle2Diving].animations[Obstacle::State::SwimOver].setRepeating(false);

	//turtle 3 animations
	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::Dive].addFrameSet(frames.getFramesFor("3turtles"));
	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::Dive].setDuration(sf::seconds(1.f));
	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::Dive].setRepeating(false);

	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::Surface].addFrameSet(frames.getFramesFor("3rturtles"));
	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::Surface].setDuration(sf::seconds(1.f));
	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::Surface].setRepeating(false);

	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::SwimUnder].addFrameSet(frames.getFramesFor("3turtles 4"));
	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::SwimUnder].setDuration(sf::seconds(1.f));
	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::SwimUnder].setRepeating(false);

	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::SwimOver].addFrameSet(frames.getFramesFor("3turtles 1"));
	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::SwimOver].setDuration(sf::seconds(3.f));
	data[ObstacleType::Turtle3Diving].animations[Obstacle::State::SwimOver].setRepeating(false);
	

	return data;
}


std::map<GEX::Particle::Type, GEX::ParticleData> GEX::initalizeParticleData()
{
	std::map<GEX::Particle::Type, GEX::ParticleData> data;
	data[GEX::Particle::Type::Propellant].color = sf::Color(50, 150, 100);
	data[GEX::Particle::Type::Propellant].lifetime = sf::seconds(0.6f);

	data[GEX::Particle::Type::Smoke].color = sf::Color(100, 150, 50);
	data[GEX::Particle::Type::Smoke].lifetime = sf::seconds(0.8f);

	return data;
}

GEX::FrogData GEX::intitalizeFrogData()
{
	GEX::FrogData frogData;
	JsonFrameParser frames = JsonFrameParser("Media/Textures/Atlas.json");

	frogData.texture = TextureID::Frog;
	frogData.textureRect = sf::IntRect(43, 379, 40, 40);
	frogData.animations[GEX::Frog::State::Up].addFrameSet(frames.getFramesFor("up"));
	frogData.animations[GEX::Frog::State::Up].setDuration(sf::Time(sf::seconds(1.f)));
	frogData.animations[GEX::Frog::State::Up].setRepeating(false);
	frogData.animations[GEX::Frog::State::Down].addFrameSet(frames.getFramesFor("down"));
	frogData.animations[GEX::Frog::State::Down].setDuration(sf::Time(sf::seconds(1.f)));
	frogData.animations[GEX::Frog::State::Down].setRepeating(false);
	frogData.animations[GEX::Frog::State::Left].addFrameSet(frames.getFramesFor("left"));
	frogData.animations[GEX::Frog::State::Left].setDuration(sf::Time(sf::seconds(1.f)));
	frogData.animations[GEX::Frog::State::Left].setRepeating(false);
	frogData.animations[GEX::Frog::State::Right].addFrameSet(frames.getFramesFor("right"));
	frogData.animations[GEX::Frog::State::Right].setDuration(sf::Time(sf::seconds(1.f)));
	frogData.animations[GEX::Frog::State::Right].setRepeating(false);
	frogData.animations[GEX::Frog::State::Die].addFrameSet(frames.getFramesFor("die"));
	frogData.animations[GEX::Frog::State::Die].setDuration(sf::Time(sf::seconds(2.f)));
	frogData.animations[GEX::Frog::State::Die].setRepeating(false);

	return frogData;
}

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
	data[PetName::EggBaby].ageGroup = AgeGroup::Adult;
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

//std::map<GEX::AircraftType, GEX::AircraftData> GEX::initalizeAircraftData()
//{
//
//	ask for values
//	std::map<GEX::AircraftType, GEX::AircraftData> data;
//	data[AircraftType::Eagle].hitpoints = 100;
//	data[AircraftType::Eagle].speed = 1200.f;
//	data[AircraftType::Eagle].texture = TextureID::Entities;
//	data[AircraftType::Eagle].textureRect = sf::IntRect(0, 0, 48, 64);
//	data[AircraftType::Eagle].fireInterval = sf::seconds(0.5);
//	data[AircraftType::Eagle].hasRollAnimation = true;
//
//	data[AircraftType::Raptor].hitpoints = 20;
//	data[AircraftType::Raptor].speed = 200.f;
//	data[AircraftType::Raptor].texture = TextureID::Entities;
//	data[AircraftType::Raptor].textureRect = sf::IntRect(144, 0, 84, 64);
//	data[AircraftType::Raptor].directions.emplace_back(Direction(40.f, 100.f));
//	data[AircraftType::Raptor].directions.emplace_back(Direction(-80.f, 100.f));
//	data[AircraftType::Raptor].directions.emplace_back(Direction(40.f, 100.f));
//	data[AircraftType::Raptor].fireInterval = sf::Time::Zero;
//	data[AircraftType::Raptor].hasRollAnimation = false;
//
//
//	data[AircraftType::Avenger].hitpoints = 40;
//	data[AircraftType::Avenger].speed = 200.f;
//	data[AircraftType::Avenger].texture = TextureID::Entities;
//	data[AircraftType::Avenger].textureRect = sf::IntRect(228, 0, 60, 59);
//	data[AircraftType::Avenger].directions.emplace_back(Direction(45.f, 50.f));
//	data[AircraftType::Avenger].directions.emplace_back(Direction(0.f, 50.f));
//	data[AircraftType::Avenger].directions.emplace_back(Direction(-45.f, 100.f));
//	data[AircraftType::Avenger].directions.emplace_back(Direction(0.f, 50.f));
//	data[AircraftType::Avenger].directions.emplace_back(Direction(45.f, 50.f));
//	data[AircraftType::Avenger].fireInterval = sf::seconds(2);
//	data[AircraftType::Avenger].hasRollAnimation = false;
//
//	data[AircraftType::Boss].hitpoints = 1200;
//	data[AircraftType::Boss].speed = 10.f;
//	data[AircraftType::Boss].texture = TextureID::Boss;
//	data[AircraftType::Boss].directions.emplace_back(Direction(45.f, 50.f));
//	data[AircraftType::Boss].directions.emplace_back(Direction(0.f, 50.f));
//	data[AircraftType::Boss].directions.emplace_back(Direction(-45.f, 100.f));
//	data[AircraftType::Boss].directions.emplace_back(Direction(0.f, 50.f));
//	data[AircraftType::Boss].directions.emplace_back(Direction(45.f, 50.f));
//	data[AircraftType::Boss].fireInterval = sf::seconds(2);
//
//	return data;
//}
