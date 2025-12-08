#include "il2cpp.hpp"

namespace menu
{
	void il2cpp::init()
	{
		const HMODULE game_assembly = GetModuleHandleW(L"GameAssembly.dll");

		il2cpp_domain_get = reinterpret_cast<il2cpp_domain_get_t>(GetProcAddress(game_assembly, "il2cpp_domain_get"));
		il2cpp_domain_assembly_open = reinterpret_cast<il2cpp_domain_assembly_open_t>(GetProcAddress(game_assembly, "il2cpp_domain_assembly_open"));
		il2cpp_assembly_get_image = reinterpret_cast<il2cpp_assembly_get_image_t>(GetProcAddress(game_assembly, "il2cpp_assembly_get_image"));
		il2cpp_class_from_name = reinterpret_cast<il2cpp_class_from_name_t>(GetProcAddress(game_assembly, "il2cpp_class_from_name"));
		il2cpp_class_get_method_from_name = reinterpret_cast<il2cpp_class_get_method_from_name_t>(GetProcAddress(game_assembly, "il2cpp_class_get_method_from_name"));
		il2cpp_string_new_utf16 = reinterpret_cast<il2cpp_string_new_utf16_t>(GetProcAddress(game_assembly, "il2cpp_string_new_utf16"));

		domain = il2cpp_domain_get();
		assembly_image = il2cpp_assembly_get_image(il2cpp_domain_assembly_open(domain, "Assembly-CSharp"));

		init_methods();
	}

	void il2cpp::init_methods()
	{
		for (const auto& initializer : method_initializers)
			initializer();
	}
}