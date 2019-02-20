/*
*@author: Greg VanKampen & Vaughn Rowse
*@file: World.h
*@description: A controller to handle collisions and events
*/
#pragma once
#include<SFML/System.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "SceneNode.h"
#include "SpriteNode.h"
#include "TextureManager.h"
#include "Pet.h"
#include "CommandQueue.h"
#include <vector>
#include "PostEffect.h"
#include "BloomEffect.h"
#include "SoundPlayer.h"
#include "Obstacle.h"
#include "FontManager.h"
#include <stdlib.h>
#include <time.h>
#include "Icon.h"



namespace sf {
	class RenderTarget;
}
namespace GEX {
	class World
	{
	public:
		World(sf::RenderTarget& outputTarget,SoundPlayer& sounds);
		~World();
		void							update(sf::Time dt);
		void adaptPlayerPosition();
		void							draw();
		CommandQueue&					getCommandQueue();

		sf::FloatRect					getViewBounds() const;
		sf::FloatRect					getSpawnerBounds() const;
		bool							hasAlivePlayer() const;
		bool							hasPlayerReachedEnd() const;
		void							destroyEntitesOutOfView();
		void							iconNavLeft();
		void							iconNavRight();
		StateID							getCurrentIconState();

		enum Layer {
			Background = 0,
			LowerField,
			UpperField,
			LayerCount
		};
		struct SpawnPoint {
			SpawnPoint(ObstacleType type, float x, float y)
			:type(type),
			x(x),
			y(y){}
			ObstacleType type;
			float x;
			float y;
		};
	private:
		void							loadTextures();
		void							buildScene();
		void							handleCollisions();
		void							initalizeIcons();
	private:
		sf::RenderTarget&				_target;
		sf::RenderTexture				_sceneTexture;
		sf::View						_worldview;
		TextureManager					_textures;
		//SoundPlayer&					_sounds;



		SceneNode						_sceneGraph;
		std::vector<SceneNode*>			_sceneLayers;
		CommandQueue					_command;
		sf::FloatRect					_worldBounds;
		Pet*							_pet;
		sf::Vector2f					_spawnPosition;
		std::vector<Icon *>				_icons;
		int								_selectedIcon;

	};


}

