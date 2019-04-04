/*
*@author: Greg VanKampen & Vaughn Rowse
*@file: World.cpp
*@description: A controller to handle collisions and events
*/
#include "World.h"
#include"Frog.h"
#include "Pickup.h"
#include "ParticleNode.h"
#include <SFML\Graphics\RenderTarget.hpp>
#include "SoundNode.h"
#include <iostream>
#include <time.h>
#include <random>
namespace GEX {

	namespace
	{
		const std::map<ObstacleType, ObstacleData> TABLE = initalizeObstacleData();
	}
	// car2
	// car3
	// truck

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

	//Manages players movement patterns created from world interaction
	void World::adaptPlayerPosition() {
		//if (_player->isOnPlatform())
		//{
		//	updatePlayerOnPlatform();
		//	// move with platform
		//}
		//else
		//{
		//	_player->setVelocity(0.f, 0.f);
		//}

		////keep player in bounds
		//const float BORDER_DISTANCE_HORIZONTAL = 40.f;
		//const float BORDER_DISTANCE_BOTTOM = 20.f;
		//const float BORDER_DISTANCE_TOP = 100.f;
		//sf::FloatRect viewBounds(_worldview.getCenter() - _worldview.getSize() / 2.f, _worldview.getSize()); //ASK
		//sf::Vector2f position = _player->getPosition();
		//position.x = std::max(position.x, viewBounds.left + BORDER_DISTANCE_HORIZONTAL);
		//position.x = std::min(position.x, viewBounds.left + viewBounds.width - BORDER_DISTANCE_HORIZONTAL);
		//position.y = std::max(position.y, viewBounds.top + BORDER_DISTANCE_TOP);
		//position.y = std::min(position.y, viewBounds.top + viewBounds.height - BORDER_DISTANCE_BOTTOM);
		//_player->setPosition(position);
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

	//check if player is currently active
	bool World::hasAlivePlayer() const
	{
		//return _player->getLives() > 0 || _player->isDead();
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
		//Command command;
		//command.category = Category::Type::KillObstacle;
		//command.action = derivedAction<Entity>([this](Entity& e, sf::Time dt) 
		//{
		//	int i = 1;
		//	if (!getSpawnerBounds().intersects(e.getBoundingBox())) {
		//		e.remove();
		//	}
		//});
		//_command.push(command);
		//command.category = Category::Type::PlatformObstacle;
		//_command.push(command);
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
		_sounds.play(s);
	}



	//loads textures
	void World::loadTextures()
	{
		_textures.load(GEX::TextureID::Landscape, "Media/Textures/room.png");
		_textures.load(GEX::TextureID::EggBaby, "Media/Textures/pets/eggie/baby_egg.png");
		_textures.load(GEX::TextureID::MelonChan, "Media/Textures/pets/melon-chan/melon-chan.png");
		_textures.load(GEX::TextureID::TouchFuzzy, "Media/Textures/pets/touch-fuzzy/touch_fuzzy.png");
		_textures.load(GEX::TextureID::Slip, "Media/Textures/pets/slip/slip.png");
		_textures.load(GEX::TextureID::Lily, "Media/Textures/pets/lily/lily.png");
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
		sf::Texture& texture = _textures.get(TextureID::Landscape);
		sf::IntRect textureRect(_worldBounds);
		texture.setRepeated(false);
		std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
		backgroundSprite->setPosition(_worldBounds.left, _worldBounds.top);
		backgroundSprite->scale(2, 2);
		_sceneLayers[Background]->attachChild(std::move(backgroundSprite));

		//add player aircraft & game objects
		//std::unique_ptr<Frog> playerEntity(new Frog(_textures));
		//playerEntity->setPosition(_spawnPosition);
		//_player = playerEntity.get();
		//_sceneLayers[UpperField]->attachChild(std::move(playerEntity));
		

		//Obstacles
		//addObstacles();
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
		////build list of colliding pairs of scenenodes
		//std::set<SceneNode::Pair> collisionPairs;
		//_sceneGraph.checkSceneCollision(_sceneGraph, collisionPairs);
		//_player->setIsOnPlatform(false);
		//for (SceneNode::Pair pair : collisionPairs) {
		//	if (matchesCategories(pair, Category::Type::Frog, Category::Type::KillObstacle)) {
		//		if(_player->getLives() > 0)
		//			_player->die();
		//	}
		//	if (matchesCategories(pair, Category::Type::Frog, Category::Type::Finish)) {
		//		auto& finish = static_cast<Obstacle&>(*(pair.second));
		//		if (!finish.hasFinishFrog() && !finish.hasCroc()) {
		//			finish.setHasFinishFrog(true);
		//			addScore(500);
		//			if (_lilypadCounter < 5)
		//				_lilypadCounter++;
		//			// checks if all lily pads have been filled
		//			if (_lilypadCounter == 5)
		//			{
		//				// increases level by resetting all lily pads and increasing level counter
		//				increaseLevel();
		//			}
		//			resetPlayer();
		//		}
		//		else {
		//			if (_player->getLives() > 0)
		//				_player->die();
		//		}
		//	}
		//	if (matchesCategories(pair, Category::Type::Frog, Category::Type::PlatformObstacle))
		//	{
		//		auto& platform = static_cast<Obstacle&>(*(pair.second));
		//		if(platform.isActive())
		//			_player->setIsOnPlatform(true);
		//		else
		//			_player->setIsOnPlatform(false);
		//	}
		//	if (matchesCategories(pair, Category::Type::Frog, Category::Type::BonusObstacle)) {
		//		auto& bonus = static_cast<Obstacle&>(*(pair.second));
		//		addScore(1000);
		//		bonus.destroy();
		//	}
		//}
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
