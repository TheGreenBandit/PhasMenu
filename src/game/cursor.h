#pragma once

#include "common.hpp"

namespace menu::SDK
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

	DECLARE_POINTER(Cursor_Set_Visible, void(*)(bool visible, method_info* methodinfo), "UnityEngine.CoreModule", "UnityEngine", "Cursor", "set_visible", 1);

	DECLARE_POINTER(Cursor_Get_LockState, CursorLockMode(*)(method_info* methodinfo), "UnityEngine.CoreModule", "UnityEngine", "Cursor", "get_lockState", 0);

	DECLARE_POINTER(Cursor_Set_LockState, void(*)(CursorLockMode mode, method_info* methodinfo), "UnityEngine.CoreModule", "UnityEngine", "Cursor", "set_lockState", 1);
}