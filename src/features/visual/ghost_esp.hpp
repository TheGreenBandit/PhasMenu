#pragma once

#include "features/feature_manager.hpp"
#include "util/game_util.hpp"

namespace menu
{
	struct ghost_esp : toggle_feature
	{
		using toggle_feature::toggle_feature;

		ImVec2 screen_pos = ImVec2(-1, -1);
		std::string name = "NAME";
		std::string type = "TYPE";
		
		float distance = 1.f;//todo make on_gui be so that when you right click an option is opens a popup window with the feature's extrea options usch as color, different ways, etc
		bool box_esp = false;
		bool line_esp = false;
		float color_esp[4] = { 255, 255, 255, 255 };

		virtual void on_tick() override
		{
			if (!g_game_util->is_game_started())
			{
				screen_pos = ImVec2(-1, -1);
				return;
			}

			if (auto ghost = game::network->Fields.LocalPlayer->Fields.PlayerStats->Fields.LevelController->Fields.CurrentGhost; ghost != nullptr)
			{
				sdk::Vector3 pos = sdk::Transform_Get_Position_ptr(ghost->Fields.HuntingRaycastPoint, nullptr);
				screen_pos = g_game_util->world_to_screen(pos);

				//text
				sdk::GhostTraits gt = ghost->Fields.GhostInfo->Fields.GhostTraits;
				name = S(gt.GhostName);
				type = g_game_util->get_ghost_name(gt.InitialGhostType);//initial because if mimic it will show what mimic is mimicing

				auto ct = sdk::Component_Get_Transform_ptr(reinterpret_cast<sdk::Component*>(game::network->Fields.LocalPlayer->Fields.Camera), nullptr);
				auto cp = sdk::Transform_Get_Position_ptr(ct, nullptr);
				distance = g_game_util->get_distance_between_coords(pos, cp);
			}
		}

		virtual void on_overlay() override
		{
			if (screen_pos != ImVec2(-1, -1))
			{
				float mult = 6.17757f / distance;

				ImVec2 name_pos = ImVec2(screen_pos.x - (62.5f * mult), screen_pos.y - (175.f * mult) + 20.f);
				ImGui::GetBackgroundDrawList()->AddText(name_pos, ImGui::GetColorU32(ImVec4(color_esp[0], color_esp[1], color_esp[2], color_esp[3])), std::format("{}\n{}", name, type).c_str());

				ImVec2 screen = g_gui_util->get_screen_size();
				if (line_esp)
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(screen.x / 2, screen.y), screen_pos, ImGui::GetColorU32(ImVec4(color_esp[0], color_esp[1], color_esp[2], color_esp[3])));
				if (box_esp)
					ImGui::GetBackgroundDrawList()->AddRect(ImVec2(screen_pos.x - (62.5f * mult), screen_pos.y - (175.f * mult)), ImVec2(screen_pos.x - (62.5f * mult) + (125.f * mult), screen_pos.y - (175.f * mult) + (350.f * mult)), ImGui::GetColorU32(ImVec4(color_esp[0], color_esp[1], color_esp[2], color_esp[3])));
			}		
		}

		virtual void on_gui() override
		{
			ImGui::PushItemWidth(100);
			ImGui::ColorPicker4("Color", color_esp, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs);

			ImGui::Checkbox("Box ESP", &box_esp);
			ImGui::Checkbox("Line ESP", &line_esp);
		}
	};
	static inline ghost_esp* g_ghost_esp = new ghost_esp("Ghost ESP", "Spot the ghost.", EXTRA_MENU);
}