#include "gui.hpp"
#include "features/all.hpp"//needs to be included in a cpp file for the features to actually initialize

namespace menu
{
	void gui::init()
	{
        ImVec4* colors = ImGui::GetStyle().Colors;
        {
            colors[ImGuiCol_WindowBg] = ImVec4(0.03f, 0.03f, 0.03f, 0.50f);
            colors[ImGuiCol_ChildBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.50f);
            colors[ImGuiCol_Border] = ImVec4(0.10f, 0.50f, 0.10f, 0.00f);

            colors[ImGuiCol_FrameBg] = ImColor(20, 20, 20, 255);
            colors[ImGuiCol_FrameBgHovered] = ImColor(15, 40, 15, 255);
            colors[ImGuiCol_FrameBgActive] = ImVec4(0.0f, 0.9f, 0.2f, 1.f);

            colors[ImGuiCol_Button] = ImVec4(0.0f, 0.7f, 0.15f, 1.f);
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.0f, 0.85f, 0.25f, 1.f);
            colors[ImGuiCol_ButtonActive] = ImVec4(0.0f, 1.0f, 0.30f, 1.f);

            colors[ImGuiCol_TextSelectedBg] = ImVec4(0.0f, 0.9f, 0.25f, 1.f);
            colors[ImGuiCol_TextDisabled] = ImVec4(0.30f, 0.40f, 0.30f, 1.00f);
            colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 1.0f, 0.30f, 1.f);
        }

        ImGuiStyle* style = &ImGui::GetStyle();
        {
            style->WindowPadding = ImVec2(14, 14);
            style->WindowBorderSize = 5.f;
            style->WindowRounding = 15.f;

            style->FramePadding = ImVec2(6, 6);
            style->FrameRounding = 3.f;
            style->FrameBorderSize = 2.f;

            style->ChildBorderSize = 1.f;
            style->ChildRounding = 5.f;
        }
	}
    ImVec2 main_size = ImVec2(-1, -1);
    ImVec2 main_topleft = ImVec2(-1, -1);

	void gui::render()//bug, discord overlay appears on gui
	{
        g_notification_service->draw();
        handle_input();
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImVec2 screen = g_gui_util->get_screen_size();
        ImGui::SetNextWindowSize(screen);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5, 0));
        ImGui::Begin("OVERLAY", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs);
        
        ImGui::PushFont(NULL, 35);
        ImGui::TextColored(ImVec4(1, .5, 0, 1), "Phas");
        ImGui::SameLine();
        ImGui::Text("Menu");
        ImGui::PopFont();

        ImGui::PopStyleVar();
        //make custom image crosshair
        ImGui::GetWindowDrawList()->AddCircle(ImVec2(screen.x / 2, screen.y / 2), 10, ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1)));//crosshair test
        ImGui::GetWindowDrawList()->AddCircle(ImVec2(screen.x / 2, screen.y / 2), 5, ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1)));
        

        float wb = ImGui::GetStyle().WindowBorderSize;//fix me so it borders the window right, once fixed try removing it down to just 1 gif
        ImVec2 win_max = ImVec2(main_topleft.x + main_size.x, main_topleft.y + main_size.y);
        if ((main_topleft != ImVec2(-1, -1)) && m_menu_open && g.gui.rainbow_border)
        {
            //Top
            ImGui::GetForegroundDrawList()->AddImage(g_renderer.gifs.find("rainbow_border1")->second->get_current_frame(0, g.gui.rainbow_border_speed)->view, ImVec2(main_topleft.x - wb, main_topleft.y), ImVec2(win_max.x + wb, main_topleft.y + wb));
            //Bottom
            ImGui::GetForegroundDrawList()->AddImage(g_renderer.gifs.find("rainbow_border2")->second->get_current_frame(1, g.gui.rainbow_border_speed)->view, ImVec2(main_topleft.x - wb, win_max.y), ImVec2(win_max.x + wb, win_max.y + wb));
            // Left
            ImGui::GetForegroundDrawList()->AddImage(g_renderer.gifs.find("rainbow_border3")->second->get_current_frame(2, g.gui.rainbow_border_speed)->view, ImVec2(main_topleft.x - wb, main_topleft.y), ImVec2(main_topleft.x, win_max.y));
            // Right
            ImGui::GetForegroundDrawList()->AddImage(g_renderer.gifs.find("rainbow_border4")->second->get_current_frame(3, g.gui.rainbow_border_speed)->view, ImVec2(win_max.x, main_topleft.y), ImVec2(win_max.x + wb, win_max.y));
        }

        for (auto feature : g_toggle_features)//for esp n shit like that, or custom menus but we also have the popup menus for custom menus so
        {
            if (feature->is_enabled())
                feature->on_overlay();
        }
        ImGui::End();

        if (!m_menu_open)
            return;

		ImGui::Begin((std::string("PhasMenu") + RELEASE).c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
        main_topleft = ImGui::GetWindowPos();
        main_size = ImGui::GetWindowSize();
        ImGui::Text((std::string("PhasMenu") + RELEASE).c_str());
		ImGui::Separator();

        ImGui::BeginGroup();    
        ImGui::BeginChild("side_bar", ImVec2(50, main_size.y - ImGui::GetStyle().WindowPadding.y * 2));//side bar
        for (int i = 0; i <= SETTINGS; i++)
        {
            if (ImGui::Button(tab_to_icon((etab)i)))
                m_selected_tab = (etab)i;
        }
        ImGui::EndChild();
        ImGui::EndGroup();

        ImGui::SameLine();

        ImGui::BeginGroup();
        //ImGui::BeginChild("main_view", ImVec2(main_size.x - 50 - ImGui::GetStyle().WindowPadding.x * 2, main_size.y - ImGui::GetStyle().WindowPadding.y * 2));
        try 
        {
            //g_gui_util->checkbox("Infinite Sprint");
            switch (m_selected_tab)
            {
                case SELF: self_tab(); break;
                case GHOST: ghost_tab(); break;
                case NETWORK: network_tab(); break;
                case VISUAL: visual_tab(); break;
                case SETTINGS: settings_tab(); break;
            }
        }
        catch (std::exception e)
        {
            LOG(WARNING) << "ERROR IN GUI: " << e.what();
        }

        //ImGui::EndChild();
        ImGui::EndGroup();
        ImGui::End();

        for (toggle_feature* feature : g_toggle_features)
        {
            const char* popup = std::format("{}_popup", feature->label()).c_str();
            if (feature->popup_open())
            {
                ImGui::SetNextWindowSize(ImVec2(190, 195));
                ImGui::Begin(popup, &feature->popup_open(), ImGuiWindowFlags_NoTitleBar);
                ImGui::Text(feature->label().c_str());
                ImGui::Separator();
                ImGui::BeginChild(std::format("{}_child", feature->label()).c_str());
                feature->on_gui();
                ImGui::EndChild();
                ImGui::End();
            }
        }
	}

	void gui::handle_input()
	{
        HWND main_hwnd = FindWindowA(NULL, (std::string("PhasMenu") + RELEASE).c_str());
        HWND overlay_hwnd = FindWindowA(NULL, "OVERLAY");
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            if (!m_menu_open)
				SetForegroundWindow(main_hwnd);
            else
                SetForegroundWindow(FindWindowA(NULL, "Phasmophobia"));
            m_menu_open = !m_menu_open;
        }
        //handle overlay shit
        if (m_menu_open)
        {
            SetWindowLong(main_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);//dont show in alttab
            SetWindowPos(main_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);//keep focus
        }
        SetWindowLong(overlay_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);//not clickable, dont show in alttab
        SetWindowPos(overlay_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);//set to top
        for (auto feature : g_toggle_features)//for esp n shit like that, or custom menus but we also have the popup menus for custom menus so
        {
            HWND feature_hwnd = FindWindowA(NULL, feature->label().c_str());
            SetWindowLong(feature_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
            SetWindowPos(feature_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
        }
	}
}