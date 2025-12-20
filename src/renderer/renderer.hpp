#pragma once

#include "common.hpp"

namespace menu
{
	struct image
	{
		int size[2] = { 0, 0 };
		ID3D11ShaderResourceView* view = nullptr;
	};

	struct gif_frame
	{
		ID3D11ShaderResourceView* view = nullptr;
		int delay_ms = 0;
	};

	struct gif_image
	{
		int width = 0;
		int height = 0;
		std::vector<gif_frame*> frames;
		int current_frame = 0;
		float time_accumulator = 0.0f;
		bool has_staggered = false;

		gif_frame* get_current_frame(int stagger = 0, float speed = .2)
		{
			if (!this || frames.empty())
			{
				LOG(INFO) << "FRAMES EMPTY!";
				return new gif_frame();
			}
			if (!has_staggered)
			{
				current_frame = stagger;
				has_staggered = true;
			}
			auto ret =  frames[current_frame];
			time_accumulator += speed;//.01 every second it updates//this function is called 100 times a second
			if (time_accumulator >= 1.0f)
			{
				current_frame++;
				time_accumulator = 0.f;
			}
			if (current_frame >= frames.size() - 1)
				current_frame = 0;
			
			return ret;
		}
	};

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
		std::map<std::string, gif_image*> gifs;

		bool load_texture_from_file(std::filesystem::path path, image** image);
		bool load_gif_from_file(std::filesystem::path path, std::string name, std::map<std::string, gif_image*>* gif_map);

		void loop();
		void init();
		void cleanup();
		void destroy();
	};
	inline auto g_renderer = renderer();
}