#pragma once
#include "sdk.hpp"
#include "matrix.hpp"

namespace menu::sdk
{
	struct Camera
	{
	};

	DECLARE_POINTER(Camera_Get_WorldToCameraMatrix, Matrix4x4(*)(Camera* camera, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Camera",
		"get_worldToCameraMatrix", 0);

	DECLARE_POINTER(Camera_Get_ProjectionMatrix, Matrix4x4(*)(Camera* camera, MethodInfo* methodInfo), "UnityEngine.CoreModule", "UnityEngine", "Camera",
		"get_projectionMatrix", 0);
}
