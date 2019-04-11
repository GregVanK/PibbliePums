/*
*@author: Greg VanKampen  
*@file: PlayerControl.h
*@description: A class to handle player inputs
*/
#include "PlayerControl.h"
#include "World.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Category.h"
namespace GEX {

	PlayerControl::PlayerControl()
		:_currentMissionStatus(MissionStatus::Running)
	{
		initalizeActions();
		for (auto& pair : _actionBindings) {
			pair.second.category = Category::Pet;
		}
	}
	void PlayerControl::handleEvent(const sf::Event & event, CommandQueue & commands)
	{
		if (event.type == sf::Event::KeyPressed) {
			auto found = _keyBindings.find(event.key.code);
			if (found != _keyBindings.end()) {
				commands.push(_actionBindings[found->second]);
			}
		}
	}

	void PlayerControl::handleRealTimeInput(CommandQueue & commands)
	{
		//traverse
		for (auto pair : _keyBindings) {
			//look up action
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second)) {
				commands.push(_actionBindings[pair.second]);
			}
		}
	}
	void PlayerControl::setMissionStatus(MissionStatus status)
	{
		_currentMissionStatus = status;
	}
	MissionStatus PlayerControl::getMissionStatus() const
	{
		return _currentMissionStatus;
	}
	bool PlayerControl::isRealTimeAction(Action action) {
		switch (action) {
			return true;
			break;
		default:
			return false;
		}

	}
	void PlayerControl::initalizeActions() {	
	 }
}

