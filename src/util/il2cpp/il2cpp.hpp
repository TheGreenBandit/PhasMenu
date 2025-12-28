#pragma once

#include "common.hpp"
#include "game/il2cpptemp.hpp"

namespace menu
{
	//backend shit
	using il2cpp_domain_get_t = Il2CppDomain* (*)();
	using il2cpp_domain_assembly_open_t = Il2CppAssembly* (*)(Il2CppDomain* domain, const char* name);
	using il2cpp_assembly_get_image_t = Il2CppImage* (*)(Il2CppAssembly* assembly);
	using il2cpp_class_from_name_t = Il2CppClass*(*)(Il2CppImage* image, const char* namespaze, const char* name);
	using il2cpp_class_get_method_from_name_t = void* (*)(Il2CppClass* klass, const char* name, int argsCount);
	using il2cpp_string_new_utf16_t = void* (*)(const wchar_t* str, int len);

	using il2cpp_image_get_class_count_t = int(*)(void* image);
	using il2cpp_image_get_class_t = void* (*)(void* image, int index);
	using il2cpp_class_get_name_t = const char* (*)(void* klass);
	using il2cpp_class_get_namespace_t = const char* (*)(void* klass);
	using il2cpp_class_get_field_count_t = int(*)(void* klass);
	using il2cpp_class_get_fields_t = void* (*)(void* klass, void** iter);
	using il2cpp_field_get_name_t = const char* (*)(void* field);
	using il2cpp_field_get_type_t = Il2CppType * (*)(void* field);
	using il2cpp_type_get_name_t = const char* (*)(void* type);
	using il2cpp_class_get_methods_t = void* (*)(void* klass, void** iter);
	using il2cpp_method_get_name_t = const char* (*)(void* method);
	using il2cpp_class_get_type_t = Il2CppType * (*)(Il2CppClass* klass);
	using il2cpp_type_get_object_t = Il2CppObject * (*)(const Il2CppType* type);
	using il2cpp_array_new_t = void*(*)(Il2CppClass* klass, il2cpp_array_size_t  arg_count);
	using il2cpp_value_box_t = Il2CppObject*(*)(Il2CppClass* klass, void* data);

	class il2cpp
	{
	public:
		Il2CppDomain* domain = nullptr;
		Il2CppImage* assembly_image = nullptr;

		il2cpp_domain_get_t il2cpp_domain_get = nullptr;
		il2cpp_domain_assembly_open_t il2cpp_domain_assembly_open = nullptr;
		il2cpp_assembly_get_image_t il2cpp_assembly_get_image = nullptr;
		il2cpp_class_from_name_t il2cpp_class_from_name = nullptr;
		il2cpp_class_get_method_from_name_t il2cpp_class_get_method_from_name = nullptr;
		il2cpp_string_new_utf16_t il2cpp_string_new_utf16 = nullptr;

		il2cpp_image_get_class_count_t il2cpp_image_get_class_count = nullptr;
		il2cpp_image_get_class_t il2cpp_image_get_class = nullptr;
		il2cpp_class_get_name_t il2cpp_class_get_name = nullptr;
		il2cpp_class_get_namespace_t il2cpp_class_get_namespace = nullptr;
		il2cpp_class_get_field_count_t il2cpp_class_get_field_count = nullptr;
		il2cpp_class_get_fields_t il2cpp_class_get_fields = nullptr;
		il2cpp_field_get_name_t il2cpp_field_get_name = nullptr;
		il2cpp_field_get_type_t il2cpp_field_get_type = nullptr;
		il2cpp_type_get_name_t il2cpp_type_get_name = nullptr;
		il2cpp_class_get_methods_t il2cpp_class_get_methods = nullptr;
		il2cpp_method_get_name_t il2cpp_method_get_name = nullptr;
		il2cpp_class_get_type_t il2cpp_class_get_type = nullptr;
		il2cpp_type_get_object_t il2cpp_type_get_object = nullptr;
		il2cpp_array_new_t il2cpp_array_new = nullptr;
		il2cpp_value_box_t il2cpp_value_box = nullptr;
		std::vector<std::function<void()>> method_initializers;

		void dump_to_file(std::filesystem::path path);

		void init();
		void init_methods();
	};
	inline auto g_il2cpp = il2cpp();
}


inline Il2CppObject* get_type_from_class(Il2CppClass* clazz)
{
	const Il2CppType* type = g_il2cpp.il2cpp_class_get_type(clazz);
	if (!type)
		return nullptr;
	else
		return g_il2cpp.il2cpp_type_get_object(type);
}

inline Il2CppObject* get_type_from_class(const char* assembly_name, const char* namespaze, const char* className)
{
	Il2CppImage* image = g_il2cpp.assembly_image;
	if (strcmp(assembly_name, "Assembly-CSharp") != 0)
	{
		image = g_il2cpp.il2cpp_assembly_get_image(g_il2cpp.il2cpp_domain_assembly_open(g_il2cpp.domain, assembly_name));
		if (!image)
			return nullptr;
	}

	// Retrieve the Il2CppClass pointer
	Il2CppClass* targetClass = g_il2cpp.il2cpp_class_from_name(image, namespaze, className);
	if (!targetClass)
		return nullptr;

	// Retrieve the Il2CppType pointer
	const Il2CppType* targetType = g_il2cpp.il2cpp_class_get_type(targetClass);
	if (!targetType)
		return nullptr;

	// Retrieve the Il2CppObject pointer
	return g_il2cpp.il2cpp_type_get_object(targetType);
}

template <typename T>//weird fuckery here to get shit working for now
static T get_pointer(const char* assembly_name, const char* namespace_name, const char* class_name, const char* method_name, int args_count = 0)
{
	Il2CppImage* image = g_il2cpp.assembly_image;
	if (strcmp(assembly_name, "Assembly-CSharp") != 0)
	{
		image = g_il2cpp.il2cpp_assembly_get_image(menu::g_il2cpp.il2cpp_domain_assembly_open(menu::g_il2cpp.domain, assembly_name));
		if (!image)
			return nullptr;
	}

	Il2CppClass* klass = g_il2cpp.il2cpp_class_from_name(image, namespace_name, class_name);
	if (!klass)
		return nullptr;

	void* method = g_il2cpp.il2cpp_class_get_method_from_name(klass, method_name, args_count);
	if (!method)
		return nullptr;
	return reinterpret_cast<T>(static_cast<MethodInfo*>(method)->methodPointer);
}

#define DECLARE_POINTER(NAME, TYPE, ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT) \
using NAME = TYPE; \
inline NAME NAME##_ptr = nullptr; \
inline void Init_##NAME() { \
    NAME##_ptr = get_pointer<NAME>(ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT); \
    if (!NAME##_ptr) { } \
} \
namespace { struct NAME##_registrar { NAME##_registrar() { menu::g_il2cpp.method_initializers.push_back(Init_##NAME); } }; static NAME##_registrar NAME##_reg; }