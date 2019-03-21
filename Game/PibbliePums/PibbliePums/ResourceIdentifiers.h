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
		ShopScreen,
		StatsScreen,
		MinigameScreen,
		Explosion,Particle,
		FinishLine,
		StatIcon,
		FoodInvIcon,
		GameIcon,
		ShopIcon,
		Cursor,
		CPUCursor,

		HappinessIcon,
		FullnessIcon,
		WeightIcon,
		MoneyIcon,

		RockIcon,
		PaperIcon,
		ScissorsIcon,

		BabyMeter0,
		BabyMeter1,
		BabyMeter2,
		BabyMeter3,

		EggIcon,
		MelonChanIcon

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