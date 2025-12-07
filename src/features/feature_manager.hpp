#pragma once

#include "../common.hpp"

namespace menu
{
	class feature_manager
	{
		bool m_running = false;
	public:
		
		void init();
		void destroy();

		void loop();
	};
	inline auto g_feature_manager = feature_manager();
}