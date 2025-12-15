#pragma once

#include "common.hpp"

namespace menu
{
	class renderer
	{
		bool m_running = false;
		WNDCLASSEXW m_wnd_class;
		ID3D11Device* m_d3d_device = nullptr;
		ID3D11DeviceContext* m_d3d_device_context = nullptr;
		IDXGISwapChain* m_swapchain = nullptr;
		bool m_swapchain_occluded = false;
		UINT m_resize_width = 0, m_resize_height = 0;
		ID3D11RenderTargetView* m_main_render_target_view = nullptr;
	private:
		bool create_device(HWND hWnd);
		void cleanup_device();
		void create_render_target();
		void cleanup_render_target();
		void handle_window_movement();
		static LRESULT WINAPI wnd_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		HWND gui_hwnd;

		void loop();
		void init();
		void cleanup();
		void destroy();
	};
	inline auto g_renderer = renderer();
}