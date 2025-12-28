#pragma once

#include "features/feature_manager.hpp"
#include "util/game_util.hpp"
#include "game/photon_view.hpp"

namespace menu
{
	struct rpc_viewer : toggle_feature
	{
		using toggle_feature::toggle_feature;
	public:
		std::string rpc_plain;
		std::vector<std::string> rpc_list_plain;
		bool test = false;
		virtual void on_tick() override
		{
			if (!test)
				return;

			auto view = game::network->Fields.LocalPlayer->Fields.View;
			if (!view)
				return;

			auto object_class = get_type_from_class("mscorlib", "System", "Object")->klass;
			auto args = (sdk::Object__Array*)g_il2cpp.il2cpp_array_new(object_class, 1);

			bool value = true;
			auto bool_class = get_type_from_class("mscorlib", "System", "Boolean")->klass;
			sdk::Object* boxed_bool = (sdk::Object*)g_il2cpp.il2cpp_value_box(bool_class, &value);

			//args->vector[0] = boxed_bool;

			sdk::PhotonView_RPC_ptr(view, S_("SpawnDeadBodyNetworked"), sdk::RpcTarget::All, args, nullptr);

			test = false;
		}

		virtual void on_overlay() override
		{
			if (!(std::find(rpc_list_plain.begin(), rpc_list_plain.end(), rpc_plain) != rpc_list_plain.end()))
				rpc_list_plain.push_back(rpc_plain);

			ImGui::Begin("RPC Viewer");
			if (ImGui::Button("Log Recieved To File"))
			{
				test = true;
			}
			//add blocking rpcs
			ImGui::BeginChild("RPC_LIST");
			for (std::string rpc : rpc_list_plain)
			{
				ImGui::TextWrapped(rpc.c_str());
			}
			ImGui::EndChild();
			ImGui::End();

		}
	};
	static inline rpc_viewer* g_rpc_viewer = new rpc_viewer("RPC Viewer", "Look at RPCs being sent and log them to a file.");
}