#pragma once
//somehow this is turning out to be the main include class because sdk.hpp dont like me
#include "sdk.hpp"
#include "vector2.hpp"
#include "vector3.hpp"
#include "mouse_look.hpp"
#include "camera.hpp"
#include "physics_character_controller.hpp"

namespace menu::sdk
{
	struct FirstPersonControllerFields
	{
		MonoBehaviourFields MonoBehaviourFields;
		bool CanMove;
		bool CanTurn;
		bool IsSprinting;
		bool IsMoving;
		bool CanSprint;
		float RunstepLength; // range 0 - 1
		float StickToGroundForce;
		float GravityMultiplier;
		MouseLook* MouseLook;
		bool UseFovKick;
		void* FovKick; // FOVKick
		bool UseHeadBob;
		bool ToggleSprint;
		void* HeadBob; // CurveControlledBob
		float StepInterval;
		Camera* Camera;
		Vector2 Input;
		Vector3 MoveDir;
		PhysicsCharacterController* CharacterController;
		bool Crouching;
		float CurrentSpeed;
		Vector3 DesiredMove;
		RaycastHit HitInfo;
		void* OnStartSprint; // UnityEvent
		void* OnStartWalk; // UnityEvent
	};

	struct FirstPersonController
	{
		void* Clazz;
		void* Monitor;
		FirstPersonControllerFields Fields;
	};

	DECLARE_POINTER(FirstPersonController_Update, void (*)(FirstPersonController* firstPersonController, method_info* methodInfo), "Assembly-CSharp", "", "FirstPersonController", "Update", 0);
}
