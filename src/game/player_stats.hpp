#pragma once
#include "sdk.hpp"
#include "level_controller.hpp"

namespace menu::sdk
{
	struct PlayerStatsFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		Player* Player;//0x28
		void* SetupPhaseController;//0x30
		LevelController* LevelController;//0x38
		void* LevelStats;//0x40
	};

	struct PlayerStats
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		PlayerStatsFields Fields;
	};	
}
