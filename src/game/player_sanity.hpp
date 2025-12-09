#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	struct Player;

	struct PlayerSanityFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		void* View; // PhotonView
		Player* Player;
		float Insanity;
		float SanityUpdateTimer;
		float SanityCheckTimer;
		void* ShadowRenderTexture; // RenderTexture
		bool PlayerIsInLight;
		float DifficultyRate;
		bool IsCursed;
		float NormalSanityRate;
		float SetupSanityRate;
		bool SanityChallengeHasBeenSet;
		void* NearbyFireLights; // List<Candle>
	};

	struct PlayerSanity
	{
		void* Clazz;
		void* Monitor;
		PlayerSanityFields Fields;
	};

	DECLARE_POINTER(PlayerSanity_SetInsanity, void(*)(PlayerSanity* playerSanity, int insanity, method_info* methodInfo), "Assembly-CSharp", "", "PlayerSanity",
	                       "SetInsanity", 1);
}
