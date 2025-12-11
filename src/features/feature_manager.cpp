#include "feature_manager.hpp"
#include "thread_pool.hpp"
//#include "core/toggle/toggle_feature.hpp"
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
		auto net = g_game_util->get_network();//this does work here, definitely can work out features this way

		if (g.self.fast_sprint)
		{
			auto fpc_ = net->Fields.LocalPlayer->Fields.FirstPersonController;
			LOG(INFO) << fpc_->Fields.CurrentSpeed;
			fpc_->Fields.CurrentSpeed = ((!fpc_->Fields.CanSprint || !fpc_->Fields.IsSprinting) ? 1.6 * g.self.fast_sprint_value : 3.0 * g.self.fast_sprint_value);
			fpc_->Fields.UseHeadBob = false;
		}

		if (g.self.infinite_sprint)
		{
			auto lp = net->Fields.LocalPlayer;
			auto ps_ = lp->Fields.PlayerStamina;
			ps_->Fields.CurrentStamina = 10;
			ps_->Fields.StaminaDrained = false;
		}

		//if (g_gui.test_bool)
			//sdk::PlayerStamina_PreventStaminaDrainForTime_ptr(1.f, nullptr);
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