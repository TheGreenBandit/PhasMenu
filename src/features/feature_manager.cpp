#include "feature_manager.hpp"
#include "thread_pool.hpp"
#include "core/toggle_feature.hpp"
#include "renderer/gui/gui.hpp"
#include "game/sdk.hpp"
#include "util/game_util.hpp"

namespace menu
{
	void feature_manager::init()
	{
		m_running = true;
		g_thread_pool->push([this] 
		{
			while (m_running)
			{
				loop();
				std::this_thread::sleep_for(10ms);
			}
		});
	}

	void feature_manager::destroy()
	{
		m_running = false;
	}

	void feature_manager::loop()//test
	{
		
	}
}