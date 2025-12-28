#pragma once
#include "sdk.hpp"
#include "ghost_traits.hpp"

namespace menu::sdk
{
	struct LevelRoom;
	struct GhostAI;

	struct GhostInfoFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields; // MonoBehaviourPun derived class field
		GhostTraits GhostTraits;//use for getting name n stuff
		GhostAI* Ghost;
		LevelRoom* FavouriteRoom;
		float ActivityMultiplier;
		bool HasSetEvidence;
	};

	struct GhostInfo
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		GhostInfoFields Fields;
	};
}
