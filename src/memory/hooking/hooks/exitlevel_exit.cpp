#include "../hooking.hpp"
#include "util/game_util.hpp"

namespace menu
{
	void hooks::exitlevel_exit(sdk::ExitLevel* el, void* photonMessageInfo, method_info* mi)
	{
		//reset
		LOG(INFO) << "GAME OVER, SETTING STATES TO NULLPTR";

		return g_hooking->get_original<hooks::exitlevel_exit>()(el, photonMessageInfo, mi);
	}
}