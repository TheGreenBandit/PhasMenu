#pragma once

#include "features/feature_manager.hpp"
#include "util/game_util.hpp"

namespace menu
{
	struct fuse_box_esp : toggle_feature
	{
		using toggle_feature::toggle_feature;

		ImVec2 screen_pos;

		float distance = 1.f;//todo make on_gui be so that when you right click an option is opens a popup window with the feature's extrea options usch as color, different ways, etc
		bool line_esp = false;
		float color_esp[4] = { 255, 255, 255, 255 };
		bool is_broken = false;
		bool is_on = false;

		virtual void on_tick() override
		{
			auto fuse_box = game::network->Fields.LocalPlayer->Fields.PlayerStats->Fields.LevelController->Fields.FuseBox;
			if (fuse_box != nullptr)
			{
				sdk::Vector3 pos = sdk::Transform_Get_Position_ptr(fuse_box->Fields.HandleObject, nullptr);
				is_broken = fuse_box->Fields.IsBroken;
				is_on = fuse_box->Fields.IsOn;

				screen_pos = g_game_util->world_to_screen(pos);

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
				ImGui::GetBackgroundDrawList()->AddText(name_pos, ImGui::GetColorU32(ImVec4(color_esp[0], color_esp[1], color_esp[2], color_esp[3])), std::format("Fusebox\n{}", is_broken ? "Broken" : (is_on ? "On" : "Off")).c_str());
				ImVec2 screen = g_gui_util->get_screen_size();
				if (line_esp)
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(screen.x / 2, screen.y), screen_pos, ImGui::GetColorU32(ImVec4(color_esp[0], color_esp[1], color_esp[2], color_esp[3])));
			}
		}
	};
	static inline fuse_box_esp* g_fuse_box_esp = new fuse_box_esp("Fusebox ESP", "Lights, Camera, Action.");
}