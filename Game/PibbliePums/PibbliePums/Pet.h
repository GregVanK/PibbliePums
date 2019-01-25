#pragma once
#include "Entity.h"
#include "TextureManager.h"
#include <SFML\Graphics\Sprite.hpp>
#include "Animation2.h"
#include <functional>
#include <random>
#include <time.h>
#include <chrono>
#include <ctime> 
namespace GEX {
	enum class PetName {
		EggBaby,
		MelonChan
	};
	class Pet : public Entity
	{
	public:
		
		enum class Position {
			Left,
			Right,
			Center
		};
		enum class Facing {
			Left,
			Right
		};
		enum class State {
			Idle,
			Walking,
			Upset,
			Happy,
			Sick
		};
		Pet(PetName type, const TextureManager& textures, bool flippable);
		virtual void				drawcurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		unsigned int				getCategory() const override;
		sf::FloatRect				getBoundingBox()const override;
		
	protected:
		void						updateCurrent(sf::Time dt, CommandQueue& commands) override;
	private:
		void						remove() override;
		void						updateMovement(sf::Time dt);
		void						updateAnimations();
	private:
		sf::Sprite						_sprite;
		Position						_position;
		Facing							_facing;
		PetName							_petType;
		sf::Time						_movementTimer;
		bool							_isFlippable;
		std::map<State, Animation2>		_animations;
		State							_state;
		std::chrono::system_clock::time_point	_birthday;
		std::chrono::system_clock::time_point	_evoTime;
		const TextureManager*					_textureManager;

		bool							_agedUp;
	};
}

