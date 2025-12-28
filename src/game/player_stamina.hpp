#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	struct Player;

	struct PlayerStaminaFields
	{
		MonoBehaviourFields* MonoBehaviourFields;//MonoBehaviourFields MonoBehaviourFields;
		void* OutOfStaminaSource; // AudioSource
		void* OutOfBreathMale; // AudioClip[]
		void* OutOfBreathFemale; // AudioClip[]
		Player* Player;
		bool MaleSoundsOverride;
		bool FemaleSoundsOverride;
		bool IsMoving;
		bool CanSprint;
		bool IsSprinting;
		bool IsWalking;
		bool Draining;
		bool CanDrainStamina;
		bool NewIsSprinting;
		bool NewIsWalking;
		bool StaminaDrained;
		bool Delayed;
		float CurrentStaminaRecharge;
		float CurrentStamina;
		float RestoreDelay;
		void* OnStaminaDrained; // UnityEvent
		void* OnStaminaRestored; // UnityEvent
	};

	struct PlayerStamina
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		PlayerStaminaFields Fields;
	};

	DECLARE_POINTER(PlayerStamina_PreventStaminaDrainForTime, void (*)(float time, MethodInfo* methodinfo), "Assembly-CSharp", "", "PlayerStamina", "PreventStaminaDrainForTime", 1);
	DECLARE_POINTER(PlayerStamina_Update, void (*)(PlayerStamina* playerstamina, MethodInfo* methodinfo), "Assembly-CSharp", "", "PlayerStamina", "Update", 0);
}
