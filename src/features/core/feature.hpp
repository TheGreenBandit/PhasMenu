//#pragma once
//
//#include "common.hpp"
//
//namespace menu
//{
//	enum class feature_type : int32_t
//	{
//		toggle,
//		execute
//	};
//
//	class feature
//	{
//	public:
//		std::string m_name = "NULL NAME";
//		std::string m_description = "NULL DESC";
//		feature_type m_type;
//		int m_keybind = -255;
//		std::string get_name();
//		std::string get_description();
//		feature_type get_type();
//		int get_keybind();
//
//		feature(std::string name, std::string desc, feature_type type, int keybind)
//			: m_name(name), m_description(desc), m_type(type), m_keybind(keybind) 
//		{
//			//g_feature_manager.m_features.push_back(this);
//		}
//	};
//}