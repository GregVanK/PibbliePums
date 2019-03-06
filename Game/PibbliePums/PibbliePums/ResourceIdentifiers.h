/*
*@author: Greg VanKampen
*@file: ResourceIdentifiers.h
*@description: Holds IDs of resources
*/
#pragma once
namespace GEX {
	enum class TextureID { 
		Landscape,
		Pet,
		EggBaby,
		MelonChan,
		Jungle,
		Entities,
		LilyPad,
		Frog,
		TitleScreen, 
		GexScreen,
		InventoryScreen,
		StatsScreen,
		Explosion,Particle,
		FinishLine,
		StatIcon,
		FoodInvIcon,
		GameIcon,
		ShopIcon,
		Cursor
	};
	enum class FontID {
		Main
	};
	enum class MusicID {
		MenuTheme,
		MissionTheme
	};
	enum class SoundEffectID {
		FroggerMove,
		FroggerDie,
		Jump,
	};
}