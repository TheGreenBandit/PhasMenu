#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	struct GameObject
	{
	};

	// GameObject[]
	struct GameObjectArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
		GameObject* Vector[65535];
	};

	DECLARE_POINTER(GameObject_GetComponentByName, void* (*)(GameObject* gameObject, String* type, method_info* mi), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "GetComponentByName", 1);

	DECLARE_POINTER(GameObject_Get_Transform, Transform* (*)(GameObject* gameObject, method_info* mi), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "get_transform", 0);

	DECLARE_POINTER(GameObject_FindGameObjectsWithTag, GameObjectArray* (*)(String* tag, method_info* mi), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "FindGameObjectsWithTag", 1);

	DECLARE_POINTER(GameObject_Set_Layer, void* (*)(GameObject* gameObject, int layer, method_info* mi), "UnityEngine.CoreModule", "UnityEngine", "GameObject", "set_layer", 1);
}
