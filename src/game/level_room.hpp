#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	struct LevelRoomFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* LightSwitches; // List<LightSwitch>
		void* Doors; // Door[]
		void* RoomColliders; // List<Collider>
		Transform* MirrorCameraOverride;
		void* AudioReverbZone; // AudioReverbZone
		int32_t RoomType;
		void* EvidenceSpawnOverride; // BoxCollider
		int32_t FloorType;
		String* RoomName;
		float Temperature;
		float MaximumTemperature;
		float MinimumTemperature;
		float CurrentPlayerInRoomTimer;
		bool AllowGhostToRoamOtherFloor;
		bool IsMostlyDarkRoom;
		bool RoomModifierActive;
		bool CanRunPlayerEnter;
	};

	struct LevelRoom
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		LevelRoomFields Fields;
	};
}
