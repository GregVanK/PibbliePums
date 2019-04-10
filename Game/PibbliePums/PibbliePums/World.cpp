/*
*@author: Greg VanKampen & Vaughn Rowse
*@file: World.cpp
*@description: A controller to handle collisions and events
*/
#include "World.h"



#include <SFML\Graphics\RenderTarget.hpp>
#include "SoundNode.h"
#include <iostream>
#include <time.h>
#include <random>
namespace GEX {


	World::World(sf::RenderTarget& outputTarget, SoundPlayer& sounds) : _target(outputTarget),
		_worldview(outputTarget.getDefaultView()),
		_textures(),
		_sceneGraph(),
		_sceneLayers(),
		_worldBounds(0.f, 0.f, _worldview.getSize().x, _worldview.getSize().y),
		_spawnPosition(_worldview.getSize().x / 2.f, (_worldview.getSize().y / 4.f)*3.f),
		_selectedIcon(0),
		_sounds(sounds)
	{

		_sceneTexture.create(_target.getSize().x, _target.getSize().y);
		loadTextures();
		
		srand(time(NULL));

		buildScene();
		//create and connect pet

		PetName pettype;
		switch (rand() % 2) {
		case 0:
			pettype = PetName::Slip;
			break;
		default:
			pettype = PetName::EggBaby;
			break;
		}

		std::unique_ptr<Pet> petEntity(new Pet(pettype, _textures, true));
		petEntity->setPosition(_spawnPosition);
		_pet = petEntity.get();
		_sceneLayers[UpperField]->attachChild(std::move(petEntity));
		
		//prep the view
		_worldview.setCenter(_worldview.getSize().x / 2.f, _worldBounds.height - _worldview.getSize().y / 2.f);
		initalizeIcons();
	}
	World::~World()
	{
	}

	void World::update(sf::Time dt)
	{
		//run all commands in queue
		while (!_command.isEmpty()) {
			_sceneGraph.onCommand(_command.pop(), dt);
		}
		//handle special events
		handleCollisions();
		_sceneGraph.removeWrecks();
		_sceneGraph.update(dt,_command);
		//world events
		destroyEntitesOutOfView();
	}
	//render the game
	void World::draw()
	{
		_target.setView(_worldview);
		_target.draw(_sceneGraph);
		
	}
	CommandQueue & World::getCommandQueue()
	{
		return _command;
	}
	//gets display area
	sf::FloatRect World::getViewBounds() const
	{
		return sf::FloatRect(_worldview.getCenter() - _worldview.getSize() / 2.f, _worldview.getSize());
	}

	//gets removal area
	sf::FloatRect World::getSpawnerBounds() const
	{
		sf::FloatRect bounds = getViewBounds();
		bounds.left -= 100.f;
		bounds.width += 200.f;
		bounds.top -= 100.f;
		bounds.height += 200.f;
		return bounds;
	}

	bool World::hasAlivePlayer() const
	{
		return true;
	}

	//unused
	bool World::hasPlayerReachedEnd() const
	{
		return false;
	}

	//removes obstacles that leave the view
	void World::destroyEntitesOutOfView()
	{
	}

	void World::iconNavLeft()
	{
		_icons[_selectedIcon]->toggleActive();
		if (_selectedIcon == 0) {
			_selectedIcon = _icons.size() - 1;
		}
		else
		{
			_selectedIcon--;
		}
		_icons[_selectedIcon]->toggleActive();
	}

	void World::iconNavRight()
	{
		_icons[_selectedIcon]->toggleActive();
		if (_selectedIcon ==  _icons.size() - 1) {
			_selectedIcon = 0;
		}
		else
		{
			_selectedIcon++;
		}
		_icons[_selectedIcon]->toggleActive();	
	}
	StateID World::getCurrentIconState()
	{
		return _icons[_selectedIcon]->getState();
	}

