#pragma once

#include "features/feature_manager.hpp"
#include "util/game_util.hpp"

namespace menu
{
	class ghost_esp : toggle_feature
	{
		using toggle_feature::toggle_feature;
	public:
		ImVec2 screen_pos;
		virtual void on_tick() override
		{
			if (game::ghost != nullptr)
			{
				sdk::Vector3 pos = sdk::Transform_Get_Position_ptr(game::ghost->Fields.HuntingRaycastPoint, nullptr);
				screen_pos = g_game_util->world_to_screen(pos);
			}
			else
				LOG(INFO) << "ghost is nullptr, check if game started!";
		}

		virtual void on_overlay() override
		{
			if (screen_pos != ImVec2(-1, -1))
			{
				ImGui::GetBackgroundDrawList()->AddText(screen_pos, ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1)), std::format("GHOST TEST!\n").c_str());
			}
				
		}
	};
	static inline ghost_esp g_ghost_esp("Ghost ESP", "Spot the ghost.");
}