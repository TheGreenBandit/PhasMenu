#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	struct LevelRoom;
	struct GhostAI;

	struct GhostInfoFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields; // MonoBehaviourPun derived class field
		/*GhostTraits */ void* GhostTraits;//use for getting name n stuff
		GhostAI* Ghost;
		LevelRoom* FavouriteRoom;
		float ActivityMultiplier;
		bool HasSetEvidence;
	};

	struct GhostInfo
	{
		void* Clazz;
		void* Monitor;
		GhostInfoFields Fields;
	};
}
