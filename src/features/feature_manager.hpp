#pragma once

#include "../common.hpp"
//#include "core/feature.hpp"
//#include "core/toggle/toggle_feature.hpp"
//#include "core/execute/executable_feature.hpp"

namespace menu
{
	class feature_manager
	{
		bool m_running = false;
	public:
		//std::vector<feature*> m_features;

		void init();
		void destroy();
		void loop();

		//feature* get_feature_from_name(std::string name);
	};
	inline auto g_feature_manager = feature_manager();
}