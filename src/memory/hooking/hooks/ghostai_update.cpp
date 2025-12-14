#include "../hooking.hpp"

namespace menu
{
	void hooks::ghostai_update(sdk::GhostAI* gai, method_info* mi)
	{
		if (game::ghost == nullptr)
			game::ghost = gai;
		
		return g_hooking->get_original<hooks::ghostai_update>()(gai, mi);
	}
}