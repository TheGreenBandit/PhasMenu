#include "features/feature_manager.hpp"
#include "util/game_util.hpp"

namespace menu
{
	class infinite_sprint : toggle_feature
	{
		using toggle_feature::toggle_feature;

		virtual void on_tick() override
		{
			if (game::network != nullptr)
			{
				auto lp = game::network->Fields.LocalPlayer;
				auto ps_ = lp->Fields.PlayerStamina;
				ps_->Fields.CurrentStamina = 10;
				ps_->Fields.StaminaDrained = false;
			}
		}
	};
	infinite_sprint g_infinite_sprint("Infinite Sprint", "Prevents your stamina from draining while sprinting.");
}