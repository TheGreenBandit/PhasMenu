#pragma once
#include "sdk.hpp"
#include "player.hpp"

namespace menu::sdk
{
	struct Network;

	enum Role : uint32_t
	{
		None,
		Developer,
		Discord,
		Creator,
		Translator,
		Competition,
		Artist,
		Holiday22,
		Easter23,
		Halloween23,
		Holiday23,
		Easter24,
		Halloween24,
		Holiday24,
		Easter25,
		Halloween25,
		Holiday25,
		ApocalypseSilver,
		ApocalypseGold,
		LighthouseKeeper,
		LighthouseFerryman,
		Ranger,
		Inmate,
		Halloween24Foil,
		Holiday24Foil,
		Easter24Foil,
		AchievementHunter,
		Halloween25Foil,
		Holiday25Foil,
		Easter25Foil,
		TwitchDropChronicle,
		TwitchDropChronicleFoil,
		AmericanHeart,
		AmericanHeartFoil,
		FarmhouseFieldwork,
		TwitchDropGrafton,
		TwitchDropGraftonFoil,
		Anniversary25,
		TwitchCon25,
		Anniversary25Foil,
		TwitchCon25Foil,
		DinerGhostInTheMachine,
		NellsDiner,
		TwitchDropNellsDiner,
		TwitchDropNellsDinerFoil,
		Moneybags
	};

	struct __declspec(align(8)) NetworkPlayerSpotFields
	{
		bool PlayerReady;
		int PlayerCharacterIndex;
		PhotonPlayer* PhotonPlayer; // Photon.Realtime.Player //neeeedddddddd, very useful
		String* UnityPlayerID;//String*
		int Experience;
		int Level;
		int Prestige;
		Player* Player;
		float PlayerVolume;
		String* AccountName;//String*
		bool IsKicked;
		bool IsHacker;
		bool IsBlocked;
		void* RoleBadges; // ???[]
		Role Role; // ???
		int PrestigeIndex;
		bool PrestigeTheme;
		void* VotedContract; // Contract
		int32_t PlatformType; // StoreSDKManager.???
		bool HasReceivedPlayerInformation;
		bool PlayerIsBlocked;
		int32_t LegacyLevel;
		int32_t LegacyAccent;
		int32_t LegacyBackground;
		int32_t LegacyColor;
		void* PlayerEquipment;
		bool HasBroughtItems;
		int32_t TotalEquipmentCost;
		void* OnBlockMuteStateChanged;
	};

	// Network.PlayerSpot
	struct NetworkPlayerSpot
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		NetworkPlayerSpotFields Fields;
	};

	// Network.PlayerSpot[]
	struct NetworkPlayerSpotArray
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		Il2CppArrayBounds* Bounds; // Il2CppArrayBounds
		il2cpp_array_size_t* MaxLength; // Il2CppArraySizeT
		NetworkPlayerSpot* Vector[32];
	};

	struct __declspec(align(8)) ListNetworkPlayerSpotFields
	{
		NetworkPlayerSpotArray* Items;
		int32_t Size;
		int32_t Version;
		Object* SyncRoot; // Object
	};

	// List<Network.PlayerSpot>
	struct ListNetworkPlayerSpot
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		ListNetworkPlayerSpotFields Fields;
	};

	struct NetworkFields
	{
		MonoBehaviourPunCallbacksFields MonoBehaviourPunCallbacksFields; // MonoBehaviourPunCallbacksFields derived class field
		Player* LocalPlayer;
		ListNetworkPlayerSpot* PlayersData;
		void* PlayerColors; // Color[]
		void* DefaultPlayerColors; // Color[]
		void* JoinedLobby; // UnityEvent
		void* JoinedRoom; // UnityEvent
		void* LeftRoom; // UnityEvent
		void* Disconnected; // UnityEvent
		void* OnMicrophoneChanged; // Network.???
		void* OnMasterClientSwitchedEvent; // Network.???
		void* OnPlayerLeftRoomEvent; // Network.???
		void* OnPlayerSpotAssigned; // Network.???
		void* OnLocalPlayerSpawned; // UnityEvent
		void* OnSeasonalEventCompleted; // UnityEvent
		void* OnPlayerColorChanged; // UnityEvent
		void* LevelSystem; // LevelSystem
		bool IsChangingScenes;
		String* LastOnlineRoomName;//String*
		void* RecentKickedFromRooms; // HashSet<String>
		bool FailedToConnectToVivox;
		bool IsAttemptingVivoxLogin;
		void* InviteSystem; // Network.InviteSystem
		bool IsChangingRooms;
		String* ChangeToRegionOnDisconnect;//String*
	};

	struct Network
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		NetworkFields Fields;
	};

	DECLARE_POINTER(Network_Get_Network, Network* (*)(MethodInfo* mi), "Assembly-CSharp", "", "Network", "get_Instance", 0);
}