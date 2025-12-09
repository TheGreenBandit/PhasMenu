#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	enum class RigidbodyConstraints : int32_t
	{
		None = 0,
		FreezePositionX = 2,
		FreezePositionY = 4,
		FreezePositionZ = 8,
		FreezePosition = 14,
		FreezeRotationX = 16,
		FreezeRotationY = 32,
		FreezeRotationZ = 64,
		FreezeRotation = 112,
		FreezeAll = 126
	};

	struct Rigidbody
	{
	};

	DECLARE_POINTER(Rigidbody_Set_IsKinematic, void(*)(Rigidbody* rigidbody, bool isKinematic, method_info* methodInfo), "UnityEngine.PhysicsModule", "UnityEngine",
		"Rigidbody", "set_isKinematic", 1);

	DECLARE_POINTER(Rigidbody_Get_Constraints, RigidbodyConstraints(*)(Rigidbody* rigidbody, method_info* methodInfo), "UnityEngine.PhysicsModule", "UnityEngine",
		"Rigidbody", "get_constraints", 0);

	DECLARE_POINTER(Rigidbody_Set_Constraints, void(*)(Rigidbody* rigidbody, RigidbodyConstraints contraints, method_info* methodInfo), "UnityEngine.PhysicsModule",
		"UnityEngine", "Rigidbody", "set_constraints", 1);
}
