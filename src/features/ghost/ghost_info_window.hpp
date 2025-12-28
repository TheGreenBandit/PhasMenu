#pragma once

#include "features/feature_manager.hpp"
#include "util/game_util.hpp"

namespace menu
{
	struct ghost_info_window : toggle_feature
	{
		using toggle_feature::toggle_feature;

		std::string ghost_name;
		std::string ghost_type;
		bool is_mimic = false;
		std::string mimic_type;
		std::string current_room;
		std::string favorite_room;
		std::string state;
		bool hunting = false;


		virtual void on_tick() override
		{
			if (!g_game_util->is_game_started())
				return;

			auto ghost = game::network->Fields.LocalPlayer->Fields.PlayerStats->Fields.LevelController->Fields.CurrentGhost;

			if (ghost != nullptr)
			{
				ghost_name = S(ghost->Fields.GhostInfo->Fields.GhostTraits.GhostName);
				auto igt = ghost->Fields.GhostInfo->Fields.GhostTraits.InitialGhostType;
				ghost_type = g_game_util->get_ghost_name(igt);
				if (igt == sdk::GhostType::Mimic)
				{
					is_mimic = true;
					mimic_type = g_game_util->get_ghost_name(ghost->Fields.GhostInfo->Fields.GhostTraits.GhostType);
				}
					
				favorite_room = S(ghost->Fields.GhostInfo->Fields.FavouriteRoom->Fields.RoomName);
				if (auto cur_room = game::network->Fields.LocalPlayer->Fields.PlayerStats->Fields.LevelController->Fields.CurrentGhostRoom; cur_room != nullptr)
					current_room = S(cur_room->Fields.RoomName);
				else
					current_room = "Wandering...";
				hunting = ghost->Fields.IsHunting;
				state = g_game_util->get_ghost_state(ghost->Fields.CurrentState);
			}
		}

		virtual void on_overlay() override
		{
			ImGui::Begin("Ghost Info Window");
			ImGui::Text(ghost_name.c_str());
			ImGui::Text("Type: %s", ghost_type);//fix these
			if (is_mimic)
				ImGui::Text("Mimicking: %s", mimic_type);
			ImGui::Text("Favorite Room: %s", favorite_room);
			ImGui::Text("Current Room: %s", current_room);
			ImGui::Text("State: %s", state);
			ImGui::Text(hunting ? "HUNTING!!!" : "Not Hunting Yet...");
			ImGui::End();

		}
	};
	static inline ghost_info_window* g_ghost_info_window = new ghost_info_window("Ghost Info Window", "Ghost info stuff to look at.");
}