#include "settings.hpp"
#include "thread_pool.hpp"
#include "features/feature_manager.hpp"

namespace menu
{
	bool loaded = false;
	void menu_settings::destroy()
	{
		m_running = false;
	}
	
	void menu_settings::init(const file& save_file)
	{
		m_running   = true;
		m_save_file = save_file;
		//load();
		g_thread_pool->push([this]
        {
                LOG(INFO) << "PUSHING SETTINGS LOOP " << std::this_thread::get_id();
			while (m_running)
			{
				std::this_thread::sleep_for(100ms);
				//if (loaded)
				//	save();
			}
            LOG(INFO) << "CLEARING FEATURE MANAGER LOOP " << std::this_thread::get_id();
		});
	}

	//template<typename T>
	//void process_features(pugi::xml_node features_node)
	//{
	//	for (variable_value<T>* vv : g_variable_values<T>) {
	//		pugi::xml_node node = features_node.child(vv->label().c_str());
	//		if (!node.empty()) {
	//			vv->is_enabled() = node.child("is_enabled");

	//			vv->m_value = node.child("value").text().as_string();
	//		}
	//	}
	//}
    const char* replace_spaces(const char* og)
    {
        std::string temp = og;
        std::replace(temp.begin(), temp.end(), ' ', '_');
        return temp.c_str();
    }
    const char* replace_scores(const char* og)
    {
        std::string temp = og;
        std::replace(temp.begin(), temp.end(), '_', ' ');
        return temp.c_str();
    }

    void menu_settings::save()
    {
        //std::filesystem::path path = std::getenv("appdata");
        //path /= "Blade";
        //path /= "Settings";
        //path /= "settings-menu.xml";

        //std::filesystem::create_directories(path.parent_path());

        //pugi::xml_document xml;
        //pugi::xml_node root = xml.append_child("menu");

        //// ===== FEATURES =====
        //pugi::xml_node features_node = root.append_child("features");
        //for (toggle_feature* tf : g_toggle_features)
        //{
        //    LOG(INFO) << "SAVING FEAURE! NAME: " << replace_spaces(tf->label().c_str()) << " ENABLED: " << tf->is_enabled() << " VALUE: " << tf->value() << " HOTKEY: " << tf->hotkey();
        //    pugi::xml_node node = features_node.append_child("feature");
        //    node.append_attribute("name") = replace_spaces(tf->label().c_str());
        //    node.append_child("enabled").text() = tf->is_enabled();
        //    node.append_child("value").text() = tf->value();
        //    node.append_child("hotkey").text() = tf->hotkey();
        //}

        //// ===== SPAWNER =====
        //pugi::xml_node spawner_node = root.append_child("spawner");
        //pugi::xml_node spawner_vehicle_node = spawner_node.append_child("vehicle");
        //auto p = g.spawner.vehicle;
        //spawner_vehicle_node.append_child("auto_rotate").text() = p.auto_rotate;
        //g_xml->append3f(spawner_vehicle_node, "offset", p.offset);
        //spawner_vehicle_node.append_child("spawn_inside").text() = p.spawn_inside;

        //// ===== GUI =====
        //pugi::xml_node gui_node = root.append_child("gui");
        //gui_node.append_child("menu_scale").text() = g.gui.menu_scale;
        //gui_node.append_child("menu_type").text() = g.gui.menu_type;

        //// ===== SETTINGS =====
        //pugi::xml_node settings_node = root.append_child("settings");
        //pugi::xml_node h = settings_node.append_child("hotkeys");
        //h.append_child("menu_toggle").text() = g.settings.hotkeys.menu_toggle;

        //// ===== WINDOW =====
        //pugi::xml_node window_node = root.append_child("window");
        //pugi::xml_node l = window_node.append_child("list_ui");
        //g_xml->append4f(l, "size", g.window.list_ui.size);
        //g_xml->append4f(l, "pos", g.window.list_ui.pos);

        //if (!xml.save_file(path.string().c_str()))
        //    LOG(WARNING) << "Failed to save XML to " << path;
        //else
        //    LOG(INFO) << "Settings saved successfully to " << path;
    }



    void menu_settings::load()
    {
        //std::filesystem::path path = std::getenv("appdata");
        //path /= "Blade";
        //path /= "Settings";
        //path /= "settings-menu.xml";

        //if (!std::filesystem::exists(path))
        //{
        //    LOG(INFO) << "Saving new settings!";
        //    save();
        //}

        //pugi::xml_document xml;
        //pugi::xml_parse_result result = xml.load_file(path.string().c_str());

        //if (!result)
        //{
        //    LOG(WARNING) << "FAILED TO LOAD OLD XML FILE! Path: " << path
        //        << " | Error: " << result.description();
        //    return;
        //}

        //pugi::xml_node root = xml.child("menu");
        //if (!root)
        //{
        //    LOG(WARNING) << "Invalid XML: missing <menu> root!";
        //    return;
        //}

        //// ===== FEATURES =====
        //pugi::xml_node features_node = root.child("features");
        //if (features_node)
        //{
        //    for (toggle_feature* tf : g_toggle_features)
        //    {
        //        // Find the <feature> node with matching name attribute
        //        pugi::xml_node node = features_node.child(replace_spaces(tf->label().c_str()));
        //        if (!node)
        //        {
        //            LOG(WARNING) << "No XML node for feature: " << tf->label();
        //            continue;
        //        }

        //        tf->is_enabled() = node.child("enabled").text().as_bool(false);
        //        tf->value() = node.child("value").text().as_float();
        //        tf->hotkey() = node.child("hotkey").text().as_int();
        //    }
        //}

        //// ===== SPAWNER =====
        //pugi::xml_node spawner_node = root.child("spawner");
        //if (spawner_node)
        //{
        //    pugi::xml_node spawner_vehicle_node = spawner_node.child("vehicle");
        //    if (spawner_vehicle_node)
        //    {
        //        auto p = g.spawner.vehicle;
        //        p.auto_rotate = spawner_vehicle_node.child("auto_rotate").text().as_bool();
        //        g_xml->child3f(spawner_vehicle_node, "offset", p.offset);
        //        p.spawn_inside = spawner_vehicle_node.child("spawn_inside").text().as_bool();
        //    }
        //}

        //// ===== GUI =====
        //pugi::xml_node gui_node = root.child("gui");
        //if (gui_node)
        //{
        //    g.gui.menu_scale = gui_node.child("menu_scale").text().as_float();
        //    g.gui.menu_type = static_cast<menutype>(gui_node.child("menu_type").text().as_int());
        //}

        //// ===== SETTINGS =====
        //pugi::xml_node settings_node = root.child("settings");
        //if (settings_node)
        //{
        //    pugi::xml_node h = settings_node.child("hotkeys");
        //    if (h)
        //        g.settings.hotkeys.menu_toggle = h.child("menu_toggle").text().as_int();
        //}

        //// ===== WINDOW =====
        //pugi::xml_node window_node = root.child("window");
        //if (window_node)
        //{
        //    pugi::xml_node l = window_node.child("list_ui");
        //    if (l)
        //    {
        //        g_xml->child4f(l, "size", g.window.list_ui.size);
        //        g_xml->child4f(l, "pos", g.window.list_ui.pos);
        //    }
        //}

        //loaded = true;
        //LOG(INFO) << "Settings loaded successfully from " << path;
    }

}