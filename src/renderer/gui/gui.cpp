#include "gui.hpp"
#include "renderer/renderer.hpp"
#include "util/gui_util.hpp"
#include "util/notify.hpp"
#include "features/all.hpp"

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
        
        
        //this works
        //ImGui::GetForegroundDrawList()->AddImage(g_renderer.gifs.find("rainbow_border2")->second->get_current_frame()->view, ImVec2(main_topleft.x, main_topleft.y + 8), ImVec2(main_topleft.x + 480, main_topleft.y));
        
        //border testing
        //Top
        static float speed = .2f;
        float wb = ImGui::GetStyle().WindowBorderSize;//fix me so it borders the window right, once fixed try removing it down to just 1 gif
        ImVec2 win_max = ImVec2(main_topleft.x + main_size.x, main_topleft.y + main_size.y);
        if ((main_topleft != ImVec2(-1, -1)) && menu_open)
        {
            //ImGui::GetForegroundDrawList()->AddImage(g_renderer.gifs.find("rainbow_border1")->second->get_current_frame(0, speed)->view, ImVec2(main_topleft.x - wb, main_topleft.y), ImVec2(win_max.x + wb, main_topleft.y + wb));
            //Bottom
            //ImGui::GetForegroundDrawList()->AddImage(g_renderer.gifs.find("rainbow_border2")->second->get_current_frame(1, speed)->view, ImVec2(main_topleft.x - wb, win_max.y), ImVec2(win_max.x + wb, win_max.y + wb));
            // Left
            //ImGui::GetForegroundDrawList()->AddImage(g_renderer.gifs.find("rainbow_border3")->second->get_current_frame(2, speed)->view, ImVec2(main_topleft.x - wb, main_topleft.y), ImVec2(main_topleft.x, win_max.y));
            // Right
            //ImGui::GetForegroundDrawList()->AddImage(g_renderer.gifs.find("rainbow_border4")->second->get_current_frame(3, speed)->view, ImVec2(win_max.x, main_topleft.y), ImVec2(win_max.x + wb, win_max.y));
        }

        for (auto feature : g_toggle_features)
        {
            if (feature->is_enabled())
                feature->on_overlay();
        }
        ImGui::End();

        if (!menu_open)
            return;

		ImGui::Begin("PhasMenu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
        main_topleft = ImGui::GetWindowPos();
        main_size = ImGui::GetWindowSize();
        //ImGui::SetWindowFocus();
        ImGui::Text("PhasMenu Dev Staging");
		ImGui::Separator();
        ImGui::BeginGroup();
        
        ImGui::BeginChild("side_bar", ImVec2(50, main_size.y - ImGui::GetStyle().WindowPadding.y * 2));//side bar
        ImGui::Button("H", ImVec2(50, 50));//home
        ImGui::Button("S", ImVec2(50, 50));//self
        ImGui::Button("V", ImVec2(50, 50));//visual
        ImGui::Button(ICON_FA_COGS, ImVec2(50, 50));//settings
        ImGui::EndChild();
        ImGui::EndGroup();
        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::BeginChild("main_view", ImVec2(main_size.x - 50 - ImGui::GetStyle().WindowPadding.x * 2, main_size.y - ImGui::GetStyle().WindowPadding.y * 2));
        if (ImGui::Button("DUMP TO FILE"))
            g_il2cpp.dump_to_file(g_file_manager.get_base_dir() / "sdk_dump.hpp");
        if (ImGui::Button("Test Log"))
            LOG(INFO) << "TEST";
        if (ImGui::Button("Test Notification"))
        {
            g_notification_service->push("TEST NOTIFICATION!", "TEST MESSAGE");
            notify::dx("DEBUG", "Test notification.", ImGuiToastType_Info);
        }


        ImGui::Text("ALPHA");
        ImGui::SameLine();
        ImGui::SliderFloat("## 1", &(ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w), .1, 1);
        ImGui::Text("WINDOW BORDER");
        ImGui::SameLine();
        ImGui::SliderFloat("## 2", &ImGui::GetStyle().WindowBorderSize, 1, 50);
        ImGui::Text("SPEED");
        ImGui::SameLine();
        ImGui::SliderFloat("## 3", &speed, .01, 1);
        
        try
        {
            g_gui_util->checkbox("Fusebox ESP");
            g_gui_util->checkbox("Ghost ESP");

            g_gui_util->checkbox("Infinite Sprint");
            g_gui_util->checkboxslider("Movement Speed", "", 0, 10);
        }
        catch (std::exception e)
        {
            LOG(WARNING) << "GUI ERROR: " << e.what();
        }
        ImGui::EndChild();
        ImGui::EndGroup();
        //ImGui::GetForegroundDrawList()->AddImage(g_renderer.gifs.find("rainbow_border")->second->get_current_frame()->view, ImVec2(tl.x, tl.y - 50), ImVec2(tl.x + size.x, tl.y + size.y + 50));
        // Top
        
        // Bottom
        //ImGui::GetForegroundDrawList()->AddImage(g_renderer.gifs.find("rainbow_border2")->second->get_current_frame()->view, ImVec2(tl.x - wb, win_max.y), ImVec2(win_max.x + wb, win_max.y + wb));
        // Left
        //ImGui::GetForegroundDrawList()->AddImage(g_renderer.gifs.find("rainbow_border3")->second->get_current_frame()->view, ImVec2(tl.x - wb, tl.y), ImVec2(tl.x, win_max.y));
        // Right
        //ImGui::GetForegroundDrawList()->AddImage(g_renderer.gifs.find("rainbow_border4")->second->get_current_frame()->view, ImVec2(win_max.x, tl.y), ImVec2(win_max.x + wb, win_max.y));
        //ImGui::GetForegroundDrawList()->AddImage(g_renderer.gifs.find("rainbow_border1")->second->get_current_frame()->view, ImVec2(tl.x, tl.y), ImVec2(tl.x + size.x, tl.y + size.y));
        ImGui::End();

        for (toggle_feature* feature : g_toggle_features)
        {
            const char* popup = std::format("{}_popup", feature->label()).c_str();
            if (feature->popup_open())
            {
                ImGui::SetNextWindowSize(ImVec2(190, 195));
                ImGui::Begin(popup, &feature->popup_open(), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
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
        HWND main_hwnd = FindWindowA(NULL, "PhasMenu");
        HWND overlay_hwnd = FindWindowA(NULL, "OVERLAY");
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            if (!menu_open)
				SetForegroundWindow(main_hwnd);
            else
                SetForegroundWindow(FindWindowA(NULL, "Phasmophobia"));
            menu_open = !menu_open;
        }
        //handle overlay shit
        if (menu_open)
        {
            SetWindowLong(main_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);//dont show in alttab
            SetWindowPos(main_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);//keep focus
        }
        SetWindowLong(overlay_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);//not clickable, dont show in alttab
        SetWindowPos(overlay_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);//set to top
	}
}