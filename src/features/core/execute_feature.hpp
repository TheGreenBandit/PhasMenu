#pragma once
#include "common.hpp"

namespace menu
{
	class execute_feature;
	inline std::vector<execute_feature*> g_execute_features;
	class execute_feature
	{
		std::string m_label = "NULL";
		std::string m_desc = "NULL";
		int m_key = 0;

	public:
		execute_feature(const std::string label, const std::string_view& description) : m_label(label), m_desc(description)
		{
			g_execute_features.push_back(this);
		}

		execute_feature(const std::string label) : m_label(label), m_desc("")
		{
			g_execute_features.push_back(this);
		}

		virtual void action() {};

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

		template<typename T>
		inline T as()
		{
			return (T)this;
		}
	};

	inline execute_feature* g_default_execute = new execute_feature("NULL", "NULL");
}