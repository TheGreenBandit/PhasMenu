#pragma once

#include "sdk.hpp"

namespace menu::sdk
{
	struct ExitLevel
	{
	};

	DECLARE_POINTER(ExitLevel_Exit, void(*)(ExitLevel* el, void* photonMessageInfo, MethodInfo* methodInfo), "Assembly-CSharp", "", "ExitLevel", "Exit", 1);
}