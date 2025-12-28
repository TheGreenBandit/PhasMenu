#pragma once
#include "sdk.hpp"
#include "vector3.hpp"
#include "transform.hpp"
#include "matrix.hpp"
#include "quaternion.hpp"

namespace menu::sdk
{
	struct Transform
	{
		int* childCount;
		Vector3* eulerAngles;
		Vector3* foward;
		bool* hasChanged;
		int* hieracrchyCapacity;
		Vector3* localEulerAngles;
		Vector3* localPosition;
		Vector3* localRotation;
		Vector3* localScale;
		Matrix4x4* localToWorldMatric;
		Vector3* lossyScale;
		Transform* parent;
		Transform* parentInternal;
		Vector3* position;
		Vector3* right;
		Transform* root;
		Quaternion* rotation;
		Vector3* up;
		Matrix4x4* worlToLocalMatrix;
	};

	DECLARE_POINTER(Transform_Get_Position, Vector3(*)(Transform* transform, MethodInfo* mi), "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_position",
		0)

	DECLARE_POINTER(Transform_Set_Position, void(*)(Transform* transform, Vector3 position, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform",
		"set_position", 1)

	DECLARE_POINTER(Transform_Get_Right, Vector3(*)(Transform* transform, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_right", 0)

	DECLARE_POINTER(Transform_Get_Up, Vector3(*)(Transform* transform, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_up", 0)

	DECLARE_POINTER(Transform_Get_Forward, Vector3(*)(Transform* transform, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_forward", 0)

	//DECLARE_POINTER(Transform_Get_Rotation, Quaternion(*)(Transform* transform, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform",
	//	"get_rotation", 0)

	//DECLARE_POINTER(Transform_Set_Rotation, void(*)(Transform* transform, Quaternion rotation, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform",
	//	"set_rotation", 1)

	DECLARE_POINTER(Transform_Get_Parent, Transform* (*)(Transform* transform, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_parent", 0)

	DECLARE_POINTER(Transform_Set_Parent, void(*)(Transform* transform, Transform* parent, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Transform",
		"set_parent", 1)
}
