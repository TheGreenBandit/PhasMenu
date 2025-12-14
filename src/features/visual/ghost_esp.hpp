#pragma once

#include "features/feature_manager.hpp"
#include "util/game_util.hpp"

namespace menu
{
	class ghost_esp : toggle_feature
	{
	public:

		using toggle_feature::toggle_feature;

		ImVec2 screen_pos;
		std::string name = "NAME";
		std::string type = "TYPE";
		float distance = 1.f;
		bool box_esp = false;

		virtual void on_tick() override
		{		
			if (game::ghost != nullptr)
			{
				sdk::Vector3 pos = sdk::Transform_Get_Position_ptr(game::ghost->Fields.HuntingRaycastPoint, nullptr);
				screen_pos = g_game_util->world_to_screen(pos);

				//text
				sdk::GhostTraits gt = game::ghost->Fields.GhostInfo->Fields.GhostTraits;
				name = S(gt.GhostName);
				type = g_game_util->get_ghost_name(gt.InitialGhostType);//initial because if mimic it will show what mimic is mimicing

				auto ct = sdk::Component_Get_Transform_ptr(reinterpret_cast<sdk::Component*>(game::network->Fields.LocalPlayer->Fields.Camera), nullptr);
				auto cp = sdk::Transform_Get_Position_ptr(ct, nullptr);
				distance = g_game_util->get_distance_between_coords(pos, cp);
			}
		}

		virtual void on_overlay() override
		{
			if (screen_pos != ImVec2(-1, -1))//todo add box esp, maybe skeleton
			{
				//ImGui::PushFont(nullptr, .1 * distance);//todo make this scale
				ImGui::GetBackgroundDrawList()->AddText(screen_pos, ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1)), std::format("{}\n{}\n{}s", name, type, distance).c_str());
				//ImGui::PopFont();

				if (box_esp)
				{
					float mult = 6.17757f / distance;
					ImGui::GetBackgroundDrawList()->AddRect(ImVec2(screen_pos.x - (62.5f * mult), screen_pos.y - (175.f * mult)), ImVec2(screen_pos.x - (62.5f * mult) + (125.f * mult), screen_pos.y - (175.f * mult) + (350.f * mult)), ImGui::GetColorU32(ImVec4(1, 1, 1, 1)));
				}
			}		
		}
	};
	static inline ghost_esp* g_ghost_esp = new ghost_esp("Ghost ESP", "Spot the ghost.");
}