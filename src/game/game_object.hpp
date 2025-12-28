#pragma once
#include "sdk.hpp"
#include "object.hpp"
#include "type.hpp"

namespace menu::sdk
{
	struct GameObject
	{
	};

	// GameObject[]
	struct GameObjectArray
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		Il2CppArrayBounds* Bounds; // Il2CppArrayBounds
		Il2CppArraySize* MaxLength; // Il2CppArraySizeT
		GameObject* Vector[65535];
	};

	DECLARE_POINTER(GameObject_GetComponentByName, void* (*)(GameObject* gameObject, String* type, MethodInfo* mi), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "GetComponentByName", 1);

	DECLARE_POINTER(GameObject_Get_Transform, Transform* (*)(GameObject* gameObject, MethodInfo* mi), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "get_transform", 0);

	DECLARE_POINTER(GameObject_FindGameObjectsWithTag, GameObjectArray* (*)(String* tag, MethodInfo* mi), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "FindGameObjectsWithTag", 1);

	DECLARE_POINTER(GameObject_FindObjectsOfType, Object__Array* (*)(Type* type, MethodInfo* mi), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "FindGameObjectsOfType", 1);
	
	DECLARE_POINTER(GameObject_Set_Layer, void* (*)(GameObject* gameObject, int layer, MethodInfo* mi), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "set_layer", 1);
}
