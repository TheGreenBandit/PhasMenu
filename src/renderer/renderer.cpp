#include "renderer.hpp"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "gui/gui.hpp"
#include "thread_pool.hpp"
#include "widgets/imgui_notify.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_GIF
#include "widgets/stb_image.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
    HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace menu
{
    void load_images()
    {
        g_renderer.load_gif_from_file(g_file_manager.get_base_dir() / "Resources" / "rainbow_border1.gif", "rainbow_border1", &g_renderer.gifs);
        g_renderer.load_gif_from_file(g_file_manager.get_base_dir() / "Resources" / "rainbow_border2.gif", "rainbow_border2", &g_renderer.gifs);
        g_renderer.load_gif_from_file(g_file_manager.get_base_dir() / "Resources" / "rainbow_border3.gif", "rainbow_border3", &g_renderer.gifs);
        g_renderer.load_gif_from_file(g_file_manager.get_base_dir() / "Resources" / "rainbow_border4.gif", "rainbow_border4", &g_renderer.gifs);
    }

    void renderer::init()
    {
        m_running = true;
        g_thread_pool->push([this]
            {
                LOG(INFO) << "PUSHING RENDERER LOOP " << std::this_thread::get_id();
                m_wnd_class = { sizeof(m_wnd_class), CS_CLASSDC, wnd_proc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"PhasMenu", nullptr };
                RegisterClassExW(&m_wnd_class);

                gui_hwnd = ::CreateWindowExW(WS_EX_TOPMOST | WS_EX_TRANSPARENT, m_wnd_class.lpszClassName, L"PhasMenu", WS_POPUPWINDOW, 0, 0, 50, 50, NULL, NULL, m_wnd_class.hInstance, NULL);
                if (!create_device(gui_hwnd))
                    destroy();
                
                ShowWindow(gui_hwnd, SW_HIDE);
                UpdateWindow(gui_hwnd);

                ImGui_ImplWin32_EnableDpiAwareness();

                IMGUI_CHECKVERSION();
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO(); (void)io;
                io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
                io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

                io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;//enable multiviewports

                ImGui::StyleColorsDark();
                ImGuiStyle& style = ImGui::GetStyle();

                std::filesystem::path w = std::getenv("SYSTEMROOT");
                std::filesystem::path windows_fonts = w.string() + "//Fonts";
                std::filesystem::path font_file_path = windows_fonts /= "./msyh.ttc";
                if (!std::filesystem::exists(font_file_path))
                    font_file_path = windows_fonts /= "./msyh.ttf";
                auto font_file = std::ifstream(font_file_path, std::ios::binary | std::ios::ate);
                const auto font_data_size = static_cast<int>(font_file.tellg());
                const auto font_data = std::make_unique<std::uint8_t[]>(font_data_size);

                font_file.seekg(0);
                font_file.read(reinterpret_cast<char*>(font_data.get()), font_data_size);
                font_file.close();
                {
                    ImFontConfig fnt_cfg{};
                    fnt_cfg.FontDataOwnedByAtlas = false;
                    strcpy(fnt_cfg.Name, "Fnt20px");
                    g_gui.segoeui_font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 20.0f, &fnt_cfg,
                        io.Fonts->GetGlyphRangesDefault());
                    fnt_cfg.MergeMode = true;
                    io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 20.f, &fnt_cfg, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
                    io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 20.f, &fnt_cfg, io.Fonts->GetGlyphRangesCyrillic());
                    ImGui::MergeIconsWithLatestFont(20.f);
                    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
                    ImFontConfig icons_config;
                    icons_config.MergeMode = true;
                    icons_config.PixelSnapH = false;
                    io.Fonts->AddFontFromFileTTF("widgets/font_awesome_5", 20.f, &icons_config, icons_ranges);
                    io.Fonts->Build();
                }
                ImGui_ImplWin32_Init(gui_hwnd);
                ImGui_ImplDX11_Init(m_d3d_device, m_d3d_device_context);
                ImGui_ImplWin32_EnableAlphaCompositing(gui_hwnd);
                g_gui.init();
                load_images();
                while (m_running)
                {
                    loop();
                }
                cleanup();
            });
    }

	void renderer::destroy()
	{
		m_running = false;
	}

	void renderer::loop()
	{
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                g_running = false;
        }

        if (m_swapchain_occluded && m_swapchain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
            return;
        m_swapchain_occluded = false;

        if (m_resize_width != 0 && m_resize_height != 0)
        {
            cleanup_render_target();
            m_swapchain->ResizeBuffers(0, m_resize_width, m_resize_height, DXGI_FORMAT_UNKNOWN, 0);
            m_resize_width = m_resize_height = 0;
            create_render_target();
        }
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.00f);
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        g_gui.render();
        ImGui::EndFrame();
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        m_d3d_device_context->OMSetRenderTargets(1, &m_main_render_target_view, nullptr);
        m_d3d_device_context->ClearRenderTargetView(m_main_render_target_view, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        auto io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)//THIS IS REQUIRED TO NOT HAVE THE ACTUAL WINDOW BG!!!!!
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT hr = m_swapchain->Present(1, 0);
        m_swapchain_occluded = (hr == DXGI_STATUS_OCCLUDED);
	}

	void renderer::cleanup()
	{
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        cleanup_device();
        ::DestroyWindow(gui_hwnd);
        ::UnregisterClassW(m_wnd_class.lpszClassName, m_wnd_class.hInstance);
	}

    void renderer::handle_window_movement()//todo clean this up
    {
        POINT cursor;
        GetCursorPos(&cursor);

        if (!ImGui::IsAnyItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
        {
            static POINT prev = cursor;
            RECT rect;
            GetWindowRect(gui_hwnd, &rect);
            MoveWindow(gui_hwnd, rect.left + (cursor.x - prev.x), rect.top + (cursor.y - prev.y), rect.right - rect.left, rect.bottom - rect.top, TRUE);

            prev = cursor;
        }
        else
            static POINT prev = cursor;
    }

    LRESULT WINAPI renderer::wnd_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;

        switch (msg)
        {
        case WM_SIZE:
            if (wParam == SIZE_MINIMIZED)
                return 0;
            g_renderer.m_resize_width = (UINT)LOWORD(lParam); // Queue resize
            g_renderer.m_resize_height = (UINT)HIWORD(lParam);
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
        case WM_MOUSEMOVE: //make window move
            if (ImGui::IsAnyItemActive())
                break;
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            MoveWindow(hWnd, x, y, 200, 200, TRUE);
            break;
        }
        return ::DefWindowProcW(hWnd, msg, wParam, lParam);
    }

    bool renderer::create_device(HWND hWnd)
    {
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT createDeviceFlags = 0;
        //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
        HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &m_swapchain, &m_d3d_device, &featureLevel, &m_d3d_device_context);
        if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
            res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &m_swapchain, &m_d3d_device, &featureLevel, &m_d3d_device_context);
        if (res != S_OK)
            return false;

        create_render_target();
        return true;
    }

    void renderer::cleanup_device()
    {
        cleanup_render_target();
        if (m_swapchain) { m_swapchain->Release(); m_swapchain = nullptr; }
        if (m_d3d_device_context) { m_d3d_device_context->Release(); m_d3d_device_context = nullptr; }
        if (m_d3d_device) { m_d3d_device->Release(); m_d3d_device = nullptr; }
    }

    void renderer::create_render_target()
    {
        ID3D11Texture2D* pBackBuffer;
        m_swapchain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        m_d3d_device->CreateRenderTargetView(pBackBuffer, nullptr, &m_main_render_target_view);
        pBackBuffer->Release();
    }

    void renderer::cleanup_render_target()
    {
        if (m_main_render_target_view) { m_main_render_target_view->Release(); m_main_render_target_view = nullptr; }
    }


    bool renderer::load_texture_from_file(std::filesystem::path path, image** image_)//todo js make it into a map
    {
        image* ret = new image();
        ret->size[0] = 0;
        ret->size[1] = 0;
        ret->view = nullptr;

        unsigned char* image_data = stbi_load(path.string().c_str(), &ret->size[0], &ret->size[1], NULL, 4);
        if (image_data == NULL)
        {
            LOG(WARNING) << "FAILED TO LOAD IMAGE, CHECK IF IMAGE WAS DOWNLOADED SUCCESSFULLY.";
            return false;
        }
        // Create texture 
        D3D11_TEXTURE2D_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.Width = ret->size[0];
        desc.Height = ret->size[1];
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;

        ID3D11Texture2D* pTexture = NULL;
        D3D11_SUBRESOURCE_DATA subResource;
        subResource.pSysMem = image_data;
        subResource.SysMemPitch = desc.Width * 4;
        subResource.SysMemSlicePitch = 0;
        m_d3d_device->CreateTexture2D(&desc, &subResource, &pTexture);

        // Create texture view 
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        ZeroMemory(&srvDesc, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = desc.MipLevels;
        srvDesc.Texture2D.MostDetailedMip = 0;
        m_d3d_device->CreateShaderResourceView(pTexture, &srvDesc, &ret->view);

        pTexture->Release();
        *image_ = ret;
        stbi_image_free(image_data);
        return true;
    }

    bool renderer::load_gif_from_file(std::filesystem::path path, std::string name, std::map<std::string, gif_image*>* gif_map)
    {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file)
            return false;

        size_t size = file.tellg();
        file.seekg(0);

        std::vector<unsigned char> buffer(size);
        file.read((char*)buffer.data(), size);

        int* delays = nullptr;
        int w, h, frames, comp;
        unsigned char* data = stbi_load_gif_from_memory(buffer.data(), (int)buffer.size(), &delays, &w, &h, &frames, &comp, 4);

        if (!data)
            return false;

        gif_image* gif = new gif_image();
        gif->width = w;
        gif->height = h;

        for (int i = 0; i < frames; i++)
        {
            unsigned char* frame_pixels = data + (w * h * 4 * i);

            D3D11_TEXTURE2D_DESC desc{};
            desc.Width = w;
            desc.Height = h;
            desc.MipLevels = 1;
            desc.ArraySize = 1;
            desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            desc.SampleDesc.Count = 1;
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

            D3D11_SUBRESOURCE_DATA sub{};
            sub.pSysMem = frame_pixels;
            sub.SysMemPitch = w * 4;

            ID3D11Texture2D* tex = nullptr;
            if (m_d3d_device == nullptr)
            {
                LOG(INFO) << "BAD D3D DEVICE";
                return false;
            }
            m_d3d_device->CreateTexture2D(&desc, &sub, &tex);

            ID3D11ShaderResourceView* srv = nullptr;
            m_d3d_device->CreateShaderResourceView(tex, nullptr, &srv);

            tex->Release();

            gif->frames.push_back(new gif_frame(srv, delays ? delays[i] : 100));
        }

        stbi_image_free(data);
        if (delays) 
            STBI_FREE(delays);

        gif_map->emplace(name, gif);
        return true;
    }
}