#include "features/feature_manager.hpp"
#include "util/game_util.hpp"

namespace menu
{
	class movement_speed : toggle_feature
	{
		using toggle_feature::toggle_feature;
		sdk::FirstPersonController* fpc;
		virtual void on_tick() override
		{
			fpc = game::network->Fields.LocalPlayer->Fields.FirstPersonController;
			fpc->Fields.CurrentSpeed = ((!fpc->Fields.CanSprint || !fpc->Fields.IsSprinting) ? 1.6 * value() : 3.0 * value());
			fpc->Fields.UseHeadBob = false;
		}

		virtual void on_disable() override
		{
			fpc->Fields.CurrentSpeed = 1.6;
			fpc->Fields.UseHeadBob = true;
		}
	};
	movement_speed g_movement_speed("Movement Speed", "Override your speed to whatever you want.");
}