#pragma once
#include "sdk.hpp"
#include "il2cpptemp.hpp"
#include "object.hpp"

namespace menu::sdk
{

    struct __declspec(align(8)) PhotonPlayer__Fields
    {
        struct Room* _RoomReference_k__BackingField;
        int32_t actorNumber;
        bool IsLocal;
        bool _HasRejoined_k__BackingField;
        String* nickName;
        String* _UserId_k__BackingField;
        bool _IsInactive_k__BackingField;
        struct Hashtable_1* _CustomProperties_k__BackingField;
        Object* TagObject;
    };

    struct PhotonPlayer
    {
        struct PhotonPlayer__Class* klass;
        MonitorData* monitor;
        PhotonPlayer__Fields fields;
    };
    struct PhotonView__Fields 
    {
        MonoBehaviourFields _;
        uint8_t Group;
        int32_t prefixField;
        Object__Array* instantiationDataField;
        void* lastOnSerializeDataSent;//List_1_System_Object_*
        void* syncValues;//List_1_System_Object_
        Object__Array* lastOnSerializeDataReceived;
        //void* Synchronization; //ViewSynchronization__Enum
        int32_t Synchronization;
        bool mixedModeIsReliable;
        //void* OwnershipTransfer;//OwnershipOption__Enum
        int32_t OwnershipTransfer;
        //void* observableSearch;//PhotonView_ObservableSearch__Enum
        int32_t observableSearch;
        struct List_1_UnityEngine_Component_* ObservedComponents;
        struct MonoBehaviour__Array* RpcMonoBehaviours;
        bool _IsMine_k__BackingField;
        PhotonPlayer* Controller;
        int32_t _CreatorActorNr_k__BackingField;
        bool _AmOwner_k__BackingField;
        PhotonPlayer* Owner;
        int32_t ownerActorNr;
        int32_t controllerActorNr;
        int32_t sceneViewId;
        int32_t viewIdField;
        int32_t InstantiationId;
        bool isRuntimeInstantiated;
        bool removedFromLocalViewList;
        struct Queue_1_Photon_Pun_PhotonView_CallbackTargetChange_* CallbackChangeQueue;
        struct List_1_Photon_Pun_IOnPhotonViewPreNetDestroy_* OnPreNetDestroyCallbacks;
        struct List_1_Photon_Pun_IOnPhotonViewOwnerChange_* OnOwnerChangeCallbacks;
        struct List_1_Photon_Pun_IOnPhotonViewControllerChange_* OnControllerChangeCallbacks;
    };

    struct PhotonView {
        struct PhotonView__Class* klass;
        MonitorData* monitor;
        PhotonView__Fields fields;
    };

	struct ServerSettings
	{
		void* appSettings;//0x18 AppSettings
		String* devRegion;//0x20
		int32_t punLogging;//0x28 PunLogLevel
		bool enableSupportLogger; //0x2C
		bool runInBackground; //0x2D
		bool startInOfflineMode;//0x2E
		ListStringFields* rpcList;//0x30 List<string> what we are really after, can list every rpc in game using this
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
	DECLARE_POINTER(PhotonView_ToString, String*(*)(PhotonView* _this, MethodInfo* mi), "PhotonUnityNetworking", "Photon.Pun", "PhotonView", "ToString", 0)
	DECLARE_POINTER(PhotonView_RPC, void(*)(PhotonView* _this, String* method_name, RpcTarget target, Object__Array* paramters, MethodInfo* mi), "PhotonUnityNetworking", "Photon.Pun", "PhotonView", "RPC", 3)
	//DECLARE_POINTER(PhotonView_RPC, void(*)(String* method_name, PhotonPlayer* target, void* /*params object[]*/ paramters), "PhotonUnityNetworking", "Photon.Pun", "PhotonView", "RPC", 3)
}