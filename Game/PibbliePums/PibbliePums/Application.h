/*
*@author: Greg VanKampen
*@file: Application.h
*@description: Main game application controller header
*/
#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "PlayerControl.h"
#include "TextureManager.h"
#include "StateStack.h"
#include "Gamestate.h"
#include "TitleState.h"
#include "InventoryState.h"
#include "StatsState.h"
#include "ShopState.h"
#include "MiniGameState.h"
#include "SoundPlayer.h"
#include "Pet.h"

class Application
{
public:
	Application();
	void run();

private:
	void processInput();
	void update(sf::Time deltaTime);
	void render();
	void registerStates();
private:
	void loadIcons();
	static const sf::Time	TimePerFrame;
	sf::RenderWindow _window;

	GEX::PlayerControl _player;
	GEX::TextureManager _textures;
	GEX::StateStack _stateStack;
	GEX::MusicPlayer _music;
	GEX::SoundPlayer _sound;
	sf::Font _font;
	static const int WIDTH = 480;
	static const int HEIGHT = 600;
	unsigned int _statNumFrames;
	int _rotate;
};


	

