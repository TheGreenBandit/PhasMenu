#pragma once

#include "sdk.hpp"
#include "type.hpp"

namespace menu::sdk
{
	struct Object__Array__VTable
	{
	};
	struct Object__Array__Class 
	{
		Il2CppClass_0 _0;
		Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
		struct Object__Array__StaticFields* static_fields;
		const Il2CppRGCTXData* rgctx_data;
		Il2CppClass_1 _1;
		Object__Array__VTable vtable;
	};

	struct Object__VTable 
	{
		VirtualInvokeData Equals;
		VirtualInvokeData Finalize;
		VirtualInvokeData GetHashCode;
		VirtualInvokeData ToString;
	};

	struct Object__StaticFields 
	{
	};

	struct Object__Class 
	{
		Il2CppClass_0 _0;
		Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
		Object__StaticFields* static_fields;
		const Il2CppRGCTXData* rgctx_data;
		Il2CppClass_1 _1;
		Object__VTable vtable;
	};

	struct Object
	{
		Object__Class* klass;
		MonitorData* monitor;
	};

	struct Object__Array 
	{
		Object__Array__Class* klass;
		MonitorData* monitor;//MonitorData*
		Il2CppArrayBounds* bounds;//Il2CppArrayBounds*
		il2cpp_array_size_t max_length;//il2cpp_array_size_t*
		Object* vector[32];
	};
	DECLARE_POINTER(Marshal_PtrToStructure, Object* (*)(void* pointer, Type* type, MethodInfo* mi), "mscorlib", "System.Runtime.InteropServices", "Marshal", "PtrToStructure", 1);
}