#pragma once

#include "widgets/imgui_notify.h"

namespace menu::notify//definitely need to edit this, 
{
	inline void dx(const char* title, const char* content = "", const char* icon = "", ImGuiToastType_ type = ImGuiToastType_Info, int remove = 3000)
	{
		ImGuiToast toast(type, remove); // <-- content can also be passed here as above
		toast.set_title(title);
		toast.set_content(content);
		toast.set_custom_icon(icon);
		ImGui::InsertNotification(toast);
	}

	inline void dx(const char* title, const char* content = "", ImGuiToastType_ type = ImGuiToastType_Info, int remove = 3000)
	{
		ImGuiToast toast(type, remove); // <-- content can also be passed here as above
		toast.set_title(title);
		toast.set_content(content);
		switch (type)
		{
		case ImGuiToastType_Success:
			toast.set_custom_icon(ICON_FA_CHECK_CIRCLE); break;
		case ImGuiToastType_Error:
			toast.set_custom_icon(ICON_FA_STOP_CIRCLE); break;
		case ImGuiToastType_Warning:
			toast.set_custom_icon(ICON_FA_EXCLAMATION_CIRCLE); break;
		default:
			toast.set_custom_icon(ICON_FA_CIRCLE); break;
		}
		ImGui::InsertNotification(toast);
	}
}