/**
*@author: Greg VanKampen
*@file: GameState.cpp
*@description: State when the game plays in
*/
#include "Gamestate.h"


	Gamestate::Gamestate(GEX::StateStack & stack, Context context)
		:State(stack,context),
		_world(*context.window,*context.sound),
		player(*context.player)
	{
		context.music->play(GEX::MusicID::Room);
	}
	void Gamestate::draw()
	{
		_world.draw();
	}
	bool Gamestate::update(sf::Time dt)
	{
		_world.update(dt);
		GEX::CommandQueue& commands = _world.getCommandQueue();
		player.handleRealTimeInput(commands);
		return true;
	}
	bool Gamestate::handleEvents(const sf::Event & event)
	{
		GEX::CommandQueue& commands = _world.getCommandQueue();
		player.handleEvent(event,commands);
		if (!GEX::Pet::getInstance().isDead()) {
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Left)
			{
				_world.iconNavLeft();
				_world.playSound(GEX::SoundEffectID::CursorMove);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Right)
			{
				_world.iconNavRight();
				_world.playSound(GEX::SoundEffectID::CursorMove);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Down || event.key.code == sf::Keyboard::Key::Up) {
				_world.playSound(GEX::SoundEffectID::Select);
				GEX::StateID pushableState = _world.getCurrentIconState();
				requestStackPush(pushableState);
			}
		}
		return true;
	}
