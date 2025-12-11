#pragma once

#include <imgui.h>
#include "feature.hpp"

namespace menu
{
	class gui_util
	{
	public:
		void checkbox(std::string_view featurelabel)
		{
			toggle_feature* feature = feature::get_togglefeature_from_label(featurelabel);
			if (feature == nullptr)
			{
				ImGui::Text(std::format("NULL FEATURE! {}", featurelabel.data()).c_str());
				return;
			}
			ImGui::PushID(feature->label().c_str());
			bool guipos = ((uint32_t)feature->flags() & (1 << (uint32_t)feature_flags::EXTRA_MENU));
			if (guipos) { feature->on_gui(); ImGui::SameLine(); }
			ImGui::Checkbox(featurelabel.data(), &feature->is_enabled());
			if (ImGui::IsItemHovered() && feature->description() != "")
				ImGui::SetTooltip(feature->description().c_str());
			if (!guipos) feature->on_gui();
			ImGui::PopID();
		}

		void checkboxslider(std::string featurelabel, std::string_view value = ".", float min = 0, float max = 200)
		{
			toggle_feature* feature = feature::get_togglefeature_from_label(featurelabel);
			ImGui::Checkbox(featurelabel.c_str(), &feature->is_enabled());
			if (ImGui::IsItemHovered() && feature->description() != "")
				ImGui::SetTooltip(feature->description().c_str());

			ImGui::SameLine();
			ImGui::PushID(feature->label().c_str());
			ImGui::SliderFloat(value != "." ? value.data() : featurelabel.c_str(), &feature->value(), min, max);
			//switch (decltype(T))todo something like this
			//{
			//	case float: ImGui::SliderFloat(value != "." ? value.data() : featurelabel.c_str(), &feature->value(), min, max); break;
			//	case int: ImGui::SliderInt(value != "." ? value.data() : featurelabel.c_str(), &feature->value(), min, max); break;
			//}
			
			if (ImGui::IsItemHovered() && feature->description() != "")
				ImGui::SetTooltip(feature->description().c_str());
		}
	};
	inline auto g_gui_util = new gui_util();
}