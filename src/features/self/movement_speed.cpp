#include "features/feature_manager.hpp"
#include "util/game_util.hpp"

namespace menu
{
	class movement_speed : toggle_feature
	{
		using toggle_feature::toggle_feature;

		virtual void on_tick() override
		{
			auto net = g_game_util->get_network();
			auto fpc_ = net->Fields.LocalPlayer->Fields.FirstPersonController;
			fpc_->Fields.CurrentSpeed = ((!fpc_->Fields.CanSprint || !fpc_->Fields.IsSprinting) ? 1.6 * value() : 3.0 * value());
			fpc_->Fields.UseHeadBob = false;
		}

		virtual void on_disable() override
		{
			auto net = g_game_util->get_network();
			auto fpc_ = net->Fields.LocalPlayer->Fields.FirstPersonController;
			fpc_->Fields.CurrentSpeed = 1.6;
			fpc_->Fields.UseHeadBob = true;
		}
	};
	movement_speed g_movement_speed("Movement Speed", "Override your speed to whatever you want.");
}