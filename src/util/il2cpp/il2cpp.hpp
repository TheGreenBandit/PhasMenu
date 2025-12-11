#pragma once

#include "common.hpp"

struct method_info//temp reciever
{
	void* method_pointer;
};

namespace menu
{
	//backend shit
	using il2cpp_domain_get_t = void* (*)();
	using il2cpp_domain_assembly_open_t = void* (*)(void* domain, const char* name);
	using il2cpp_assembly_get_image_t = void* (*)(void* assembly);
	using il2cpp_class_from_name_t = void* (*)(void* image, const char* namespaze, const char* name);
	using il2cpp_class_get_method_from_name_t = void* (*)(void* klass, const char* name, int argsCount);
	using il2cpp_string_new_utf16_t = void* (*)(const wchar_t* str, int len);

	using il2cpp_image_get_class_count_t = int(*)(void* image);
	using il2cpp_image_get_class_t = void* (*)(void* image, int index);
	using il2cpp_class_get_name_t = const char* (*)(void* klass);
	using il2cpp_class_get_namespace_t = const char* (*)(void* klass);
	using il2cpp_class_get_field_count_t = int(*)(void* klass);
	using il2cpp_class_get_fields_t = void* (*)(void* klass, void** iter);
	using il2cpp_field_get_name_t = const char* (*)(void* field);
	using il2cpp_field_get_type_t = void* (*)(void* field);
	using il2cpp_type_get_name_t = const char* (*)(void* type);
	using il2cpp_class_get_methods_t = void* (*)(void* klass, void** iter);
	using il2cpp_method_get_name_t = const char* (*)(void* method);

	class il2cpp
	{
	public:
		void* domain = nullptr;
		void* assembly_image = nullptr;

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
		std::vector<std::function<void()>> method_initializers;

		void dump_to_file(std::filesystem::path path);

		void init();
		void init_methods();
	};
	inline auto g_il2cpp = il2cpp();
}

template <typename T>//weird fuckery here to get shit working for now
static T get_pointer(const char* assembly_name, const char* namespace_name, const char* class_name, const char* method_name, int args_count = 0)
{
	void* image = menu::g_il2cpp.assembly_image;
	if (strcmp(assembly_name, "Assembly-CSharp") != 0)
	{
		image = menu::g_il2cpp.il2cpp_assembly_get_image(menu::g_il2cpp.il2cpp_domain_assembly_open(menu::g_il2cpp.domain, assembly_name));
		if (!image)
			return nullptr;
	}

	void* klass = menu::g_il2cpp.il2cpp_class_from_name(image, namespace_name, class_name);
	if (!klass)
		return nullptr;

	void* method = menu::g_il2cpp.il2cpp_class_get_method_from_name(klass, method_name, args_count);
	if (!method)
		return nullptr;
	return reinterpret_cast<T>(static_cast<method_info*>(method)->method_pointer);
}

#define DECLARE_POINTER(NAME, TYPE, ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT) \
using NAME = TYPE; \
inline NAME NAME##_ptr = nullptr; \
inline void Init_##NAME() { \
    NAME##_ptr = get_pointer<NAME>(ASSEMBLY, NAMESPACE, CLASS, METHOD, ARGCOUNT); \
    if (!NAME##_ptr) { } \
} \
namespace { struct NAME##_registrar { NAME##_registrar() { menu::g_il2cpp.method_initializers.push_back(Init_##NAME); } }; static NAME##_registrar NAME##_reg; }