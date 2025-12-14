#pragma once
#include "sdk.hpp"
#include "ghost_info.hpp"

namespace menu::sdk
{
	enum class GhostState : int32_t
	{
		Idle,
		Wander,
		Hunting,
		FavoriteRoom,
		Light,
		Door,
		Throwing,
		FuseBox,
		Appear,
		DoorKnock,
		WindowKnock,
		CarAlarm,
		Flicker,
		CCTV,
		RandomEvent,
		GhostAbility,
		Mannequin,
		TeleportObject,
		Interact,
		SummoningCircle,
		MusicBox,
		Dots,
		Salt
	};

	struct GhostAIFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		void* StateMachine; // ???
		GhostState CurrentState;
		GhostInfo* GhostInfo;
		void* Agent; // NavMeshAgent
		void* GhostAudio; // GhostAudio
		void* GhostInteraction; // GhostInteraction
		void* GhostActivity;//GhostActivity*
		void* CurrentModel; // GhostModel
		void* HalloweenModel; // GhostModel
		void* HolidayModel; // GhostModel
		void* EasterModel; // GhostModel
		void* MaleGhostModels; // GhostModel[]
		void* FemaleGhostModels; // GhostModel[]
		bool CanSwapModel;
		int32_t CurrentShadowCastingMode; // ShadowCastingMode
		void* GhostBreadcrumbs; // List<Vector3>
		float BreadcrumbTimer;
		void* PlayerSensor; // LOSSensor
		bool GhostIsAppeared;
		Transform* RaycastPoint;
		Transform* HuntingRaycastPoint;
		Transform* FeetRaycastPoint;
		float DefaultSpeed;
		float SaltSpeedMultiplier;
		float IncenseSpeedMultiplier;
		float EventSpeedMultiplier;
		bool HasHuntedRecently;
		bool RemoveInteractionChanceBlock;
		Vector3 LastKnownHuntingLocation;
		void* HuntingPostProcessingVolume;//Gameobject*
		bool IsDemonAbilityHunt;
		bool IsHunting;
		bool IsUsingLights;
		bool DelayedBySmudgeStick;
		void* ActiveIncense; // WhiteSage
		float ActiveIncenseDuration;
		bool CanWander;
		bool CanFlashAppear;
		bool IsTrapped;
		Player* BansheeTarget;
		int32_t OnryoCandleBlowoutCounter;
		Vector3 LastInteractionPoint;
		void* NormalFlashValues; // float[]
		void* DeogenFlashValues; // float[]
		void* OniFlashValues; // float[]
		int32_t FlashIndexValue;
		int32_t AppearIndexValue;
		int32_t FlashAmount;
		int32_t ObakeModelIndex;
		int32_t ObakeArrayID;
		void* NormalAppearValues; // float[]
		void* DeogenOniAppearValues; // float[]
		void* PhantomAppearValues; // float[]
		float AppearTimer;
		void* Obake1Values; // int[]
		void* Obake2Values; // int[]
		void* Obake3Values; // int[]
		void* Obake4Values; // int[]
	};

	struct GhostAI
	{
		void* Clazz;
		void* Monitor;
		GhostAIFields Fields;
	};


	DECLARE_POINTER(GhostAI_Hunting, void(*)(GhostAI* gai, bool isHunting, int a1, void* PhotonMessageInfo, method_info* mi), "Assembly-CSharp", "", "GhostAI",
		"Hunting", 3);//tood add notifcation for this

	DECLARE_POINTER(GhostAI_Start, void(*)(GhostAI* gai, method_info* mi), "Assembly-CSharp", "", "GhostAI", "Start", 0);

	DECLARE_POINTER(GhostAI_Update, void(*)(GhostAI* gai, method_info* mi), "Assembly-CSharp", "", "GhostAI", "Update", 0);
}
