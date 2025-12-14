#pragma once
#include "common.hpp"

namespace menu
{
	enum class feature_flags : uint32_t
	{
		NONE = 0,
		EXTRA_MENU
	};
	class toggle_feature;
	inline std::vector<toggle_feature*> g_toggle_features;
	class toggle_feature
	{
		feature_flags m_flags = feature_flags::NONE;
		bool m_toggle = false;
		std::string m_label = "Default Null Feature";
		std::string m_desc = "Default Null Feature";
		int m_key = 0;
		bool m_last_state = false;
		float m_value = 0;
	public:
		toggle_feature(const std::string& label, const std::string& description, int key = -255): m_label(label), m_desc(description), m_key(key)
		{
			g_toggle_features.push_back(this);
		}

		toggle_feature(const std::string& label, const std::string& description, bool& toggle, int key = -255): m_label(label), m_desc(description), m_key(key)
		{
			g_toggle_features.push_back(this);
		}

		toggle_feature(const std::string& label, const std::string& description, feature_flags flags, int key = -255) : m_label(label), m_desc(description), m_key(key), m_flags(flags)
		{
			g_toggle_features.push_back(this);
		}

		toggle_feature(const std::string& label) : m_label(label), m_key(-255)
		{
			g_toggle_features.push_back(this);
		}

		virtual void on_tick() {};
		virtual void on_enable() {};
		virtual void on_disable() {};
		virtual void on_gui() {};//main gui render
		virtual void on_overlay() {};//overlay render

		inline bool& is_enabled()
		{
			return m_toggle;
		}

		inline bool& last_state()
		{
			return m_last_state;
		}

		inline std::string& label()
		{
			return m_label;
		}

		inline std::string& description()
		{
			return m_desc;
		}

		inline int& hotkey()
		{
			return m_key;
		}

		inline float& value()
		{
			return m_value;
		}	
		
		inline feature_flags& flags()
		{
			return m_flags;
		}

		template<typename T>
		inline T* as()
		{
			return static_cast<T*>(this);
		}
	};

	inline toggle_feature* g_default_toggle = new toggle_feature("NULL", "NULL");
}