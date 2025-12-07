#include "memory/hooking/hooking.hpp"

namespace menu
{
	HRESULT hooks::swapchain_present(IDXGISwapChain* swapchain, UINT sync_interval, UINT flags)
	{
		//if (g_running)
		//	g_renderer->on_present();
		HRESULT r = 0;
		return r;
		//return hooks::original_swapchain_present(swapchain, sync_interval, flags);
	}
}