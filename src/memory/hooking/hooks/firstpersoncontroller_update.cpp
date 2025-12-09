#include "../hooking.hpp"

namespace menu
{
	void hooks::FirstPersonController_Update(sdk::FirstPersonController* fpc, method_info* mi)//crashing?
	{
		LOG(INFO) << sdk::FirstPersonController_Update_ptr;
		if (fpc == nullptr)
		{
			LOG(INFO) << "FPC IS NULLPTR SKIPPING FOR NOW";
			return g_hooking->get_original<hooks::FirstPersonController_Update>()(fpc, mi);
		}
		fpc->Fields.CurrentSpeed = 6;
		if (g.self.fast_sprint)
			fpc->Fields.CurrentSpeed = !fpc->Fields.IsSprinting ? g.self.fast_sprint_value / 2  : g.self.fast_sprint_value;
		return g_hooking->get_original<hooks::FirstPersonController_Update>()(fpc, mi);
	}
}