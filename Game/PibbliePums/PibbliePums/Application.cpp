/*
*@author: Greg VanKampen
*@file: Application.cpp
*@description: Main game application controller
*/
#include "Application.h"
#include "State.h"
#include "FontManager.h"
#include <windows.h>
#include <iostream>

const sf::Time Application::TimePerFrame = sf::seconds(1.0f / 60.0f);

Application::Application()
	:_window(sf::VideoMode(384, 384),"PibbliePums",sf::Style::Close),
	_player(),
	_font(),
	_textures(),
	_stateStack(GEX::State::Context(_window,_textures,_font,_player,_music,_sound)), 
	_statNumFrames(0)
{
	
	_window.setKeyRepeatEnabled(false);
	GEX::FontManager::getInstance().load(GEX::FontID::Main,"Media/apple_kid.ttf");

	_textures.load(GEX::TextureID::InventoryScreen, "Media/Textures/inventory.png");
	_textures.load(GEX::TextureID::StatsScreen, "Media/Textures/stats_background.png");
	_textures.load(GEX::TextureID::Cursor, "Media/Textures/Cursor.png");
	_textures.load(GEX::TextureID::CPUCursor, "Media/Textures/Cursor_Cpu.png");
	_textures.load(GEX::TextureID::ShopScreen, "Media/Textures/shop_background.png");
	_textures.load(GEX::TextureID::MinigameScreen, "Media/Textures/minigame_background2.png");

	//load minigame textures
	_textures.load(GEX::TextureID::RockIcon, "Media/Textures/icons/rock.png");
	_textures.load(GEX::TextureID::PaperIcon, "Media/Textures/icons/paper.png");
	_textures.load(GEX::TextureID::ScissorsIcon, "Media/Textures/icons/scissors.png");

	loadIcons();
	

	registerStates();
	_stateStack.pushState(GEX::StateID::Game);

	//fixes race condition crash
	_stateStack.forceUpdateStack();
	
}


void Application::run()
{

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (_window.isOpen())
	{

		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			processInput();
			if (_stateStack.isEmpty())
				_window.close();
			update(TimePerFrame);
			timeSinceLastUpdate -= TimePerFrame;
		}

		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (_window.pollEvent(event)) {
		_stateStack.handleEvent(event);
		if (event.type == sf::Event::Closed)
			_window.close();
	}
}

void Application::update(sf::Time deltaTime)
{
	_stateStack.update(deltaTime);

}

void Application::render()
{
	_window.clear();
	_stateStack.draw();
	_window.setView(_window.getDefaultView());
	_window.display();
}

void Application::registerStates()
{
	_stateStack.registerState<Gamestate>(GEX::StateID::Game);
	_stateStack.registerState<InventoryState>(GEX::StateID::Inventory);
	_stateStack.registerState<GEX::StatsState>(GEX::StateID::Stats);
	_stateStack.registerState<GEX::ShopState>(GEX::StateID::Shop);
	_stateStack.registerState<GEX::MiniGameState>(GEX::StateID::Minigame);
}

void Application::loadIcons()
{
	//stat icons
	_textures.load(GEX::TextureID::HappinessIcon, "Media/Textures/icons/happpiness_icon.png");
	_textures.load(GEX::TextureID::FullnessIcon, "Media/Textures/icons/fullness_icon.png");
	_textures.load(GEX::TextureID::WeightIcon, "Media/Textures/icons/weight_icon.png");
	_textures.load(GEX::TextureID::MoneyIcon, "Media/Textures/icons/money_icon.png");

	//meter icons
	_textures.load(GEX::TextureID::BabyMeter0, "Media/Textures/icons/meter/baby_meter_0.png");
	_textures.load(GEX::TextureID::BabyMeter1, "Media/Textures/icons/meter/baby_meter_1.png");
	_textures.load(GEX::TextureID::BabyMeter2, "Media/Textures/icons/meter/baby_meter_2.png");
	_textures.load(GEX::TextureID::BabyMeter3, "Media/Textures/icons/meter/baby_meter_3.png");
	
	_textures.load(GEX::TextureID::TeenMeter0, "Media/Textures/icons/meter/teen_meter_0.png");
	_textures.load(GEX::TextureID::TeenMeter1, "Media/Textures/icons/meter/teen_meter_1.png");
	_textures.load(GEX::TextureID::TeenMeter2, "Media/Textures/icons/meter/teen_meter_2.png");
	_textures.load(GEX::TextureID::TeenMeter3, "Media/Textures/icons/meter/teen_meter_3.png");
	_textures.load(GEX::TextureID::TeenMeter4, "Media/Textures/icons/meter/teen_meter_4.png");
	
	_textures.load(GEX::TextureID::AdultMeter0, "Media/Textures/icons/meter/adult_meter_0.png");
	_textures.load(GEX::TextureID::AdultMeter1, "Media/Textures/icons/meter/adult_meter_1.png");
	_textures.load(GEX::TextureID::AdultMeter2, "Media/Textures/icons/meter/adult_meter_2.png");
	_textures.load(GEX::TextureID::AdultMeter3, "Media/Textures/icons/meter/adult_meter_3.png");
	_textures.load(GEX::TextureID::AdultMeter4, "Media/Textures/icons/meter/adult_meter_4.png");
	_textures.load(GEX::TextureID::AdultMeter5, "Media/Textures/icons/meter/adult_meter_5.png");

	//pet stat icons
	_textures.load(GEX::TextureID::EggIcon, "Media/Textures/icons/pet_icons/egg_icon.png");
	_textures.load(GEX::TextureID::MelonChanIcon, "Media/Textures/icons/pet_icons/melon-chan_icon.png");
	_textures.load(GEX::TextureID::TouchFuzzyIcon, "Media/Textures/icons/pet_icons/touch_fuzzy_icon.png");
	_textures.load(GEX::TextureID::SlipIcon, "Media/Textures/icons/pet_icons/slip_icon.png");
	_textures.load(GEX::TextureID::LilyIcon, "Media/Textures/icons/pet_icons/lily_icon.png");
	_textures.load(GEX::TextureID::DandyLionIcon, "Media/Textures/icons/pet_icons/dandy-lion_icon.png");

}
