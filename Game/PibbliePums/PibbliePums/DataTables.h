/**
*@author: Greg VanKampen & Vaugn Rowse
*@file: Datatable.cpp
*@description: Storage of attributes for entities
*/
#pragma once
#include "TextureManager.h"
#include "Animation2.h"
#include <map>
#include "Pet.h"

namespace GEX {
	struct Direction {
		Direction(float a, float b)
			:angle(a),
			distance(b) 
		{}

		float					angle;
		float					distance;
	};

	struct PetData {
		TextureID								texture;
		sf::IntRect								textureRect;
		std::map<Pet::State, Animation2>	animations;
		std::vector<Direction>					directions;
		float									speed;
		bool									isFlippable;
		TextureID								iconTexture;
		PetName									nextEvolution;
		AgeGroup								ageGroup;
	};
	std::map<PetName, PetData>				initalizePetData();
	

}
