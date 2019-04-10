/*
*@author: Greg VanKampen & Vaughn Rowse
*@file: PlayerControl.h
*@description: A class to handle player inputs
*/

#pragma once
#include <map>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Event.hpp>
#include "Command.h"
namespace GEX {
	//foward declaration
	class CommandQueue;
	enum  class Action
	{
		MoveRight,
		MoveLeft,
		Select
	};
	enum class MissionStatus {
		Running
	};
	class PlayerControl
	{
	public:
		PlayerControl();
		void			handleEvent(const sf::Event& event, CommandQueue& commands);
		void			handleRealTimeInput(CommandQueue& commands);
		void			setMissionStatus(MissionStatus status);
		MissionStatus	getMissionStatus() const;
	private:
		void			initalizeActions();
		static bool		isRealTimeAction(Action action);
	private:
		std::map<sf::Keyboard::Key, Action> _keyBindings;
		std::map<Action, Command>			_actionBindings;
		MissionStatus						_currentMissionStatus;
	};
}

