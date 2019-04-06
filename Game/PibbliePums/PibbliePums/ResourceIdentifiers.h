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
		TouchFuzzy,
		Slip,
		Lily,
		DandyLion,

		Death,


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

		TeenMeter0,
		TeenMeter1,
		TeenMeter2,
		TeenMeter3,
		TeenMeter4,

		AdultMeter0,
		AdultMeter1,
		AdultMeter2,
		AdultMeter3,
		AdultMeter4,
		AdultMeter5,

		EggIcon,
		MelonChanIcon,
		TouchFuzzyIcon,
		SlipIcon,
		LilyIcon,
		DandyLionIcon

	};
	enum class FontID {
		Main
	};
	enum class MusicID {
		Room,
		Stats,
		Inventory,
		MiniGame,
		Shop
	};
	enum class SoundEffectID {
		FroggerMove,
		FroggerDie,
		Jump,
		CursorMove,
		Select,
		Back,
	};
}