#include "notification_service.hpp"
#include "util/gui_util.hpp"

namespace menu
{
	notification_service::notification_service()
	{
		g_notification_service = this;
	}

	notification_service::~notification_service()
	{
		g_notification_service = nullptr;
	}

	void notification_service::push(notification n)
	{
		notifications.emplace(std::hash<std::string>{}(n.message + n.title), n);
	}

	void notification_service::push(std::string title, std::string message, notification_type type)
	{
		push({ type, title, message, std::chrono::system_clock::now(), 3000.f , 1.f });
	}

	std::vector<notification> notification_service::get()//all things are handled in the get function as this is called rapidly
	{
		std::vector<notification> notifications_to_send;
		std::vector<std::size_t> to_remove;
		for (auto& n : notifications) 
		{
			std::chrono::time_point<std::chrono::system_clock> curTime = std::chrono::system_clock::now();
			const float time_diff = (float)std::chrono::duration_cast<std::chrono::milliseconds>(curTime - n.second.created_on).count();
			n.second.alpha = 1;
			if (n.second.destroy_in <= time_diff) 
			{
				n.second.alpha = 1.f - ((time_diff - n.second.destroy_in) / 600);
				n.second.alpha = n.second.alpha < 0.f ? 0.f : n.second.alpha;
			}

			if (n.second.alpha > 0.f)
				notifications_to_send.push_back(n.second);
			else 
				to_remove.push_back(n.first);
		}
		for (std::size_t k : to_remove)
			notifications.erase(k);

		return notifications_to_send;
	}

	void notification_service::draw()
	{
		if (notifications.empty())
			return;
		auto notifications = get();
		for (int i = 0; i < notifications.size(); i++)
		{
			notification n = notifications[i];
			ImVec2 screen = g_gui_util->get_screen_size();
			ImGui::SetNextWindowBgAlpha(n.alpha);
			ImGui::SetNextWindowSize(ImVec2(200.f, 200.f));
			ImGui::SetNextWindowPos(ImVec2(screen.x - 245.f, (i * 200.f) + (i * 45.f)));//sizing shit, make me nicer
			ImVec4 col = notification_colors.find(n.type)->second;
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(col.x, col.y, col.z, n.alpha));
			ImGui::Begin(std::to_string(i).c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
			ImGui::Text(n.title.c_str());//add icon too
			ImGui::Separator();
			ImGui::TextWrapped(n.message.c_str());
			ImGui::End();
			ImGui::PopStyleColor();
		}
	}
}