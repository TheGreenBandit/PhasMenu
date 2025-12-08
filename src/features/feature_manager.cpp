#include "feature_manager.hpp"
#include "thread_pool.hpp"
//#include "core/toggle/toggle_feature.hpp"
#include "renderer/gui/gui.hpp"
#include "game/sdk.hpp"
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
		if (g_gui.test_bool)
			sdk::PlayerStamina_PreventStaminaDrainForTime_ptr(1.f, nullptr);
		//for (auto& feature : m_features)
		{
		//	if (feature->get_type() == feature_type::toggle)
			{
		//		auto m_toggle_feature = static_cast<toggle_feature*>(feature);
				//if (m_toggle_feature->is_enabled())
				//	m_toggle_feature->on_tick();
			}
		}
	}
}