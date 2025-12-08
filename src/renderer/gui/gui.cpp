#include "gui.hpp"

namespace menu
{
	void gui::init()
	{

	}

	void gui::render()
	{
		handle_input();

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(805, 366));
		ImGui::Begin("PhasMenu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		ImGui::Button("Welcome");
		ImGui::End();
	}

	void gui::handle_input()
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
			menu_open = !menu_open;
	}
}