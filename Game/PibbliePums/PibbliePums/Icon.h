#pragma once
#include <SFML\Graphics\Sprite.hpp>
#include "TextureManager.h"
#include "Entity.h"
#include "State.h"
#include <vector>
namespace GEX {
	class Icon : public Entity
	{
	public:
		enum class IconID {
			FoodInv,
			Games,
			Shop,
			Stats
		};
		Icon(const TextureManager& textures, IconID id, bool isActive);
		virtual void				drawcurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		unsigned int				getCategory() const override;
		sf::FloatRect				getBoundingBox()const override;
		void						toggleActive() { _isActive = !_isActive;};
		StateID						getState();
	protected:
		void						updateCurrent(sf::Time dt, CommandQueue& commands) override;

	private:
		sf::Sprite					_sprite;
		bool						_isActive;
		StateID						_state;


	};
}

