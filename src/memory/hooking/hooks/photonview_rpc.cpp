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

		std::string param = "";
		for (int i = 0; i < parameters->max_length; i++)
		{
			sdk::Object* p = parameters->vector[i];
			std::string add = "";

			if ((Il2CppClass*)p->klass == get_type_from_class("mscorlib", "System", "Boolean")->klass)//this works on our rpc calling but not on other rpc calling, our rpc calling with param doenst register the param also. something is def wrong
				add = ((*reinterpret_cast<bool*>(g_il2cpp.il2cpp_object_unbox((Il2CppObject*)p))) ? "True" : "False");
			else if (((Il2CppClass*)p->klass) == (get_type_from_class("mscorlib", "System", "Int32")->klass))
				add = std::to_string(*reinterpret_cast<int*>(g_il2cpp.il2cpp_object_unbox((Il2CppObject*)p)));
			else if ((Il2CppClass*)p->klass == get_type_from_class("mscorlib", "System", "String")->klass)
				add = S(reinterpret_cast<sdk::String*>(g_il2cpp.il2cpp_object_unbox((Il2CppObject*)p)));
			else
				add = ((Il2CppClass*)p->klass)->name;
				
			param += add += (parameters->max_length < 1 ? "None" : (parameters->max_length < 2 ? "" : i != parameters->max_length - 1 ? ", " : ""));
		}
			

		g_rpc_viewer->rpc_plain = std::format("NAME: {}, PARAMS: {}, TARGET: {}, FROM: {}", S(method_name), param, targ, S(sdk::PhotonView_ToString_ptr(_this, nullptr)));
		//LOG(INFO) << "A RPC WAS CALLED!\n" << S(method_name) << "\n For:" << targ << "\n From:" << S(sdk::PhotonView_ToString_ptr(_this, nullptr));
		//todo add argument logging?

		return g_hooking->get_original<hooks::photonview_rpc>()(_this, method_name, target, parameters, mi);
	}
}