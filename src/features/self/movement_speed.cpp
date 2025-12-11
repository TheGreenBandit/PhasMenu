#include "features/feature_manager.hpp"
#include "util/game_util.hpp"

namespace menu
{
	class movement_speed : toggle_feature
	{
		using toggle_feature::toggle_feature;

		virtual void on_tick() override
		{
			auto net = g_game_util->get_network();//must be in each individual loop, maybe make tick have the network argument?
			{
				auto lp = net->Fields.LocalPlayer;
				LOG(INFO) << lp->Fields.MovementSpeed;
				lp->Fields.MovementSpeed = value();
			}
		}
	};
	movement_speed g_movement_speed("Movement Speed", "Override your speed to whatever you want.");
}