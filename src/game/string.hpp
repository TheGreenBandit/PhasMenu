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
		void* Clazz;
		void* Monitor;
		StringFields Fields;
	};

	// String[]
	struct StringArray
	{
		void* Clazz;
		void* Monitor;
		void* Bounds; // Il2CppArrayBounds
		void* MaxLength; // Il2CppArraySizeT
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
		void* Clazz;
		void* Monitor;
		ListStringFields Fields;
	};

	DECLARE_POINTER(Marshal_PtrToStringAnsi, String* (*)(void* pointer, method_info* mi), "mscorlib", "System.Runtime.InteropServices", "Marshal", "PtrToStringAnsi", 1);
}
