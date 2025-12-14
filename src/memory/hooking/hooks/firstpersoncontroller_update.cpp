#include "../hooking.hpp"
#include "util/game_util.hpp"
#include "features/feature_manager.hpp"

namespace menu
{
	void hooks::firstpersoncontroller_update(sdk::FirstPersonController* fpc, method_info* mi)
	{
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