#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	struct PhotonObjectInteract {};

	enum KeyType : int32_t
	{
		None,
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
		PhotonObjectInteract photonInteract;
	};

	struct Key
	{
		void* Clazz;
		void* Monitor;
		KeyFields Fields;
	};
}