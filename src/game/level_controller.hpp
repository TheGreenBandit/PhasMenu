#pragma once
#include "sdk.hpp"
#include "ghost_ai.hpp"
#include "key.hpp"

namespace menu::sdk
{
	struct LevelControllerFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		void* SmallMapVariations; // LevelController.SmallMapVariation[]
		LevelRoom* CurrentPlayerRoom;
		LevelRoom* CurrentGhostRoom;
		GhostAI* CurrentGhost;
		void* Doors; //doorarray*
		void* AllGhostRooms; // LevelRoom[]
		void* AllInteriorRooms; // LevelRoom[]
		void* FuseboxSpawnLocations; // Transform[]
		void* MannequinTeleportSpots; // Transform[]
		LevelRoom* OutsideRoom;
		bool IsOutsideMap;
		FuseBox* FuseBox;
		void* GameController; //GameController*
		void* SoundController; // SoundController
		void* ItemSpawner; // ItemSpawner
		void* ExitDoors;//doorarray*
		void* LevelAreas; // LevelArea[]
		void* Crucifix; // List<Crucifix>
		void* FireSources; // List<FireSource>
		void* AllEquipment; // List<PhotonObjectInteract>
		StringArray* PossibleMaleFirstNames; // string[]
		StringArray* PossibleFemaleFirstNames; // string[]
		StringArray* PossibleLastNames; // string[]
		Key* MainDoorKey; // Key
		void* AllBlockedZones; // BlockedZone[]
		int IntermediateZonesBlocked;
		int ProZonesBlocked;
		int NightmareZonesBlocked;
		void* AllClothDoors; // Transform[]
		void* FPS; // List<float>
	};

	struct LevelController
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		LevelControllerFields Fields;
	};
}
