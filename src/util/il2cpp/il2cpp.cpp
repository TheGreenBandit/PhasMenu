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

        il2cpp_image_get_class_count = reinterpret_cast<il2cpp_image_get_class_count_t>(GetProcAddress(game_assembly, "il2cpp_image_get_class_count"));
        il2cpp_image_get_class = reinterpret_cast<il2cpp_image_get_class_t>(GetProcAddress(game_assembly, "il2cpp_image_get_class"));
        il2cpp_class_get_name = reinterpret_cast<il2cpp_class_get_name_t>(GetProcAddress(game_assembly, "il2cpp_class_get_name"));
        il2cpp_class_get_namespace = reinterpret_cast<il2cpp_class_get_namespace_t>(GetProcAddress(game_assembly, "il2cpp_class_get_namespace"));
        il2cpp_class_get_field_count = reinterpret_cast<il2cpp_class_get_field_count_t>(GetProcAddress(game_assembly, "il2cpp_class_get_field_count"));
        il2cpp_class_get_fields = reinterpret_cast<il2cpp_class_get_fields_t>(GetProcAddress(game_assembly, "il2cpp_class_get_fields"));
        il2cpp_field_get_name = reinterpret_cast<il2cpp_field_get_name_t>(GetProcAddress(game_assembly, "il2cpp_field_get_name"));
        il2cpp_field_get_type = reinterpret_cast<il2cpp_field_get_type_t>(GetProcAddress(game_assembly, "il2cpp_field_get_type"));
        il2cpp_type_get_name = reinterpret_cast<il2cpp_type_get_name_t>(GetProcAddress(game_assembly, "il2cpp_type_get_name"));
        il2cpp_class_get_methods = reinterpret_cast<il2cpp_class_get_methods_t>(GetProcAddress(game_assembly, "il2cpp_class_get_methods"));
        il2cpp_method_get_name = reinterpret_cast<il2cpp_method_get_name_t>(GetProcAddress(game_assembly, "il2cpp_method_get_name"));


		domain = il2cpp_domain_get();
		assembly_image = il2cpp_assembly_get_image(il2cpp_domain_assembly_open(domain, "Assembly-CSharp"));

		init_methods();
	}
    //wip /////////////////////////////////////////////
    std::string map_csharp_to_cpp(const std::string& t)
    {
        static const std::unordered_map<std::string, std::string> map =
        {
            {"System.Boolean", "bool"},
            {"System.Byte", "uint8_t"},
            {"System.SByte", "int8_t"},
            {"System.Char", "char"},
            {"System.Int16", "int16_t"},
            {"System.UInt16", "uint16_t"},
            {"System.Int32", "int"},
            {"System.UInt32", "unsigned int"},
            {"System.Int64", "int64_t"},
            {"System.UInt64", "uint64_t"},
            {"System.Single", "float"},
            {"System.Double", "double"},
            {"System.String", "std::string"},
            {"System.Object", "void*"},

        };

        auto it = map.find(t);
        if (it != map.end())
            return it->second;

        return ""; // unknown
    }


    int counter = 0;
    std::unordered_map<std::string, std::string> cache;
    std::string sanitize(const char* name) {
        if (!name || name[0] == '\0') return "unknown";

        std::string str_name(name);
        bool valid = true;
        for (char c : str_name) {
            if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_') {
                valid = false;
                break;
            }
        }
        if (valid)
            return str_name;

        if (cache.count(str_name)) return cache[str_name];

        std::ostringstream oss;
        oss << "Unk_" << std::setw(4) << std::setfill('0') << counter++;
        std::string sanitized = oss.str();

        cache[str_name] = sanitized;
        return sanitized;
    }

    std::string sanitize_type(const char* name, std::string& out_comment)
    {
        out_comment.clear();

        if (!name || name[0] == '\0')
            return "void*";

        std::string type(name);
        {
            std::string mapped = map_csharp_to_cpp(type);
            if (!mapped.empty())
                return mapped;
        }

        bool valid = true;
        for (char c : type)
        {
            if (!(std::isalnum((unsigned char)c) ||
                c == '_' || c == '.' ||
                c == '<' || c == '>' ||
                c == '[' || c == ']'))
            {
                valid = false;
                break;
            }
        }

        if (valid)
            return type;

        static int ucounter = 0;
        std::ostringstream oss;
        oss << "unk_" << std::setw(4) << std::setfill('0') << ucounter++;

        out_comment = "// class " + type;
        return "void* " + oss.str();
    }

    void il2cpp::dump_to_file(std::filesystem::path path)
    {
        if (!assembly_image) return;

        std::ofstream out(path);
        if (!out.is_open()) 
            return;

        out << "#pragma once\n";
        out << "#include \"dump_includes.hpp\"\n\n";

        int class_count = il2cpp_image_get_class_count(assembly_image);
        for (int i = 0; i < class_count; i++)
        {
            void* klass = il2cpp_image_get_class(assembly_image, i);
            if (!klass) 
                continue;

            const char* class_name = il2cpp_class_get_name(klass);
            const char* namespaze = il2cpp_class_get_namespace(klass);

            out << "namespace " << (namespaze ? sanitize(namespaze) : "global") << " {\n";
            out << "class " << sanitize(class_name) << " {\npublic:\n";

            void* field_iter = nullptr;
            while (auto field = il2cpp_class_get_fields(klass, &field_iter))
            {
                const char* field_name = il2cpp_field_get_name(field);
                void* type = il2cpp_field_get_type(field);
                const char* type_name = il2cpp_type_get_name(type);

                std::string comment;
                std::string type_out = sanitize_type(type_name, comment);

                out << "    " << type_out << " " << sanitize(field_name);

                if (!comment.empty())
                    out << " " << comment;

                out << ";\n";
            }

            void* method_iter = nullptr;
            while (auto method = il2cpp_class_get_methods(klass, &method_iter))
            {
                const char* method_name = il2cpp_method_get_name(method);
                out << "    void " << sanitize(method_name) << "();\n";
            }

            out << "};\n}\n\n";
        }

        out.close();
    }


	void il2cpp::init_methods()
	{
		for (const auto& initializer : method_initializers)
			initializer();
	}
}