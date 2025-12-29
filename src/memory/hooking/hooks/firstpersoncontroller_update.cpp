#include "../hooking.hpp"
#include "util/game_util.hpp"
#include "features/feature_manager.hpp"


namespace menu
{
	std::vector<sdk::Player*> test;
	int old_length = 0;

	void hooks::firstpersoncontroller_update(sdk::FirstPersonController* fpc, MethodInfo* mi)
	{
		if (g_game_util->get_network() == nullptr)
			return g_hooking->get_original<hooks::firstpersoncontroller_update>()(fpc, mi);
		//gonna keep using this for now
		for (int i = 0; i < game::network->Fields.PlayersData->Fields.Size; i++)//use mono to get players instead so no need to be in game relying on this shit
		{
			auto player = game::network->Fields.PlayersData->Fields.Items->Vector[i];//add check for if player in list already or if left game
			if (!(std::find(g_game_util->playerlist.begin(), g_game_util->playerlist.end(), player) != g_game_util->playerlist.end()))
				g_game_util->playerlist.push_back(player);
		}
		//remove old players that have left
		for (auto it = g_game_util->playerlist.begin(); it != g_game_util->playerlist.end();)
		{
			bool ingame = false;
			for (int i = 0; i < game::network->Fields.PlayersData->Fields.Size; i++)
			{
				if (game::network->Fields.PlayersData->Fields.Items->Vector[i] == *it)
				{
					ingame = true;
					break;
				}
			}

			if (!ingame) it = g_game_util->playerlist.erase(it); // remove player
			else it++;
		}

		for (auto feature : g_toggle_features)
		{
			if (feature->last_state() != feature->is_enabled())
			{
				feature->last_state() ? feature->on_disable() : feature->on_enable();
				feature->last_state() = feature->is_enabled();
			}

			if (feature->is_enabled())
				feature->on_tick();
		}
		for (auto feature : g_execute_features)
		{
			if (feature->ready_for_action())
			{
				feature->action();
				feature->ready_for_action() = false;
			}
		}
		return g_hooking->get_original<hooks::firstpersoncontroller_update>()(fpc, mi);
	}
}