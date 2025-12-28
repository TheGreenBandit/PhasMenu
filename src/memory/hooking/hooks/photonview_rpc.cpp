#include "../hooking.hpp"
#include "util/game_util.hpp"
#include "features/debug/rpc_viewer.hpp"

namespace menu
{
	void hooks::photonview_rpc(sdk::PhotonView* _this, sdk::String* method_name, sdk::RpcTarget target, sdk::Object__Array* parameters, MethodInfo* mi)
	{
		std::string targ = "None";
		switch (target)
		{
			case sdk::All: targ = "All"; break;
			case sdk::Others: targ = "Others"; break;
			case sdk::MasterClient: targ = "MasterClient"; break;
			case sdk::AllBuffered: targ = "AllBuffered"; break;
			case sdk::OthersBuffered: targ = "OthersBuffered"; break;
			case sdk::AllViaServer: targ = "AllViaServer"; break;
			case sdk::AllBufferedViaServer: targ = "AllBufferedViaServer"; break;
			default: targ = "NULL?"; break;
		}

		g_rpc_viewer->rpc_plain = std::format("NAME: {}, PARAMS: {}, TARGET: {}, FROM: {}", S(method_name), "Unsupported", targ, S(sdk::PhotonView_ToString_ptr(_this, nullptr)));
		//LOG(INFO) << "A RPC WAS CALLED!\n" << S(method_name) << "\n For:" << targ << "\n From:" << S(sdk::PhotonView_ToString_ptr(_this, nullptr));
		//todo add argument logging?

		return g_hooking->get_original<hooks::photonview_rpc>()(_this, method_name, target, parameters, mi);
	}
}