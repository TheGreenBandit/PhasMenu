#pragma once
#include "sdk.hpp"
#include "transform.hpp"
#include "mono_behaviour.hpp"

namespace menu::sdk
{
	struct FuseBoxFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		int32_t FuseBoxType; // FuseBox.???
		void* Rends; // Renderer[]
		void* Lights; // Light[]
		void* VolumetricLights;
		void* LightPulse; // LightPulse[]
		void* RendsToTurnOff; // Renderer[]
		void* LightSourcesWithoutSwitches; // LightSource[]
		void* RotatingObjects;
		void* LoopSource; // AudioSource
		void* Noise; // Noise
		/*Transform* */void* ParentObject;
		void* OnClip; // AudioClip
		void* OffClip; // AudioClip
		bool IsOn;
		void* Switches; // List<LightSwitch>
		void* PhotonInteract; // PhotonObjectInteract
		int CurrentOnLights;
		int MaxLights;
		Transform* MapIcon;
		Transform* shakeObject;
		Transform* HandleObject;
		Vector3 HandleOnAngle;
		Vector3 HandleOffAngle;
		/*GameObject**/void* BrokenFuseBoxObject;
		bool IsBroken;
		void* OnFuseBoxTrip; // FuseBox.FuseBoxTripEvent
	};

	struct FuseBox
	{
		void* Clazz;
		void* Monitor;
		FuseBoxFields Fields;
	};

	DECLARE_POINTER(FuseBox_Start, void (*)(FuseBox* fuseBox, method_info* methodInfo), "Assembly-CSharp", "", "FuseBox", "Start", 0);//get position on level start

	DECLARE_POINTER(FuseBox_Use, void (*)(FuseBox* fuseBox, method_info* methodInfo), "Assembly-CSharp", "", "FuseBox", "Use", 0);//use to turn on remotely
}
