#include "../hooking.hpp"
#include "util/game_util.hpp"

namespace menu
{
	void hooks::PlayerStamina_Update(sdk::PlayerStamina* ps, method_info* mi)//not needed anymore found better way
	{
		return g_hooking->get_original<hooks::PlayerStamina_Update>()(ps, mi);
	}
}