#pragma once
#include "sdk.hpp"
#include "transform.hpp"
#include "game_object.hpp"

namespace menu::sdk
{
	struct Component
	{
	};

	DECLARE_POINTER(Component_Get_Transform, Transform* (*)(Component* component, MethodInfo* mi), "UnityEngine.CoreModule", "UnityEngine", "Component",
		"get_transform", 0);

	DECLARE_POINTER(Component_Get_GameObject, GameObject* (*)(Component* component, MethodInfo* mi), "UnityEngine.CoreModule", "UnityEngine", "Component",
		"set_transform", 1);
}
