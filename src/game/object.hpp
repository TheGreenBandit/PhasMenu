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

	struct Boolean__VTable {
		VirtualInvokeData Equals;
		VirtualInvokeData Finalize;
		VirtualInvokeData GetHashCode;
		VirtualInvokeData ToString;
		VirtualInvokeData CompareTo;
		VirtualInvokeData GetTypeCode;
		VirtualInvokeData System_IConvertible_ToBoolean;
		VirtualInvokeData System_IConvertible_ToChar;
		VirtualInvokeData System_IConvertible_ToSByte;
		VirtualInvokeData System_IConvertible_ToByte;
		VirtualInvokeData System_IConvertible_ToInt16;
		VirtualInvokeData System_IConvertible_ToUInt16;
		VirtualInvokeData System_IConvertible_ToInt32;
		VirtualInvokeData System_IConvertible_ToUInt32;
		VirtualInvokeData System_IConvertible_ToInt64;
		VirtualInvokeData System_IConvertible_ToUInt64;
		VirtualInvokeData System_IConvertible_ToSingle;
		VirtualInvokeData System_IConvertible_ToDouble;
		VirtualInvokeData System_IConvertible_ToDecimal;
		VirtualInvokeData System_IConvertible_ToDateTime;
		VirtualInvokeData ToString_1;
		VirtualInvokeData System_IConvertible_ToType;
		VirtualInvokeData CompareTo_1;
		VirtualInvokeData Equals_1;
	};

	struct Boolean__StaticFields {
		struct String* TrueString;
		struct String* FalseString;
	};

	struct Boolean__Class {
		Il2CppClass_0 _0;
		Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
		struct Boolean__StaticFields* static_fields;
		const Il2CppRGCTXData* rgctx_data;
		Il2CppClass_1 _1;
		struct Boolean__VTable vtable;
	};

	struct Boolean 
	{
		bool m_value;
	};

	struct Boolean__Boxed 
	{
		struct Boolean__Class* klass;
		MonitorData* monitor;
		bool fields;
	};


	DECLARE_POINTER(Marshal_PtrToStructure, Object* (*)(void* pointer, Type* type, MethodInfo* mi), "mscorlib", "System.Runtime.InteropServices", "Marshal", "PtrToStructure", 1);
}