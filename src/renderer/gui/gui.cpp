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
            colors[ImGuiCol_Border] = ImVec4(0.10f, 0.50f, 0.10f, 1.00f);

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
            style->WindowBorderSize = 10.f;
            style->WindowRounding = 15.f;

            style->FramePadding = ImVec2(6, 6);
            style->FrameRounding = 3.f;
            style->FrameBorderSize = 2.f;

            style->ChildBorderSize = 1.f;
            style->ChildRounding = 5.f;
        }
	}

	void gui::render()//bug, discord overlay appears on gui
	{
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
        ImGui::GetWindowDrawList()->AddCircle(ImVec2(screen.x / 2, screen.y / 2), 10, ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1)));//crosshair test
        ImGui::GetWindowDrawList()->AddCircle(ImVec2(screen.x / 2, screen.y / 2), 5, ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1)));
        for (auto feature : g_toggle_features)
        {
            if (feature->is_enabled())
                feature->on_overlay();
        }
        ImGui::End();

        if (!menu_open)
            return;

		ImGui::Begin("PhasMenu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
        
        ImGui::SetWindowFocus();
        ImGui::Text("PhasMenu Dev Staging");
		ImGui::Separator();
        ImGui::BeginChild("side_bar", ImVec2(50, 350));//side bar
        ImGui::Button("H", ImVec2(50, 50));//home
        ImGui::Button("S", ImVec2(50, 50));//self
        ImGui::Button("V", ImVec2(50, 50));//visual
        ImGui::Button(ICON_FA_COGS, ImVec2(50, 50));//settings
        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::BeginChild("main_view", ImVec2(755, 350));
        if (ImGui::Button("DUMP TO FILE"))
            g_il2cpp.dump_to_file(g_file_manager.get_base_dir() / "sdk_dump.hpp");
        if (ImGui::Button("Test Log"))
            LOG(INFO) << "TEST";
        if (ImGui::Button("Test Notification"))
            notify::dx("DEBUG", "Test notification.", ImGuiToastType_Info);

        ImGui::Text(std::format("ALPHA {}", ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w).c_str());
        ImGui::SameLine();
        ImGui::SliderFloat("Value", &(ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w), .1, 1);
        try
        {
            //Fusebox ESP
            g_gui_util->checkbox("Fusebox ESP");
            ImGui::SameLine();
            ImGui::PushItemWidth(50);
            ImGui::ColorPicker4("Fusebox Color", feature::get_feature_from_label_type_specific<fuse_box_esp>("Fusebox ESP")->color_esp, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs);

            ImGui::Checkbox("FuseboxLine ESP", &feature::get_feature_from_label_type_specific<fuse_box_esp>("Fusebox ESP")->line_esp);

            g_gui_util->checkbox("Ghost ESP");
            ImGui::SameLine();
            ImGui::PushItemWidth(50);
            ImGui::ColorPicker4("ESP Color", feature::get_feature_from_label_type_specific<ghost_esp>("Ghost ESP")->color_esp, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs);

            ImGui::Checkbox("Box ESP", &feature::get_feature_from_label_type_specific<ghost_esp>("Ghost ESP")->box_esp);
            ImGui::Checkbox("Line ESP", &feature::get_feature_from_label_type_specific<ghost_esp>("Ghost ESP")->line_esp);
            g_gui_util->checkbox("Infinite Sprint");
            g_gui_util->checkboxslider("Movement Speed", "", 0, 10);
        }
        catch (std::exception e)
        {
            LOG(WARNING) << "GUI ERROR: " << e.what();
        }
        ImGui::EndChild();
		ImGui::End();
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