#pragma once
#include "Entity.h"
#include "TextureManager.h"
#include <SFML\Graphics\Sprite.hpp>
#include "Animation2.h"
#include <functional>
#include <random>
#include <time.h>
namespace GEX {
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
		Pet(const TextureManager& textures, bool flippable);
		virtual void				drawcurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		unsigned int				getCategory() const override;
		sf::FloatRect				getBoundingBox()const override;
		
	protected:
		void						updateCurrent(sf::Time dt, CommandQueue& commands) override;
	private:
		void						remove() override;
		void						updateMovement(sf::Time dt);
	private:
		sf::Sprite						_sprite;
		Position						_position;
		Facing							_facing;
		sf::Time						_movementTimer;
		bool							_isFlippable;
	};
}

