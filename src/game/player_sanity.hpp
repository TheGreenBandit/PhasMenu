#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	struct Player;
	struct PhotonView;

	struct PlayerSanityFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		PhotonView* View; // PhotonView
		Player* Player;
		float Insanity;//100 -insanity
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
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		PlayerSanityFields Fields;
	};

	DECLARE_POINTER(PlayerSanity_SetInsanity, void(*)(PlayerSanity* playerSanity, int insanity, MethodInfo* methodInfo), "Assembly-CSharp", "", "PlayerSanity",
	                       "SetInsanity", 1);
}
