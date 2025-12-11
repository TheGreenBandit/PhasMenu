#pragma once

#include "../common.hpp"
#include "core/toggle_feature.hpp"
#include "core/execute_feature.hpp"

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