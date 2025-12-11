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
		auto net = g_game_util->get_network();

		if (g.self.fast_sprint)
		{
			auto fpc_ = net->Fields.LocalPlayer->Fields.FirstPersonController;
			LOG(INFO) << fpc_->Fields.CurrentSpeed;
			fpc_->Fields.CurrentSpeed = ((!fpc_->Fields.CanSprint || !fpc_->Fields.IsSprinting) ? 1.6 * g.self.fast_sprint_value : 3.0 * g.self.fast_sprint_value);
			fpc_->Fields.UseHeadBob = false;
		}

		for (auto feature : g_toggle_features)
		{
			if (feature->last_state() != feature->is_enabled())
			{
				feature->last_state() ? feature->on_disable() : feature->on_enable();
				feature->last_state() = feature->is_enabled();
			}

			if (feature->is_enabled())
				feature->on_tick();
		}
	}
}