	void World::playSound(SoundEffectID s)
	{
		_sounds.removeStoppedSounds();
		_sounds.play(s);
	}
	//loads textures
	void World::loadTextures()
	{
		_textures.load(GEX::TextureID::RoomBackground, "Media/Textures/room.png");
		_textures.load(GEX::TextureID::EggBaby, "Media/Textures/pets/eggie/baby_egg.png");
		_textures.load(GEX::TextureID::MelonChan, "Media/Textures/pets/melon-chan/melon-chan.png");
		_textures.load(GEX::TextureID::TouchFuzzy, "Media/Textures/pets/touch-fuzzy/touch_fuzzy.png");
		_textures.load(GEX::TextureID::Slip, "Media/Textures/pets/slip/slip.png");
		_textures.load(GEX::TextureID::Lily, "Media/Textures/pets/lily/lily.png");
		_textures.load(GEX::TextureID::DandyLion, "Media/Textures/pets/dandy-lion/dandy-lion.png");
		_textures.load(GEX::TextureID::Death, "Media/Textures/pets/death/death.png");
		_textures.load(GEX::TextureID::StatIcon, "Media/Textures/icons/stats.png");
		_textures.load(GEX::TextureID::FoodInvIcon, "Media/Textures/icons/fruit.png");
		_textures.load(GEX::TextureID::GameIcon, "Media/Textures/icons/games.png");
		_textures.load(GEX::TextureID::ShopIcon, "Media/Textures/icons/dollar_sign.png");
	}

	//inital construction of the world
	void World::buildScene()
	{
		//initalizes layers
		for (int i = 0; i < LayerCount; ++i) {
			auto category = (i == UpperField) ? Category::Type::AirSceneLayer : Category::Type::None;
			SceneNode::Ptr layer(new SceneNode(category));
			_sceneLayers.push_back(layer.get());
			_sceneGraph.attachChild(std::move(layer));
		}

		//sets background
		sf::Texture& texture = _textures.get(TextureID::RoomBackground);
		sf::IntRect textureRect(_worldBounds);
		texture.setRepeated(false);
		std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
		backgroundSprite->setPosition(_worldBounds.left, _worldBounds.top);
		backgroundSprite->scale(2, 2);
		_sceneLayers[Background]->attachChild(std::move(backgroundSprite));

	}

	//checks collision categories pairs
	bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
	{
		unsigned int category1 = colliders.first->getCategory();
		unsigned int category2 = colliders.second->getCategory();

		if (type1 & category1  && type2 & category2) {
			return true;
		}
		if (type1 & category2  && type2 & category1) {
			std::swap(colliders.first, colliders.second);
			return true;
		}
		return false;
	}

	//handles collisions between player and obstacles
	void World::handleCollisions()
	{
	}

	void World::initalizeIcons()
	{
		const float TOP_ROW = 40;
		const float ICON_PADDING = 50;
		std::unique_ptr<Icon> statsIcon(new Icon(_textures, Icon::IconID::Stats, true));
		std::unique_ptr<Icon> foodIcon(new Icon(_textures, Icon::IconID::FoodInv, false));
		std::unique_ptr<Icon> gameIcon(new Icon(_textures, Icon::IconID::Games, false));
		std::unique_ptr<Icon> shopIcon(new Icon(_textures, Icon::IconID::Shop, false));
		_icons.push_back(statsIcon.get());
		_icons.push_back(foodIcon.get());
		_icons.push_back(gameIcon.get());
		_icons.push_back(shopIcon.get());
		_sceneLayers[UpperField]->attachChild(std::move(statsIcon));
		_sceneLayers[UpperField]->attachChild(std::move(foodIcon));
		_sceneLayers[UpperField]->attachChild(std::move(gameIcon));
		_sceneLayers[UpperField]->attachChild(std::move(shopIcon));
		for (int i = 0; i < _icons.size(); i++) {
			//gets a relative position based on amount of icons loaded
			float xPos = (((i) * (getViewBounds().width / (_icons.size()))) + ICON_PADDING);
			_icons[i]->setPosition(sf::Vector2f(xPos, TOP_ROW));
		}
	}
}
