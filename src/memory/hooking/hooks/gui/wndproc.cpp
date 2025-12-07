#include "memory/hooking/hooking.hpp"
#include "renderer/renderer.hpp"

namespace menu
{
	LRESULT hooks::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		//if (g_running)
		//	g_renderer->wndproc(hwnd, msg, wparam, lparam);
		return 0;
		//return CallWindowProcW(g_hooking->m_og_wndproc, hwnd, msg, wparam, lparam);
	}
}
