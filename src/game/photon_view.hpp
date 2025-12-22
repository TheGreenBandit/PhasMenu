#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	struct PhotonViewFields
	{

	};

	struct PhotonView
	{

	};
	struct PhotonPlayer 
	{

	};

	struct ServerSettings
	{
		void* appSettings;//0x18 AppSettings
		String* devRegion;//0x20
		int32_t punLogging;//0x28 PunLogLevel
		bool enableSupportLogger; //0x2C
		bool runInBackground; //0x2D
		bool startInOfflineMode;//0x2E
		void* rpcList;//0x30 List<string> what we are really after, can list every rpc in game using this
	};

	struct PhotonNetwork
	{
		String* gameVersion;//0x0
		void* networkingClient; //LoadBalancingClient 0x8
		int MAX_VIEW_IDS; //0x10
		//String* serverSettingsFileName;//default "PhotonServerSettings"
		ServerSettings* photonServerSettings;//0x18
		//not writing the rest out fuck it
	};

	enum RpcTarget : int32_t
	{
		All,
		Others,
		MasterClient,
		AllBuffered,
		OthersBuffered,
		AllViaServer,
		AllBufferedViaServer
	};
	//can get rpc names off this, and more
	DECLARE_POINTER(PhotonView_RPC, void(*)(String* method_name, RpcTarget target, void* /*params object[]*/ paramters), "PhotonUnityNetworking", "Photon.Pun", "PhotonView", "RPC", 3)
	//DECLARE_POINTER(PhotonView_RPC, void(*)(String* method_name, PhotonPlayer* target, void* /*params object[]*/ paramters), "PhotonUnityNetworking", "Photon.Pun", "PhotonView", "RPC", 3)
}