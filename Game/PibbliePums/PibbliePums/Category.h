/*
*@author: Greg VanKampen
*@file: Category.h
*@description: Stores entity Categories
*/
#pragma once

namespace Category {
	enum Type
	{
		None = 0,
		Scene = 1 << 0,
		Pet = 1 << 1,
		AirSceneLayer = 1 << 2,
		SoundEffect = 1 << 3,

	};
}