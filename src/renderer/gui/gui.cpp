#include "gui.hpp"
#include "renderer/renderer.hpp"
#include "util/gui_util.hpp"

namespace menu
{
	void gui::init()
	{
        ImVec4* colors = ImGui::GetStyle().Colors;
        {
            colors[ImGuiCol_WindowBg] = ImVec4(0.03f, 0.03f, 0.03f, 0.10f);
            colors[ImGuiCol_ChildBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
            colors[ImGuiCol_Border] = ImVec4(0.10f, 0.30f, 0.10f, 1.00f);

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

	void gui::render()//bug, discord overlay appears on loader, menu only crashes on reinject if gui was displayed previously, look into me, reproducible, find out what isnt clearing properly
	{
        //if (!menu_open)
        //    return;
		handle_input();
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(805, 366));
		ImGui::Begin("PhasMenu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
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
        ImGui::Checkbox("Speed", &g.self.fast_sprint);
        ImGui::Text(std::format("ALPHA {}", ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w).c_str());

        ImGui::SameLine();
        ImGui::SliderFloat("Value", &g.self.fast_sprint_value, .1, 5);
        try
        {
            g_gui_util->checkbox("Infinite Sprint");
            g_gui_util->checkboxslider("Movement Speed", ".", 0, 10);
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
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            if (!menu_open)
				SetForegroundWindow(g_renderer.gui_hwnd);
            else
                SetForegroundWindow(FindWindowA(NULL, "Phasmophobia"));
            menu_open = !menu_open;
        }
	}
}