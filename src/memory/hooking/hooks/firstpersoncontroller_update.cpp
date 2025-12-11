#include "../hooking.hpp"
#include "util/game_util.hpp"

namespace menu
{
	void hooks::FirstPersonController_Update(sdk::FirstPersonController* fpc, method_info* mi)//not needed anymore found better way
	{

		return g_hooking->get_original<hooks::FirstPersonController_Update>()(fpc, mi);
	}
}