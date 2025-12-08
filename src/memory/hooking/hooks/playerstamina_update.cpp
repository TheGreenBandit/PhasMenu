#include "../hooking.hpp"

namespace menu
{
	void hooks::PlayerStamina_Update(sdk::PlayerStamina* ps, method_info* mi)
	{
		ps->Fields.CurrentStamina = 10;
		ps->Fields.StaminaDrained = false;

		return g_hooking->get_original<hooks::PlayerStamina_Update>()(ps, mi);
	}
}