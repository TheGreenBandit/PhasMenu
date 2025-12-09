#pragma once
#include "sdk.hpp"
#include "quaternion.hpp"

namespace menu::sdk
{
	struct MouseLookFields
	{
		float XSensitivity;
		float YSensitivity;
		bool ClampVerticalRotation;
		float MinimumX;
		float MaximumX;
		bool Smooth;
		float SmoothTime;
		bool LockCursor;
		Quaternion m_CharacterTargetRotation;
		Quaternion m_CameraTargetRotation;
		bool m_CursorIsLocked;
		float HorizontalLook;
		float VerticalLook;
	};

	struct MouseLook
	{
		void* Clazz;
		void* Monitor;
		MouseLookFields Fields;
	};
}
