#include "../gui.hpp"
#include "util/game_util.hpp"

namespace menu
{
	void gui::ghost_tab()
	{
		g_gui_util->checkbox("Ghost Info Window");
		if (ImGui::Button("Random Door"))
			sdk::GhostActivity_InteractWithARandomDoor_ptr(g_game_util->get_network()->Fields.LocalPlayer->Fields.PlayerStats->Fields.LevelController->Fields.CurrentGhost->Fields.GhostActivity, nullptr);
		
		if (ImGui::Button("Random Prop"))
			sdk::GhostActivity_InteractWithARandomProp_ptr(g_game_util->get_network()->Fields.LocalPlayer->Fields.PlayerStats->Fields.LevelController->Fields.CurrentGhost->Fields.GhostActivity, false, nullptr);
		
		if (ImGui::Button("Random Light"))
			sdk::GhostActivity_InteractWithARandomLightSwitch_ptr(g_game_util->get_network()->Fields.LocalPlayer->Fields.PlayerStats->Fields.LevelController->Fields.CurrentGhost->Fields.GhostActivity, false, nullptr);
	}
}