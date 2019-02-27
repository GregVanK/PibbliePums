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
		Explosion,Particle,
		FinishLine,
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