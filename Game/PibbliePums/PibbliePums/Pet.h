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
#include "Inventory.h"
#include "Food.h"
namespace GEX {
	

	enum class PetName {
		EggBaby,
		MelonChan,
		TouchFuzzy,
		Slip,
		Lily,
		DandyLion,
		Death,
		END
	};
	enum class AgeGroup {
		Baby,
		Teen,
		Adult
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
			Sick,
			Dead
		};
		Pet();
		Pet(PetName type, const TextureManager& textures, bool flippable);
		virtual void				drawcurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		unsigned int				getCategory() const override;
		sf::FloatRect				getBoundingBox()const override;
		Inventory&					getInventory() { return _inventory; }
		PetName						getPetName() { return _petType; }
		AgeGroup					getAge() { return _age; }
		int							getMoney() { return _money; }
		int							getHappiness();
		int							getFullness();
		int							getWeight() { return _weight; }
		void						addMoney(int m) { _money += m; }
		bool						isDead() { return _state == State::Dead; }

		static Pet&					getInstance();
		void						feed(Food f);

		Pet(Pet const&) = delete;
		void operator=(Pet const&) = delete;
		
	protected:
		void						updateCurrent(sf::Time dt, CommandQueue& commands) override;
		void decreaseStatsUpdate();
		void evolvePet(const sf::Time &dt);
	private:
		void						remove() override;
		void						updateMovement(sf::Time dt);
		void checkIdleAnimationState();
		void						updateAnimations();
		void						die();
		
	private:
		int								_maxStatValue;

		int								_happiness;
		int								_fullness;
		int								_weight;
		int								_money;
		bool							_isSick;

		sf::Sprite						_sprite;
		Position						_position;
		Facing							_facing;
		PetName							_petType;
		sf::Time						_movementTimer;
		bool							_isFlippable;
		std::map<State, Animation2>		_animations;
		State							_state;
		AgeGroup						_age;


		std::chrono::system_clock::time_point	_birthday;
		std::chrono::system_clock::time_point	_evoTime;
		std::chrono::system_clock::time_point	_statDecreaseTime;
		const int								STAT_DECREASE_TIME;
		const int								EVO_TIME;


		const TextureManager*					_textureManager;

		Inventory						_inventory;

		static Pet*						_instance;
	};
}

