#pragma once

#include "sdk.hpp"

namespace menu::sdk
{
    struct RuntimeTypeHandle 
    {
        void* value;
    };

    struct __declspec(align(8)) Type__Fields 
    {
        RuntimeTypeHandle _impl;
    };

    struct Type__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData GetCustomAttributes;
        VirtualInvokeData GetCustomAttributes_1;
        VirtualInvokeData IsDefined;
        VirtualInvokeData get_MemberType;
        VirtualInvokeData __unknown;
        VirtualInvokeData get_DeclaringType;
        VirtualInvokeData get_ReflectedType;
        VirtualInvokeData get_Module;
        VirtualInvokeData __unknown_1;
        VirtualInvokeData __unknown_2;
        VirtualInvokeData __unknown_3;
        VirtualInvokeData get_MetadataToken;
        VirtualInvokeData GetFields;
        VirtualInvokeData GetProperties;
        VirtualInvokeData IsEnumDefined;
        VirtualInvokeData GetEnumName;
        VirtualInvokeData GetEnumNames;
        VirtualInvokeData get_IsSerializable;
        VirtualInvokeData get_ContainsGenericParameters;
        VirtualInvokeData IsSubclassOf;
        VirtualInvokeData IsAssignableFrom;
        VirtualInvokeData GetType;
        VirtualInvokeData __unknown_4;
        VirtualInvokeData __unknown_5;
        VirtualInvokeData __unknown_6;
        VirtualInvokeData __unknown_7;
        VirtualInvokeData __unknown_8;
        VirtualInvokeData get_DeclaringMethod;
        VirtualInvokeData __unknown_9;
        VirtualInvokeData get_IsArray;
        VirtualInvokeData __unknown_10;
        VirtualInvokeData get_IsByRef;
        VirtualInvokeData __unknown_11;
        VirtualInvokeData get_IsPointer;
        VirtualInvokeData __unknown_12;
        VirtualInvokeData get_IsConstructedGenericType;
        VirtualInvokeData get_IsGenericParameter;
        VirtualInvokeData get_IsGenericMethodParameter;
        VirtualInvokeData get_IsGenericType;
        VirtualInvokeData get_IsGenericTypeDefinition;
        VirtualInvokeData get_IsSZArray;
        VirtualInvokeData get_IsVariableBoundArray;
        VirtualInvokeData get_HasElementType;
        VirtualInvokeData __unknown_13;
        VirtualInvokeData __unknown_14;
        VirtualInvokeData GetArrayRank;
        VirtualInvokeData GetGenericTypeDefinition;
        VirtualInvokeData get_GenericTypeArguments;
        VirtualInvokeData GetGenericArguments;
        VirtualInvokeData get_GenericParameterPosition;
        VirtualInvokeData get_GenericParameterAttributes;
        VirtualInvokeData GetGenericParameterConstraints;
        VirtualInvokeData get_Attributes;
        VirtualInvokeData __unknown_15;
        VirtualInvokeData get_IsAbstract;
        VirtualInvokeData get_IsSealed;
        VirtualInvokeData get_IsClass;
        VirtualInvokeData get_IsNestedAssembly;
        VirtualInvokeData get_IsNestedPublic;
        VirtualInvokeData get_IsNotPublic;
        VirtualInvokeData get_IsPublic;
        VirtualInvokeData get_IsExplicitLayout;
        VirtualInvokeData get_IsCOMObject;
        VirtualInvokeData __unknown_16;
        VirtualInvokeData get_IsContextful;
        VirtualInvokeData IsContextfulImpl;
        VirtualInvokeData get_IsCollectible;
        VirtualInvokeData get_IsEnum;
        VirtualInvokeData get_IsMarshalByRef;
        VirtualInvokeData IsMarshalByRefImpl;
        VirtualInvokeData get_IsPrimitive;
        VirtualInvokeData __unknown_17;
        VirtualInvokeData get_IsValueType;
        VirtualInvokeData IsValueTypeImpl;
        VirtualInvokeData get_IsSignatureType;
        VirtualInvokeData GetConstructor;
        VirtualInvokeData GetConstructor_1;
        VirtualInvokeData GetConstructor_2;
        VirtualInvokeData __unknown_18;
        VirtualInvokeData GetConstructors;
        VirtualInvokeData __unknown_19;
        VirtualInvokeData GetEvent;
        VirtualInvokeData __unknown_20;
        VirtualInvokeData __unknown_21;
        VirtualInvokeData GetField;
        VirtualInvokeData __unknown_22;
        VirtualInvokeData GetFields_1;
        VirtualInvokeData __unknown_23;
        VirtualInvokeData GetMember;
        VirtualInvokeData GetMember_1;
        VirtualInvokeData GetMember_2;
        VirtualInvokeData __unknown_24;
        VirtualInvokeData GetMethod;
        VirtualInvokeData GetMethod_1;
        VirtualInvokeData GetMethod_2;
        VirtualInvokeData GetMethod_3;
        VirtualInvokeData GetMethod_4;
        VirtualInvokeData GetMethod_5;
        VirtualInvokeData __unknown_25;
        VirtualInvokeData GetMethods;
        VirtualInvokeData __unknown_26;
        VirtualInvokeData __unknown_27;
        VirtualInvokeData GetProperty;
        VirtualInvokeData GetProperty_1;
        VirtualInvokeData GetProperty_2;
        VirtualInvokeData GetProperty_3;
        VirtualInvokeData GetProperty_4;
        VirtualInvokeData GetProperty_5;
        VirtualInvokeData __unknown_28;
        VirtualInvokeData GetProperties_1;
        VirtualInvokeData __unknown_29;
        VirtualInvokeData get_TypeHandle;
        VirtualInvokeData GetTypeCodeImpl;
        VirtualInvokeData __unknown_30;
        VirtualInvokeData __unknown_31;
        VirtualInvokeData GetInterface;
        VirtualInvokeData __unknown_32;
        VirtualInvokeData __unknown_33;
        VirtualInvokeData IsInstanceOfType;
        VirtualInvokeData IsEquivalentTo;
        VirtualInvokeData GetEnumUnderlyingType;
        VirtualInvokeData GetEnumValues;
        VirtualInvokeData MakeArrayType;
        VirtualInvokeData MakeArrayType_1;
        VirtualInvokeData MakeByRefType;
        VirtualInvokeData MakeGenericType;
        VirtualInvokeData MakePointerType;
        VirtualInvokeData Equals_1;
        VirtualInvokeData get_IsSzArray;
        VirtualInvokeData FormatTypeName;
        VirtualInvokeData get_IsInterface;
        VirtualInvokeData InternalGetNameIfAvailable;
    };

    struct Type__StaticFields {
        struct Binder* s_defaultBinder;
        uint16_t Delimiter;
        struct Type__Array* EmptyTypes;
        struct Object* Missing;
        struct MemberFilter* FilterAttribute;
        struct MemberFilter* FilterName;
        struct MemberFilter* FilterNameIgnoreCase;
    };

    struct Type__Class {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        Type__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        Type__VTable vtable;
    };

    struct Type 
    {
        Type__Class* klass;
        MonitorData* monitor;
        Type__Fields fields;
    };
}