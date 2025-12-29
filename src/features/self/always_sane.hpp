#pragma once

#include "features/feature_manager.hpp"
#include "util/game_util.hpp"

namespace menu
{
	struct always_sane : toggle_feature
	{
		using toggle_feature::toggle_feature;

		virtual void on_tick() override
		{
			if (game::network != nullptr)
			{
				auto lp = game::network->Fields.LocalPlayer;
				auto ps_ = lp->Fields.PlayerSanity;
				if (ps_->Fields.Insanity > 0)
				{
					ps_->Fields.Insanity = 0;

					sdk::Object__Array* args = (sdk::Object__Array*)g_il2cpp.il2cpp_array_new(get_type_from_class("mscorlib", "System", "Object")->klass, 1);
					auto single_class = get_class_from_name("mscorlib", "System", "Single");
					sdk::Single__Boxed* boxed_single = (sdk::Single__Boxed*)g_il2cpp.il2cpp_object_new(single_class);

					boxed_single->fields = 0.0f;
					args->vector[0] = (sdk::Object*)boxed_single;
					game::network->Fields.LocalPlayer->Fields.PlayerSanity->Fields.Insanity = 0;
					sdk::PhotonView_RPC_ptr(lp->Fields.View, S_("NetworkedUpdatePlayerSanity"), sdk::RpcTarget::All, args, nullptr);//update for everyone else
				}
			}
		}
	};
	inline always_sane* g_always_sane = new always_sane("Always Sane", "Prevents your sanity from draining.");
}