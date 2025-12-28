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
		/*sdk::Type* t = (sdk::Type*)get_type_from_class(game::network->Fields.LocalPlayer->Clazz);
		auto v = sdk::GameObject_FindObjectsOfType_ptr(t, nullptr);
		if (v->max_length != old_length)
		{
			test.clear();
			old_length = v->max_length;
		}
		for (int i = 0; i <= v->max_length; i++)
		{
			sdk::Player* p = reinterpret_cast<sdk::Player*>(v->vector[i]);
			if (!(std::find(g_game_util->playerlist.begin(), g_game_util->playerlist.end(), p) != g_game_util->playerlist.end()))
				test.push_back(p);
		}*/

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
		return g_hooking->get_original<hooks::firstpersoncontroller_update>()(fpc, mi);
	}
}