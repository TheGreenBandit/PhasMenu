#include "gui.hpp"

namespace menu
{
	void gui::init()
	{
        ImVec4* colors = ImGui::GetStyle().Colors;
        {
            colors[ImGuiCol_WindowBg] = ImVec4(0.03f, 0.03f, 0.03f, 0.50f);
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

	void gui::render()
	{
		handle_input();

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(805, 366));
		ImGui::Begin("PhasMenu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		ImGui::Button("Welcome");
		ImGui::End();
	}

	void gui::handle_input()
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
			menu_open = !menu_open;
	}
}