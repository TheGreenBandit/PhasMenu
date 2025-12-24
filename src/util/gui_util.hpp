#pragma once

#include <imgui.h>
#include "feature.hpp"
#include "renderer/renderer.hpp"

namespace menu
{
	class gui_util
	{
	public:
		void checkbox(std::string_view featurelabel)
		{
			app::
			toggle_feature* feature = feature::get_togglefeature_from_label(featurelabel);
			if (feature == g_default_toggle)
			{
				ImGui::Text("NULL FEATURE! %s", featurelabel.data());
				return;
			}

			ImGui::PushID(feature->label().c_str());
			ImGui::Checkbox(featurelabel.data(), &feature->is_enabled());
			bool has_extra_options = (feature->flags() & EXTRA_MENU);
			if (ImGui::IsItemHovered() && !feature->description().empty())
				ImGui::SetTooltip(std::format("{}{}", has_extra_options ? "Right click for more options!\n" : "", feature->description().c_str()).c_str());
			if (has_extra_options)
			{
				if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
					feature->popup_open() = !feature->popup_open();
			}
			ImGui::PopID();
		}

		void checkboxslider(std::string featurelabel, std::string_view value = ".", float min = 0, float max = 200)
		{
			toggle_feature* feature = feature::get_togglefeature_from_label(featurelabel);
			if (feature == g_default_toggle)
			{
				ImGui::Text(std::format("NULL FEATURE! {}", featurelabel.data()).c_str());
				return;
			}
			ImGui::PushID(("##" + feature->label()).c_str());
			ImGui::Checkbox(featurelabel.c_str(), &feature->is_enabled());
			if (ImGui::IsItemHovered() && feature->description() != "")
				ImGui::SetTooltip(feature->description().c_str());
			ImGui::PopID();
			ImGui::SameLine();
			ImGui::PushID(feature->label().c_str());
			ImGui::SliderFloat(value != "." ? value.data() : featurelabel.c_str(), &feature->value(), min, max);
			ImGui::PopID();
			
			if (ImGui::IsItemHovered() && feature->description() != "")
				ImGui::SetTooltip(feature->description().c_str());
		}

		ImVec2 get_screen_size()
		{
			const HMONITOR monitor = MonitorFromWindow(g_renderer.gui_hwnd, MONITOR_DEFAULTTONEAREST);
			MONITORINFO info = {};
			info.cbSize = sizeof(MONITORINFO);
			GetMonitorInfo(monitor, &info);
			return ImVec2(info.rcMonitor.right - info.rcMonitor.left, info.rcMonitor.bottom - info.rcMonitor.top);
		}
	};
	inline auto g_gui_util = new gui_util();
}