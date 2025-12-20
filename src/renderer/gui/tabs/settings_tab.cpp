#include "../gui.hpp"

namespace menu
{
	void gui::settings_tab()
	{
        ImGui::SliderFloat("Window Alpha", &(ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w), .1, 1);
        ImGui::SliderFloat("Border Size", &ImGui::GetStyle().WindowBorderSize, 1, 50);
		ImGui::Checkbox("Rainbow Border", &g.gui.rainbow_border);//make this into a feature, this way the slider can be adjusted from its popup
        ImGui::SliderFloat("Rainbow Border Speed", &g.gui.rainbow_border_speed, .01, 1);

		ImGui::SeparatorText("Debug Stuff");

        if (ImGui::Button("DUMP TO FILE"))
            g_il2cpp.dump_to_file(g_file_manager.get_base_dir() / "sdk_dump.hpp");
        if (ImGui::Button("Test Log"))
            LOG(INFO) << "TEST";
        if (ImGui::Button("Test Notification"))
            g_notification_service->push("TEST NOTIFICATION!", "TEST MESSAGE");
        if (ImGui::Button("List Features"))
        {
            LOG(INFO) << "LOGGING " << g_toggle_features.size() << " FEATURES!";
            for (auto f : g_toggle_features)
                LOG(INFO) << f->label();
        }
	}
}