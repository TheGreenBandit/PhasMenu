#pragma once
#include "sdk.hpp"

namespace menu::sdk
{
	struct __declspec(align(8)) StringFields
	{
		int32_t StringLength;
		uint16_t FirstChar;
	};

	struct String
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		StringFields Fields;
	};

	// String[]
	struct StringArray
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		Il2CppArrayBounds* Bounds; // Il2CppArrayBounds
		Il2CppArraySize* MaxLength; // Il2CppArraySizeT
		String* Vector[332];
	};

	struct __declspec(align(8)) ListStringFields
	{
		StringArray* Items;
		int32_t Size;
		int32_t Version;
		void* SyncRoot; // Object
	};

	// List<String>
	struct ListString
	{
		Il2CppClass* Clazz;
		MonitorData* Monitor;
		ListStringFields Fields;
	};

	DECLARE_POINTER(Marshal_PtrToStringAnsi, String* (*)(void* pointer, MethodInfo* mi), "mscorlib", "System.Runtime.InteropServices", "Marshal", "PtrToStringAnsi", 1);
}
