#pragma once

#include "features/feature_manager.hpp"
#include "util/game_util.hpp"

namespace menu
{
	struct instakill_player : execute_feature
	{
		using execute_feature::execute_feature;

		virtual void action() override
		{
			if ((game::network != nullptr) && (g_game_util->selected_player != nullptr))
			{
				sdk::PhotonView* view = g_game_util->selected_player->Fields.View;
				sdk::Object__Array* args = (sdk::Object__Array*)g_il2cpp.il2cpp_array_new(get_type_from_class("mscorlib", "System", "Object")->klass, 1);
				sdk::PhotonView_RPC_ptr(view, S_("Dead"), sdk::RpcTarget::All, args, nullptr);//ez dead no host fixme
			}
		}
	};
	inline instakill_player* g_instakill_player = new instakill_player("Instakill", "Say byebye, no body no sound just death.");
}