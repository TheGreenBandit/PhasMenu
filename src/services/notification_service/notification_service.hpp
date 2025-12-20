#pragma once
#include "common.hpp"

namespace menu
{
	enum class notification_type 
	{
		INFO,
		SUCCESS,
		WARNING,
		DANGER
	};

	struct notification
	{
		notification_type type;
		const std::string title;
		const std::string message;
		const std::chrono::time_point<std::chrono::system_clock> created_on;
		const float destroy_in;
		float alpha;
	};

	class notification_service final
	{
		std::unordered_map<std::size_t, notification> notifications;

	public:
		notification_service();
		virtual ~notification_service();

		void push(notification n);
		void push(std::string title, std::string message, notification_type type = notification_type::INFO);
		std::vector<notification> get();
		void draw();

		std::map<notification_type, ImVec4> notification_colors =
		{
			{notification_type::INFO, ImVec4(0.80f, 0.80f, 0.83f, 1.00f)},
			{notification_type::SUCCESS, ImVec4(0.29f, 0.69f, 0.34f, 1.00f)},
			{notification_type::WARNING, ImVec4(0.69f ,0.49f, 0.29f, 1.00f) },
			{notification_type::DANGER, ImVec4(0.69f, 0.29f , 0.29f, 1.00f)}
		};
	};
	inline notification_service* g_notification_service{};
}