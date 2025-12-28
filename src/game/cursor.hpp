#pragma once

#include "sdk.hpp"

namespace menu::sdk
{
	enum class CursorLockMode : int32_t
	{
		None,
		Locked,
		Confined
	};

	struct Cursor
	{
	};

	DECLARE_POINTER(Cursor_Set_Visible, void(*)(bool visible, MethodInfo* methodinfo), "UnityEngine.CoreModule", "UnityEngine", "Cursor", "set_visible", 1);

	DECLARE_POINTER(Cursor_Get_LockState, CursorLockMode(*)(MethodInfo* methodinfo), "UnityEngine.CoreModule", "UnityEngine", "Cursor", "get_lockState", 0);

	DECLARE_POINTER(Cursor_Set_LockState, void(*)(CursorLockMode mode, MethodInfo* methodinfo), "UnityEngine.CoreModule", "UnityEngine", "Cursor", "set_lockState", 1);
}