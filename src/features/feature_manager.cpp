#include "feature_manager.hpp"
#include "thread_pool.hpp"

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

	void feature_manager::loop()
	{
	}
}