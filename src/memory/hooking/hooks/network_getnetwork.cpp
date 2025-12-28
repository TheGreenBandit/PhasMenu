#include "../hooking.hpp"
#include "util/game_util.hpp"

namespace menu
{
	sdk::Network* hooks::network_getnetwork(MethodInfo* mi)
	{
		//g_game_util->get_network();//probably will do my pointers for stuff in here
		// cannot call get network in here, hooks is probably bad
		//LOG(INFO) << "SETTING NETWORK PTR";
		//game::network = g_hooking->get_original<hooks::network_getnetwork>()(mi);
		//LOG(INFO) << "NETWORK PTR SHOULD BE SET: " << game::network;
		return g_hooking->get_original<hooks::network_getnetwork>()(mi);
	}
}