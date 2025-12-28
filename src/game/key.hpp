#pragma once
#include "sdk.hpp"
#include "photon_object_interact.hpp"

namespace menu::sdk
{
	enum KeyType : int32_t
	{
		NONE,
		Main,
		Secondary,
		PermanentLock
	};

	struct KeyInfo
	{
		KeyType type;//0x18
		String* localeID;//0x20
		void* journalSprite;//0x28
	};

	struct KeyFields
	{
		MonoBehaviourPunFields MonoBehaviourPunFields;
		KeyInfo info;
		PhotonObjectInteract* photonInteract;
	};

	struct Key
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		KeyFields Fields;
	};
}