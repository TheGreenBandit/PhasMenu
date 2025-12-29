#include "../gui.hpp"
#include "util/game_util.hpp"

namespace menu
{
	void gui::network_tab()
	{
		ImGui::Text("test");
		static bool is_player_selected = false;
		sdk::NetworkPlayerSpot* selected_player = nullptr;
		const char* name = "NULL";
		ImGui::BeginChild("Listbox stuff", ImVec2(200, 50 * g_game_util->playerlist.size() + 100));
		for (int i = 0; i < g_game_util->playerlist.size(); i++)
		{
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			
			if (ImGui::Button(S(g_game_util->playerlist.at(i)->Fields.AccountName).c_str()))
			{
				name = S(g_game_util->playerlist.at(i)->Fields.AccountName).c_str();
				selected_player = g_game_util->playerlist.at(i);
				g_game_util->selected_player = g_game_util->playerlist.at(i)->Fields.Player;
				is_player_selected = true;
			}

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}
		ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginGroup();
		ImGui::BeginChild("np");
		if (!is_player_selected)//network options
		{
			ImGui::BeginChild("TITLE STUFF", ImVec2(ImGui::GetContentRegionAvail().x, 50), ImGuiChildFlags_Borders);
			ImGui::Text("Network Options"); //center me
			ImGui::EndChild();
		}
		else
		{
			//titling here
			ImGui::BeginChild("TITLE STUFF", ImVec2(ImGui::GetContentRegionAvail().x, 50), ImGuiChildFlags_Borders);
			if (ImGui::Button((std::string(ICON_FA_ARROW_LEFT) + " Back").c_str()))
				is_player_selected = false;
			ImGui::Text(name);//center me using max size
			ImGui::EndChild();
			ImGui::BeginChild("Playeroptions");

			ImGui::SeparatorText("Account Info");
			//ImGui::Text(std::format("Prestige: {}", selected_player->Fields.Prestige).c_str());
			//ImGui::Text(std::format("Level: {}", selected_player->Fields.Level).c_str());
			//ImGui::Text(std::format("Experience: {}", selected_player->Fields.Experience).c_str());
			//ImGui::SeparatorText("Player Info");
			//ImGui::Text(selected_player->Fields.Player->Fields.IsDead ? "Dead" : "Alive");
			//ImGui::Text(std::format("Current Speed: {}", selected_player->Fields.Player->Fields.MovementSpeed).c_str());
			//ImGui::Text(std::format("Sanity: {}", 100 - selected_player->Fields.Player->Fields.PlayerSanity->Fields.Insanity).c_str());
			//ImGui::Text(std::format("Current Room: {}", selected_player->Fields.Player->Fields.CurrentRoom != nullptr ? S(selected_player->Fields.Player->Fields.CurrentRoom->Fields.RoomName) : "Not in a room.").c_str());
			//auto curpos = selected_player->Fields.Player->Fields.MapIcon->position;
			//ImGui::Text(std::format("Position: X:{} Y:{} Z:{}", curpos->X, curpos->Y, curpos->Z).c_str());
			g_gui_util->button("Instakill");
			ImGui::EndChild();
		}
		ImGui::EndChild();
		ImGui::EndGroup();
		//list box to select players
	}
}